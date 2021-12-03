#pragma once

#include "Socket.h" 

#include <thread>
#include <string>
#include <vector>

#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include "ros_msgs.h"

#define RX_BUFFER_LEN 1024


class ConnectionHandler
{
    public:
        ConnectionHandler();
        ~ConnectionHandler();
        int wait_for_accept();
        
        static void handler_function(ConnectionHandler *conn_handle);

    private:
        int _receive_new_msg();
        ros::Publisher* _getPublisher(const std::string& topic);
        void _unadvertise();
        void _advertise(std::string const& topic, std::string const& message_type);

        Socket _sock;
        ros::NodeHandle *_node_handle = nullptr;
        std::string _namespace;

        std::vector<ros::Publisher*> _publisher;
};