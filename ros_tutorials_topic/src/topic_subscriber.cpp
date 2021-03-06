#include <ros/ros.h>    
#include "ros_tutorials_topic/MsgTutorial.h"

void msgCallback(const ros_tutorials_topic::MsgTutorial::ConstPtr& msg) {
    ROS_INFO("recieve msg = %d", msg->stamp.sec);
    ROS_INFO("recieve msg = %d", msg->stamp.nsec);
    ROS_INFO("recieve msg = %d", msg->data);
} 

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "topic_subscriber");   
    ros::NodeHandle nh; 
    ros::Subscriber sub=nh.subscribe("ros_tutorial_msg", 1000, &msgCallback);
    ros::spin();

    return 0;
}
