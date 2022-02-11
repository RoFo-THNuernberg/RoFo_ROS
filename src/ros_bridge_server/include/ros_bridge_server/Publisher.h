#pragma once

#include "ros/ros.h"

#include <string>

#include "RosMsgs.h"
#include "Socket.h"

class Publisher 
{
    public:
        virtual ~Publisher() {}

        virtual bool recvMessage() = 0;
        virtual bool compareTopic(std::string const& topic) = 0;

};

template <typename T, typename S> class PublisherImpl : public Publisher
{
    public:
        PublisherImpl(ros::NodeHandle& node_handle, std::string const& topic, Socket& sock) : _pub{node_handle.advertise<T>(topic, 10, false)}, _topic{topic}, _sock{sock} {}

        ~PublisherImpl() {}

        bool recvMessage() override
        {
            S ros_msg;

            int32_t msg_len = ros_msg.getSize();

            if(msg_len == 0)
            {
                if(_sock.socket_receive((uint8_t*)&msg_len, sizeof(msg_len)) == SOCKET_FAIL)
                    return false;
            }

            uint8_t* rx_buffer = new uint8_t[msg_len];
            if(_sock.socket_receive(rx_buffer, msg_len) == SOCKET_FAIL)
                return false;

            ros_msg.deserialize(rx_buffer);

            _pub.publish((T)ros_msg);

            delete[] rx_buffer;

            return true;
        }

        bool compareTopic(std::string const& topic)
        {
            return _topic == topic;
        }

    private:
        ros::Publisher _pub;
        std::string const _topic;
        Socket& _sock;
};