#include <ros/ros.h>
#include <math.h>
#include "robot_localization/pose_msg.h"

#define PI2 3.14*2
#define INC PI2/360.0
#define RADIUS 1.0

using namespace std;

class RobotPose{
public:
    RobotPose() {
        theta = 0;
        msg.x = cos(theta);
        msg.y = sin(theta);

        pub = nh.advertise<robot_localization::pose_msg>("robotPose", 10);
    }

    void genMsg() {
        theta += INC;
        msg.stamp = ros::Time();
        msg.x = cos(theta);
        msg.y = sin(theta);
    }

    void publish() {
        pub.publish(msg);
    }

private:
    ros::NodeHandle nh;
    ros::Publisher pub;
    robot_localization::pose_msg msg;
    double theta;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "robot_pose");
    RobotPose ms;

    ros::Rate loop_rate(10);
    while(ros::ok()) {
        ros::spinOnce();
        ms.genMsg();
        ms.publish();
        loop_rate.sleep();
    }

    return 0;

}