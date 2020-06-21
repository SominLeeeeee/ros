#include<ros/ros.h>
#include<iostream>
#include<eigen3/Eigen/Dense>
#include<vector>
#include<sensor_msgs/JointState.h>

#define N_JOINT 6

static constexpr double a_dh[N_JOINT] = {0.00000, -0.42500, -0.39225, 0.00000, 0.00000, 0.00000};
static constexpr double d_dh[N_JOINT] = {0.089159, 0.00000, 0.00000, 0.10915, 0.09456, 0.0823};
static constexpr double alpha_dh[N_JOINT] = {1.570796327, 0, 0, 1.570796327, -1.570796327, 0};

using namespace std;
using namespace Eigen;

Matrix4d RotZ(double rad) { // 4*4 행렬 double
    Matrix4d m;
    m <<    cos(rad), -sin(rad), 0, 0,
            sin(rad), cos(rad), 0, 0,
            0,0,1,0,
            0,0,0,1;
    return m;
}   // 롯

Matrix4d TransZ(double d) {
    Matrix4d m2;
    m2 <<   1,0,0,0,
            0,1,0,0,
            0,0,1,d,
            0,0,0,1;
    return m2;
}   // 트

Matrix4d TransX(double a) {
    Matrix4d m2;
    m2 <<   1,0,0,a,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1;
    return m2;
}   // 트

Matrix4d RotX(double rad) {
    Matrix4d m;
    m <<    1,0,0,0,
            0,cos(rad),-sin(rad),0,
            0,sin(rad),cos(rad),0,
            0,0,0,1;
    return m;
}   // 롯

class UR5{
public:
    UR5() {
        sub = nh.subscribe("/joint_states", 100, &UR5::ur5CallBack, this);
    }

    void ur5CallBack(const sensor_msgs::JointState::ConstPtr& ptr) {
        result << 1,0,0,0,
                  0,1,0,0,
                  0,0,1,0,
                  0,0,0,1;

        for(int i = 0; i < N_JOINT; i++) {
            result *= RotZ(ptr->position[i]) * TransZ(d_dh[i]) * TransX(a_dh[i]) * RotX(alpha_dh[i]);
        }

    }

    void printResult() {
        cout << "result tf matrix - " << endl;
        cout << result << endl;
    }

private:
    ros::NodeHandle nh;
    ros::Subscriber sub;

    Matrix4d result;
};

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "fk_main");
    UR5 ur;
    ros::Rate loop_rate(100);

    while(ros::ok()){
        ros::spinOnce();
        ur.printResult();
        loop_rate.sleep();
    }

    return 0;
}
