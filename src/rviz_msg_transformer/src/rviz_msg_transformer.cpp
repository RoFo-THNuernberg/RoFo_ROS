#include "ros/ros.h"

#include <functional>

#include "geometry_msgs/Point.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/PoseStamped.h"

#include <tf/transform_broadcaster.h>

class MsgTransformer : public ros::NodeHandle
{
    public:
        MsgTransformer()
        {
            _goal_point_transformer = subscribe("/move_base_simple/goal", 1, &MsgTransformer::_goal_point_transformer_callback, this);
            _actual_pose_transformer = subscribe("/robot_1/pose2D", 1, &MsgTransformer::_actual_pose_transformer_callback, this);

            _goal_point_pub = advertise<geometry_msgs::Point>("robot_1/goal_point", 1);
        }

    private:
        void _goal_point_transformer_callback(const geometry_msgs::PoseStamped& pose)
        {
            ROS_INFO("_goal_point_callback");

            geometry_msgs::Point point;

            point.x = pose.pose.position.x;
            point.y = pose.pose.position.y;


            _goal_point_pub.publish(point);
        }

        void _actual_pose_transformer_callback(const geometry_msgs::Pose2D& pose)
        {
            ROS_INFO("_actual_pose_callback");

            tf::Transform pose_tf;

            pose_tf.setOrigin(tf::Vector3(pose.x, pose.y, 0));

            tf::Quaternion q;
            q.setRPY(0, 0, pose.theta);
            pose_tf.setRotation(q);

            _actual_pose_pub.sendTransform(tf::StampedTransform(pose_tf, ros::Time::now(), "marvelmind", "robot_1"));
        }

        ros::Subscriber _goal_point_transformer;
        ros::Subscriber _actual_pose_transformer;

        ros::Publisher _goal_point_pub;

        tf::TransformBroadcaster _actual_pose_pub;

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "rviz_msg_transformer");

    ROS_INFO("Starting rviz_msg_tranformer!");

    MsgTransformer transformer;

    ros::spin();
    
    return 0;
}
