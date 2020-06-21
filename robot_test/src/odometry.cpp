#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float32.h>

constexpr double width_robot = 0.15;
constexpr double wheel_radius = 0.05;

double linear_velocity = 0;
double angular_velocity = 0;

constexpr double PI = 3.141592;


void cmd_velCallback(const geometry_msgs::Twist::ConstPtr& twist_aux)
{
	
}

int main(int argc, char** argv) {

	ros::init(argc, argv, "state_publisher");
	ros::NodeHandle n;
	ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("custom_odom", 10);
	ros::Subscriber cmd_vel_sub = n.subscribe("cmd_vel", 10, cmd_velCallback);

	// initial position
	double x = 0.0; 
	double y = 0.0;
	double th = 0.0;

	ros::Time current_time;
	ros::Time last_time;
	current_time = ros::Time::now();

	tf::TransformBroadcaster broadcaster;
	ros::Rate loop_rate(20);

	// message declarations
	geometry_msgs::TransformStamped odom_trans;
	odom_trans.header.frame_id = ;
	odom_trans.child_frame_id = ;

	while (ros::ok()) {
		current_time = ros::Time::now(); 

		/* odometry 계산 */

		geometry_msgs::Quaternion odom_quat;	
		odom_quat = tf::createQuaternionMsgFromRollPitchYaw(0,0,th);

		// update transform
		odom_trans.header.stamp = current_time; 
		odom_trans.transform.translation.x = x; 
		odom_trans.transform.translation.y = y; 
		odom_trans.transform.translation.z = 0.0;
		odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(th);

		//filling the odometry
		nav_msgs::Odometry odom;
		odom.header.stamp = current_time;
		odom.header.frame_id = ;
		odom.child_frame_id = ;

		//position


		//velocity


		// publishing the odometry and the new tf
		broadcaster.sendTransform(odom_trans);
		odom_pub.publish(odom);
		ros::spinOnce();
		loop_rate.sleep();

		last_time = current_time;
	}
	return 0;
}
