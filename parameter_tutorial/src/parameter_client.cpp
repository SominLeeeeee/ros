#include "ros/ros.h"
#include "parameter_tutorials/SrvTutorial.h"

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "parameter_client");

    if(argc != 3) {
        ROS_INFO("cmd : rosrun service_tutorial service_client arg0 arg1");
        ROS_INFO("arg0 : double number, arg1 : double number");
        return 1;
    }

    ros::NodeHandle nh;

    ros::ServiceClient parameter_client =
        nh.serviceClient<parameter_tutorials::SrvTutorial>("parameter_tutorials");

    parameter_tutorials::SrvTutorial srv;

    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);

    if(parameter_client.call(srv)) {
        ROS_INFO("send srv, srv.Request.a and b : %ld, %ld", static_cast<long int> (srv.request.a),
            static_cast<long int>(srv.request.b));
        ROS_INFO("receive srv, srv.Request.result : %ld", (long int)srv.response.result);
    }

    else {
        ROS_ERROR("Failed to call service parameter_tutorials");
        return 1;
    }

    return 0;
}