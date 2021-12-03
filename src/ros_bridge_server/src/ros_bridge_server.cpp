#include "ros/ros.h"


#include <cstring>

#include "ConnectionHandler.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "ros_bridge_server");

    ros::NodeHandle nh;

    ros::Rate loop_rate(10);

    while(ros::ok())
    {
        ConnectionHandler* new_handle = new ConnectionHandler;

        if(new_handle->wait_for_accept() == -1)
            delete new_handle;

        loop_rate.sleep();
    }

    return 0;
}