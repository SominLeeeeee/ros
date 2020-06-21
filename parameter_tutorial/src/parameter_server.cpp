#include "ros/ros.h"
#include "parameter_tutorials/SrvTutorial.h"
using namespace std;

enum {PLUS = 1, MINUS, MULTIPLICATION, DIVISION};

/*

1. 입출력은 기존과 같다
2. g_operator 없애기
3. main의 loop문 삭제하고 ros::spin() 호출하기
4. 새로운 class SimpleCalculator를 정의
5. 적절한 메소드를 정해 기존 서버의 역할 수행하도록 하기
6. 콜백 함수가 호출될때마다 calculation_method 파라미터값 읽어 서버 동작 수행

*/

class SimpleCalculator{
public:
    // 생성자, 변수들 초기화
    SimpleCalculator(string n, string pN) {
        serviceName = n;        // n이 서비스 이름
        paramName = pN;         // pN이 파라미터 이름
        this->setParameter();   // 파라미터 설정하기
        paramServer = nh.advertiseService(serviceName.c_str(), &SimpleCalculator::calculation, this);   // calculation이 콜백 함수
    }

    // 파라미터 설정하는 함수
    void setParameter() {
        nh.setParam(paramName.c_str(), 1);
        // 일단 1로 설정해두기
    }

    // 계산하는 함수
    bool calculation(parameter_tutorials::SrvTutorial::Request &req,
    parameter_tutorials::SrvTutorial::Response &res) {
        nh.getParam(paramName.c_str(), parameter);
        // 일단 파라미터 값이 뭔지 알아낸다
        switch(parameter) {
            case PLUS:
                res.result = req.a + req.b; break;
            case MINUS:
                res.result = req.a - req.b; break;
            case MULTIPLICATION:
                res.result = req.a * req.b; break;
            case DIVISION:
                res.result = (req.b == 0) ? 0 : req.a / req.b; break;
            default:
                ROS_WARN("UNKNOWN OPERATOR TYPE. It must be 1, 2, 3, 4. The value of operator is %d", parameter);
                break;
        }

        ROS_INFO("request : x = %ld, y = %ld", static_cast<long int>(req.a), static_cast<long int>(req.b));
        ROS_INFO("sending back response : %ld", static_cast<long int>(res.result));

        return true;
    }

private:
    int parameter;                  // parameter 숫자로 나타낼 변수
    string serviceName;             // 서비스 이름
    string paramName;               // 파라미터 이름
    ros::NodeHandle nh;             // 노드 핸들
    ros::ServiceServer paramServer; // 서버
};

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "parameter_server");            
    SimpleCalculator server("parameter_tutorials", "calculation_method");   // calculation method가 파라미터, param~가 서비스 이름
    ros::spin();    // 무한반복 (서버는 죽으면 안되니까)

    return 0;
}