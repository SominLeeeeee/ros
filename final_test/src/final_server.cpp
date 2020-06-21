#include<ros/ros.h>
#include "final_test/final_srv.h"
#include <cmath>
using namespace std;

#define PLUS 1
#define MINUS 2
#define MULTIPLICATION 3
#define DIVISION 4

constexpr double PI = 3.141592;

class FinalServerTest{
public:
    int param;
    float rad1, rad2;
    FinalServerTest(string n, string pN) {
        serviceName = n;
        paramName = pN;
        nh.setParam(paramName.c_str(), 1);
        paramServer = nh.advertiseService(serviceName.c_str(), &FinalServerTest::calculation, this);
    }

    ~FinalServerTest(){}


    bool calculation(final_test::final_srv::Request &req,
                    final_test::final_srv::Response &res){
        nh.getParam(paramName.c_str(),param);

        rad1 = (req.theta1 / 180) * PI;
        rad2 = (req.theta2 / 180) * PI;
        switch(param) {
            case PLUS:
                res.result = req.scalar * ( sin(rad1) + cos(rad2) );
                break;
            case MINUS:
                res.result = req.scalar * (sin(rad1) - cos(rad2));
                break;
            case MULTIPLICATION:
                res.result = req.scalar * (sin(rad1) * cos(rad2));
                break;            
            case DIVISION:
                res.result = req.scalar * (sin(rad1) / cos(rad2));
                break;            
            default:
                ROS_WARN("UNKNOWN OPERATOR TYPE. It must be 1, 2, 3, 4. The value of operator is %d", param);
                break;
        }

        ROS_INFO("recived : sin(theta1) = %f", sin(rad1));
        ROS_INFO("recived : cos(theta2) = %f", cos(rad2));
        ROS_INFO("recived : scalar      = %f", req.scalar);
        ROS_INFO("sending back Response: [%f]", res.result);
        
        return true;
    }

private:
    string serviceName;             // 서비스 이름
    string paramName;               // 파라미터 이름
    ros::NodeHandle nh;             // 노드 핸들
    ros::ServiceServer paramServer; // 서버
};

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"final_server");
    ros::NodeHandle nh;

    FinalServerTest server("final_service", "final_param");

    ros::spin();
    return 0;
}
