#pragma once

#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"

#include "msg_id.h"
#include "SmartBufferPtr.h"

namespace ros_msgs
{

    struct Pose2D : public geometry_msgs::Pose2D
    {   
        public:
            Pose2D(float new_x, float new_y, float new_theta) : geometry_msgs::Pose2D()
            {
                x = new_x;
                y = new_y;
                theta = new_theta;
            }
            Pose2D() : geometry_msgs::Pose2D() {}
            Pose2D(geometry_msgs::Pose2D pose) : geometry_msgs::Pose2D(pose) {} 

            size_t getSize() const  
            { 
                return _msg_size; 
            }

            MSG_ID getMsgType() const 
            {
                return _msg_type;
            }

            void serialize(uint8_t* buffer) const 
            { 
                float* buff = (float*)buffer;
                
                buff[0] = x;
                buff[1] = y;
                buff[2] = theta;
            }

            void deserialize(SmartBufferPtr bfr) 
            {
                x << bfr;
                bfr += 4;

                y << bfr;
                bfr += 4;

                theta << bfr;
            }

        private:
            MSG_ID const _msg_type = GEOMETRY_MSGS_POSE_2D_ID;
            size_t const _msg_size = 12;
    };
} 