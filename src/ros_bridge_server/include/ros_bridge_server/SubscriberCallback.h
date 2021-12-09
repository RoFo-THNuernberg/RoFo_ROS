#pragma once

#include "ros/ros.h"
#include "RosMsgs.h"
#include "Socket.h"
#include "msg_id.h"

#include <string>

class SubscriberCallback
{
    public:
        SubscriberCallback(std::string topic, Socket* sock) : _topic{topic}, _sock{sock} {}

        template <typename T, typename S> void create_subscribtion(std::string const& topic, ros::NodeHandle* node_handle)
        {
            _sub = node_handle->subscribe(topic, 1, &SubscriberCallback::_subscribtion_callback<T, S>, this);
        }

        template <typename T, typename S> void _subscribtion_callback(T const& msg)
        {   
            ROS_INFO("sub callback----------------------------------------------------------------");

            S local_msg = (S)msg;
            
            uint8_t pkt_buffer[2 + _topic.size() + local_msg.getSize()];
            
            int pkt_len = 0;

            pkt_buffer[0] = PUBLISH_ID;
            pkt_len++;
            
            memcpy(pkt_buffer + pkt_len, _topic.c_str(), _topic.size());
            pkt_len += _topic.size();

            pkt_buffer[pkt_len] = '\0';
            pkt_len++;
        
            local_msg.serialize(pkt_buffer + pkt_len);
            pkt_len += local_msg.getSize();
            

            _sock->socket_send(pkt_buffer, pkt_len);
        }

    private:
        std::string _topic;
        ros::Subscriber _sub;
        Socket* _sock;
};
