#include <ros/ros.h>
#include <cstdlib>
#include "multiple_topic_pkg/my_topic_one.h"
#include "multiple_topic_pkg/my_topic_two.h"

class MultipleSubscriber{
public:
    MultipleSubscriber()
    : data1(0)
    , data2(0.0)
    , calc_option(1)
    , total_data(0.0)
    {
        data_sub1 = nh.subscribe("data_one_topic", 100, &MultipleSubscriber::save_data_one, this);
        data_sub2 = nh.subscribe("data_two_topic", 100, &MultipleSubscriber::save_data_two, this);
        calc_sub  = nh.subscribe("my_calc_option_topic", 100, &MultipleSubscriber::save_calc_data, this);
        total_pub = nh.advertise<multiple_topic_pkg::my_topic_two>("total_topic", 100);
    }

    void save_data_one(const multiple_topic_pkg::my_topic_one::ConstPtr& msg) {
        ROS_INFO("received DATA ONE : %d", msg->data);
        data1 = msg->data;
    }

    void save_data_two(const multiple_topic_pkg::my_topic_two::ConstPtr& msg) {
        ROS_INFO("received DATA TWO : %f", msg->data);
        data2 = msg->data;
    }

    void save_calc_data(const multiple_topic_pkg::my_topic_one::ConstPtr& msg) {
        if(msg->data == 1) 
            ROS_INFO("calc option : -"); 
        else if(msg->data == 2) 
            ROS_INFO("calc option : +"); 
        else if(msg->data == 3) 
            ROS_INFO("calc option : x"); 
        else if(msg->data == 4) 
            ROS_INFO("calc option : /");

        calc_option = msg->data; 
    }

    void total_publish() {
        multiple_topic_pkg::my_topic_two total_msg;

        if(calc_option == 1) 
            total_data = data1 - data2;
        else if(calc_option == 2) 
            total_data = data1 + data2;
        else if(calc_option == 3) 
            total_data = data1 * data2;
        else if(calc_option == 4) 
            total_data = data1 / data2;

        total_msg.data = total_data;
        total_pub.publish(total_msg);
        ROS_INFO("total data is %f", total_data);
    }

private:
    ros::NodeHandle nh;
    ros::Subscriber data_sub1;
    ros::Subscriber data_sub2;
    ros::Subscriber calc_sub;

    ros::Publisher total_pub;

    int data1, calc_option;
    double data2, total_data;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "multiple_sub");
    MultipleSubscriber MS;

    ros::Rate loop_rate(10);

    while(ros::ok()) {
        loop_rate.sleep();
        ros::spinOnce();    
        // spin()과의 차이 : spin은 폴링, subscriber 모두 켜져서 콜백함수 기다림
        // spinOnce()는 한번만 spin 하는데 보통 반복문 안에 넣는다
        // subscriber를 할때 필요한 부가적인것들 같이 실행해줌
        // 우리는 퍼블리쉬를 같이 해줘야 하기 떄문에 spinOnce를 사용한다
        MS.total_publish();
    }    

    return 0;  
}