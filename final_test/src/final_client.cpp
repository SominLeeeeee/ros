#include<ros/ros.h>
#include<cstdlib>
#include "final_test/final_srv.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "service_client");

    if(argc != 4){
        ROS_INFO("cmd : rosrun final_test final_client arg0 arg1 arg2");
        ROS_INFO("arg0 : theta1, arg1 : theta2, arg2 : scalar");

        return 1;
    }

    ros::NodeHandle nh;

    ros::ServiceClient service_client =
        nh.serviceClient<final_test::final_srv>("final_service");

    final_test::final_srv srv;
    srv.request.theta1 = atoll(argv[1]);
    srv.request.theta2 = atoll(argv[2]);
    srv.request.scalar = atoll(argv[3]);

    if(service_client.call(srv)) {
        ROS_INFO("send srv, theta1 : %f, theta2 : %f, scalar : %f", srv.request.theta1, srv.request.theta2, srv.request.scalar);
        ROS_INFO("receive srv, result : %f", srv.response.result);
    }

    else {
        ROS_ERROR("Failed to call service final_service");
        return 1;
    }
    
    return 0;
}
