#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

constexpr static double PI = 3.14159265359; // static보다 좋다 ! 컴파일타임에 계산해버림, 런타임에 실행되는것 최대한 줄인다
constexpr static double angular_velocity = 2 * PI / 2;  // 각속도 2초에 한바퀴 도는 것(2PI가 360도)

class CircleTF {
public:
    CircleTF() : cur_theta(0), last(ros::Time::now()) {}    // 생성 하자마자 현재가 last (생성했을 때 시간)
    
    void pubTF() {
        ros::Time cur = ros::Time::now();   // cur는 현재
        double dt = (cur - last).toSec();   // 적분을 하기 위해 필요한 dt

        cur_theta += angular_velocity * dt; // dt를 이용해서 적분한다 
        // 각속도*시간 = 각도가 나온다
        // 각속도*dt = 그 짧은 시간동안 움직인 각도가 나오니까
        // cur_theta는 각도를 전부 다 더하는 것이다(적분하는 것이다)
        last = cur; // 그 다음 루프문에서 dt를 위해서

        double x = cos(cur_theta);  // x 길이는 세타의 코사인 값 (파이로 구성된 각도(라디안)로 넣어야함)
        double y = sin(cur_theta);  // y 길이는 세타의 사인 값
        // 반지름을 정해주지 않았기 때문에 1m가 반지름이 된다
        double yaw = cur_theta;     // z축 회전각도 : 세타

        tf::Transform transform;    // 그냥 외우면 된다
        transform.setOrigin(tf::Vector3(x,y,0.0));  // x y yaw값을 인자로 주면된다
        tf::Quaternion q;           // 짐볼락 현상을 막아야 한다
        q.setRPY(0, 0, yaw);        // 롤피치요를 쿼터니언 형식으로 바꿔줘야 한다
        transform.setRotation(q);   // 얼만큼 돌릴거냐? q만큼 돌릴 거다

        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_link", "child_link"));
        // 퍼블리쉬 할 객체, 시스템 타임, 베이스 링크, 차일드 링크(frame_id)를 넣어서 퍼블리쉬 한다
    }

private:
    double cur_theta;
    ros::Time last;
    tf::TransformBroadcaster br;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "tf_practice");
    ros::NodeHandle nh;

    CircleTF c;
    ros::Rate r(50);    // 50헤르츠
    while(ros::ok()) {
        c.pubTF();
        r.sleep();
    }
    return 0;
}