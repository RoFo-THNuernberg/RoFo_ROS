#pragma once

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

#include "msg_id.h"

namespace ros_msgs
{
    struct RosMsg
    {   
        virtual ~RosMsg() {}
        virtual size_t getSize() const = 0;
        virtual void serialize(uint8_t* buffer) const = 0;
        virtual void deserialize(uint8_t* buffer) = 0; 
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
                if(data.empty() == true)
                    return 0; 
                
                return sizeof(int32_t) + data.size() + 1;
            }
            
            void serialize(uint8_t* buffer) const override 
            { 
                if(data.empty() == false)
                {
                    ((int32_t*)buffer)[0] = data.size() + 1;
                    memcpy(buffer + sizeof(int32_t), data.c_str(), data.size());
                    buffer[sizeof(int32_t) + data.size()] = '\0';
                }
            }
            
            void deserialize(uint8_t* buffer)
            {
                data.assign((char*)buffer);
            }
    };

    struct Pose2D : RosMsg, public geometry_msgs::Pose2D
    {   
        public:
            Pose2D(double new_x, double new_y, double new_theta) : geometry_msgs::Pose2D()
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
                double* buff = (double*)buffer;
                
                buff[0] = x;
                buff[1] = y;
                buff[2] = theta;
            }

            void deserialize(uint8_t* buffer) 
            {   
                double* buff = (double*)buffer;

                x = buff[0];
                y = buff[1];
                theta = buff[2];
            }

        private:
            size_t const _msg_size = 24;
    };

    struct Point2D : RosMsg, public geometry_msgs::Point
    {   
        public:
            Point2D(double new_x, double new_y) : geometry_msgs::Point()
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
                double* buff = (double*)buffer;
                buff[0] = x;
                buff[1] = y;
            }

            void deserialize(uint8_t* buffer) override
            {
                double* buff = (double*)buffer;

                x = buff[0];
                y = buff[1];
            }

        private:
            size_t const _msg_size = 16;
    };

    struct Twist2D : RosMsg, public geometry_msgs::Twist
    {
        public:
            Twist2D(double x, double w) : geometry_msgs::Twist()
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
                double* buff = (double*)buffer;
                buff[0] = linear.x;
                buff[1] = angular.z;
            }

            void deserialize(uint8_t* buffer) override
            {
                double* buff = (double*)buffer;

                linear.x = buff[0];
                angular.z = buff[1];
            }       

        private:
            size_t const _msg_size = 16;
    };

    struct Pose2DSim : RosMsg, public turtlesim::Pose
    {
        public:
            Pose2DSim(float new_x, float new_y, float new_theta) : turtlesim::Pose()
            {
                x = new_x;
                y = new_y;
                theta = new_theta;
            }
            Pose2DSim() : turtlesim::Pose() {}
            Pose2DSim(turtlesim::Pose pose) : turtlesim::Pose(pose) {}

            size_t getSize() const override 
            { 
                return _msg_size; 
            }

            void serialize(uint8_t* buffer) const override 
            { 
                float* buff = (float*)buffer;
                buff[0] = x;
                buff[1] = y;
                buff[2] = theta;
            }

            void deserialize(uint8_t* buffer) override
            {
                float* buff = (float*)buffer;

                x = buff[0];
                y = buff[1];
                theta = buff[2];
            }       

        private:
            size_t const _msg_size = 12;
    };
} 