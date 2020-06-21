#include<ros/ros.h>
#include<nav_msgs/Odometry.h>
#include<tf/transform_broadcaster.h>
#include<string>
#include<cmath>
#include<gazebo_msgs/LinkStates.h>
#include<geometry_msgs/Twist.h>
#include<vector>
#include<iostream>

#define radi 3.14159265359 / 180

using namespace std;

class DiffDriveOdometry{
public:
    DiffDriveOdometry()
	: seq(0)
	, x(0.0)
	, y(0.0)
	, theta(0.0)
    {
        sub = nh.subscribe("/gazebo/link_states", 100, &DiffDriveOdometry::calcWheelVelocityGazeboCB, this);
        odomPub = nh.advertise<nav_msgs::Odometry>("/custom_odom",100);

        if(!nh.getParam("mobile_robot_odometry/base_link_id", base_link_id)) throw std::runtime_error("set base_link_id");
        if(!nh.getParam("mobile_robot_odometry/odom_link_id", odom_link_id)) throw std::runtime_error("set odom_link_id");
        if(!nh.getParam("mobile_robot_odometry/leftwheel_linkname", wheel_1_id)) throw std::runtime_error("set wheel_1_id");
        if(!nh.getParam("mobile_robot_odometry/rightwheel_linkname", wheel_3_id)) throw std::runtime_error("set wheel_3_id");
        if(!nh.getParam("mobile_robot_odometry/separation_length", separation_length)) throw std::runtime_error("set separation_length");
    }

    void calcWheelVelocityGazeboCB(const gazebo_msgs::LinkStates::ConstPtr& ptr){
        // 속도 계산 (v 를 구한다)
        int left_num,right_num;
		for(int i = 0; i <12; ++i){
            if(ptr->name[i] == wheel_1_id) {left_num = i;} 
            else if(ptr->name[i] == wheel_3_id) {right_num = i;}
        }
    /*
        sz = ptr->name.size();
        left_twist = ptr->twist[left_num];
        right_twist = ptr->twist[right_num];
*/
        left_vel = sqrt(pow(ptr->twist[left_num].linear.x, 2)+pow(ptr->twist[left_num].linear.y, 2)+pow(ptr->twist[left_num].linear.z, 2)); 
        right_vel = sqrt(pow(ptr->twist[right_num].linear.x, 2)+pow(ptr->twist[right_num].linear.y, 2)+pow(ptr->twist[right_num].linear.z, 2)); 
        base_vel = (left_vel + right_vel) / 2;
/*
        base.name.resize(sz);
        base.pose.resize(sz);
        base.twist.resize(sz);

        for(int i = 0; i < sz; i++) {
            base.name[i] = ptr->name[i];
            base.pose[i] = ptr->pose[i];
            base.twist[i] = ptr->twist[i];
            base.pose[i].position.x += 0.1;
        }
        */
    }

    void boradcastTransform(){

        tf::Transform transform;
        transform.setOrigin(tf::Vector3(x,y,0.0));
        tf::Quaternion q;
        q.setRPY(0, 0, theta);
        transform.setRotation(q);

        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), odom_link_id, base_link_id)); // linking base_link
    }

    void pubTF(){
        nav_msgs::Odometry odom;

	/*
		odometry 계산. x, y, theta, x dot, y dot, theta dot
	*/

        // 각속도 구하기
        // theta_dot = omega
        // w = R/L(vr - vl)
        theta_dot = (right_vel - left_vel) / separation_length;

        // theta 계산하기
        theta += theta_dot * 0.01;
        // theta_dot * dt를 계속해서 더해준다

        // x_dot, y_dot 계산하기
        x_dot = base_vel * cos(theta);
        y_dot = base_vel * sin(theta);

        // x, y 계산하기
        x += x_dot * 0.01;
        y += y_dot * 0.01;
        // 0.01은 dt

        // custom_odom 값 채우기
        odom.header.seq             = seq++;
        odom.header.stamp           = ros::Time::now();
        odom.header.frame_id        = odom_link_id;
        odom.child_frame_id         = base_link_id;

        odom.pose.pose.position.x   = x;    // x_dot을 dt마다 누적한 결과
        odom.pose.pose.position.y   = y;    // y_dot을 dt마다 누적한 결과
        odom.pose.pose.position.z   = 0;    // 2차원이기 때문에 z는 계산하지 않는다
        odom.pose.pose.orientation  = tf::createQuaternionMsgFromYaw(theta);
        // theta -> quaternion, 오리엔테이션 변수 다 채워준다

        odom.twist.twist.linear.x   = x_dot; // x축 속력정보
        odom.twist.twist.linear.y   = y_dot;
        odom.twist.twist.angular.z  = theta_dot;    // z축 회전이기 때문에 angluar z가 theta_dot
        // twist는 속력정보

        odomPub.publish(odom);      // 최종적으로 발행

        boradcastTransform();
    }
/*
    void debug() {
        ROS_INFO("-----------------------");
        ROS_INFO("x_dot     = %f", x_dot);
        ROS_INFO("y_dot     = %f", y_dot);
        ROS_INFO("x         = %f", x);
        ROS_INFO("y         = %f", y);
        ROS_INFO("theta_dot = %f", theta_dot);
        ROS_INFO("theta     = %f", theta);

    }
*/
private:
    ros::NodeHandle nh;
    ros::Subscriber sub;
    ros::Publisher  odomPub;

    string base_link_id, odom_link_id, wheel_1_id, wheel_3_id;
    double separation_length;       // L = 0.3
    double x_dot, y_dot, theta_dot;
    double x, y, theta;
    double left_vel, right_vel, base_vel; // vl, vr, v
    int seq;
    tf::TransformBroadcaster br;
};

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "mobile_robot_odometry");
    DiffDriveOdometry Odom;
    ros::Rate loop_rate(100); // dt is always 0.01s

    while(ros::ok()){
        ros::spinOnce();
        Odom.pubTF();
        loop_rate.sleep();
    }
    return 0;
}
