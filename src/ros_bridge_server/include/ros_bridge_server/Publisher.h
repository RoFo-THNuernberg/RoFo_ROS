#pragma once

#include "ros/ros.h"

#include <string>

#include "RosMsgs.h"

class PublisherInterface 
{
    public:
        ~PublisherInterface() {}
        virtual void publish() = 0;
        virtual std::string getTopic() = 0;
        virtual ros_msgs::RosMsg* getMsgType() = 0;

};

template <typename T> class Publisher : public PublisherInterface
{
    public:
        Publisher(ros::NodeHandle* node_handle, std::string const& topic, ros_msgs::RosMsg* msg) : _pub{node_handle->advertise<T>(topic, 10, false)}, _msg{msg} {}

        ~Publisher()
        {
            delete _msg;
        }

        void publish() override 
        {
            _pub.publish(*((T*)_msg));
        }

        std::string getTopic() override
        {
            return _pub.getTopic();
        }

        ros_msgs::RosMsg* getMsgType() override
        {
            return _msg;
        }

    private:
        ros::Publisher _pub;
        ros_msgs::RosMsg* _msg;
        

};