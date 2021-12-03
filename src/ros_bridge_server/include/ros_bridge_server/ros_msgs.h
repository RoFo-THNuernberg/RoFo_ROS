#pragma once

#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"

namespace ros_msgs
{


    class Pose2D : public geometry_msgs::Pose2D
    {   
        public:
            uint8_t* deserialize(uint8_t *buffer);

    };
}