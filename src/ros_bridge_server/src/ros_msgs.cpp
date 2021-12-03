#include "ros_msgs.h"

namespace ros_msgs
{


    uint8_t* Pose2D::deserialize(uint8_t* buffer)
    {
        x = *((float*)buffer);
        y = *((float*)(buffer + 4));
        theta = *((float*)(buffer + 8));

        return buffer + 12;
    }
}