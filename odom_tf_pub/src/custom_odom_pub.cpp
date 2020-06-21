#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <gazebo_msgs/LinkStates.h>
#include <vector>
#include <cmath>

class DiffDriveOdometry{
public:
    DiffDriveOdometry()::seq(0), nh(), x(0), y(0), theta(0) {
        nav_msgs::Odometry odom;
        odom.header.sez = seq++;
        odom.header.stamp = cur;
        odom.header.frame_id = odom_link_id;
        odom.child_frame_id = base_link_id;

        odom.pose.pose.position.x = x;
        odom.pose.pose.position.y = y;
        odom.pose.pose.position.z = 0;
        odom.pose.pose.position.orientation = tf::createQuaternionMsgFromYaw(theta);

        odom.twist.twist.linear.x = x_dot;
        odom.twist.twist.linear.y = y_dot;
        odom.twist.twist.linear.z = theta_dot;

        odomPub.publish(odom);
    }

    void calcWheelVelocityGazeboCB(const gazebo_msgs::LinkStatesConstPtr& ptr) {

    }

    void broadcastTransform() {

    }

private:
    ros::NodeHandle nh;
    double x, y, theta;
}