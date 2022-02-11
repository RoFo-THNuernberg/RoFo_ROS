#include "ros/ros.h"

#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

#include <cstdio>


FILE* file;

void data_log_callback(const std_msgs::String& data_log)
{
    fprintf(file, "%s", data_log.data.c_str());
}


/**
 * @brief The purpose of the data_logger node is to simplify the logging of certain "actions" for example recording a step response... 
 * The user can select the action type, logging time, output file and robot name through the specified parameters.
 * 
 * @note To log the different actions the user must define DATA_LOGGING in the corresponding component in the ESP code
 * and log the action with the macro LOG_DATA().
 */
int main(int argc, char **argv)
{
    ros::init(argc, argv, "data_logger");

    std::string robot_name;
    std::string logging_mode;
    std::string log_time;
    std::string log_file;

    ros::NodeHandle node_handle;
    ros::NodeHandle params_nh("~");
    params_nh.param<std::string>("robot_name", robot_name, "robot_1");
    params_nh.param<std::string>("logging_mode", logging_mode, "vel_step");
    params_nh.param<std::string>("log_time", log_time, "10");
    params_nh.param<std::string>("log_file", log_file, "data.csv");

    ROS_INFO("Start logging of %s in logging mode %s for %s to %s", robot_name.c_str(), logging_mode.c_str(), log_time.c_str(), log_file.c_str());

    file = fopen(log_file.c_str(), "w");

    ros::Subscriber recv_log = node_handle.subscribe("/robot_1/data_log", 10, data_log_callback);
    ros::Publisher start_logging = node_handle.advertise<std_msgs::String>("/robot_1/start_log", 1);
    ros::Publisher action_pub;

    //Wait for some reason doesn't work without!!!
    ros::Rate loop_rate(1);
    loop_rate.sleep();

    //notify robot to start logging 
    std_msgs::String start_logging_msg;
    start_logging_msg.data = log_time;
    start_logging.publish(start_logging_msg);

    //start action
    if(logging_mode == "vel_step")
    {
        action_pub = node_handle.advertise<geometry_msgs::Twist>(robot_name + "/vel", 1);

        geometry_msgs::Twist velocity_step;
        velocity_step.linear.x = 2;
        action_pub.publish(velocity_step);
    }
    else if(logging_mode == "marvelmind_cov")
    {

    }

    //program needs time to execute callbacks from received log packets
    loop_rate = 40;
    ros::Time start_time = ros::Time::now();
    while(ros::ok() && (ros::Time::now() - start_time).toSec() < 2 + stoi(log_time))
    {
        ros::spinOnce();
        loop_rate.sleep();
    }

    //terminate action
    if(logging_mode == "vel_step")
    {
        geometry_msgs::Twist velocity_step;
        velocity_step.linear.x = 0;
        action_pub.publish(velocity_step);
    }
    else if(logging_mode == "marvelmind_cov")
    {

    }

    fclose(file);
    
    return 0;
}
