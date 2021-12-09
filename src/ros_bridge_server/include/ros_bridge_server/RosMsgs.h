#pragma once

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Twist.h"

#include "msg_id.h"
#include "SmartBufferPtr.h"

namespace ros_msgs
{
    struct RosMsg
    {   
        virtual ~RosMsg() {}
        virtual size_t getSize() const = 0;
        virtual void serialize(uint8_t* buffer) const = 0;
        virtual void deserialize(SmartBufferPtr bfr) = 0; 
    };

    struct String : RosMsg, public std_msgs::String
    {   
        public:
            String(std::string new_data) : std_msgs::String() 
            {
                data = new_data;
            }
            String() : std_msgs::String() {}
            String(std_msgs::String str) : std_msgs::String(str) {}

            size_t getSize() const override 
            { 
                return data.size() + 1; 
            }
            
            void serialize(uint8_t* buffer) const override 
            { 
                memcpy(buffer, data.c_str(), data.size());
            }
            
            void deserialize(SmartBufferPtr bfr)
            {
                data << bfr;
            }
    };

    struct Pose2D : RosMsg, public geometry_msgs::Pose2D
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
            size_t const _msg_size = 12;
    };

    struct Point2D : RosMsg, public geometry_msgs::Point
    {   
        public:
            Point2D(float new_x, float new_y) : geometry_msgs::Point()
            {
                x = new_x;
                y = new_y;
            }
            Point2D() : geometry_msgs::Point() {}
            Point2D(geometry_msgs::Point point) : geometry_msgs::Point(point) {} 

            size_t getSize() const override 
            { 
                return _msg_size; 
            }

            void serialize(uint8_t* buffer) const override 
            { 
                float* buff = (float*)buffer;
                buff[0] = x;
                buff[1] = y;
            }

            void deserialize(SmartBufferPtr bfr) override
            {
                x << bfr;
                bfr += 4;

                y << bfr;
                bfr += 4;
            }

        private:
            size_t const _msg_size = 8;
    };

    struct Twist2D : RosMsg, public geometry_msgs::Twist
    {
        public:
            Twist2D(float x, float w) : geometry_msgs::Twist()
            {
                linear.x = x;
                angular.z = w;
            }
            Twist2D() : geometry_msgs::Twist() {}
            Twist2D(geometry_msgs::Twist vel_vector) : geometry_msgs::Twist(vel_vector) {}

            size_t getSize() const override 
            { 
                return _msg_size; 
            }

            void serialize(uint8_t* buffer) const override 
            { 
                float* buff = (float*)buffer;
                buff[0] = linear.x;
                buff[1] = angular.z;
            }

            void deserialize(SmartBufferPtr bfr) override
            {
                linear.x << bfr;
                bfr += 4;

                angular.z << bfr;
                bfr += 4;
            }       

        private:
            size_t const _msg_size = 8;
    };


} 