#include <ros/ros.h>
#include "ros_tutorials_topic/MsgTutorial.h" 

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "topic_publisher");    
    ros::NodeHandle nh; 
    ros::Publisher ros_tutorial_pub = 
        nh.advertise<ros_tutorials_topic::MsgTutorial>("ros_tutorial_msg", 1000); 
    ros::Rate loop_rate(10); 
    
    int count = 0;

    while(ros::ok()) { 
        ros_tutorials_topic::MsgTutorial msg;

        msg.stamp = ros::Time::now();
        msg.data = count;

        ROS_INFO("send msg = %d", msg.stamp.sec);
        ROS_INFO("send msg = %d", msg.stamp.nsec);
        ROS_INFO("send msg = %d", msg.data);

        ros_tutorial_pub.publish(msg); 
        loop_rate.sleep();
        count++;
    }

    return 0;
}
