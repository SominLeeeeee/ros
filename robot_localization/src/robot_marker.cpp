#include <ros/ros.h>
#include "robot_localization/pose_msg.h"
#include <visualization_msgs/Marker.h>

class RobotMarker{
public:
    RobotMarker() {
        robot_pose = nh.subscribe("robotPose", 10,
            &RobotMarker::markerInfoCB, this);
        rviz_pub = nh.advertise<visualization_msgs::Marker>("marker", 10);
    }

    void markerInfoCB(const robot_localization::pose_msg::ConstPtr& ptr) {
        stamp = ptr->stamp;
        x = ptr->x;
        y = ptr->y;
    }

    void genMsg() {
        marker.header.frame_id = "base_link";
        marker.header.stamp = stamp;

        marker.ns = "young";
        marker.id = 0;
        marker.action = visualization_msgs::Marker::ADD;

        marker.pose.position.x = x;
        marker.pose.position.y = y;
        marker.pose.position.z = 0.0;

        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;

        marker.scale.x = 0.1;
        marker.scale.y = 0.1;
        marker.scale.z = 0.1;

        marker.color.a = 1.0;
        marker.color.r = 1.0;
        marker.color.g = 0.0;
        marker.color.b = 0.0;

        marker.type = visualization_msgs::Marker::SPHERE;
    }

    void publish() {
        rviz_pub.publish(marker);
    }

private:
    ros::NodeHandle nh;
    ros::Subscriber robot_pose;
    ros::Publisher rviz_pub;

    ros::Time stamp;
    double x, y;
    visualization_msgs::Marker marker;
};

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "robot_marker");
    RobotMarker mp;

    ros::Rate loop_rate(10);
    while(ros::ok()) {
        ros::spinOnce();
        mp.genMsg();
        mp.publish();
        loop_rate.sleep();
    }
    return 0;
}
