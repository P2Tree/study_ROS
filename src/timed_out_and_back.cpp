#include "ros/ros.h"

#include "geometry_msgs/Twist.h"

#define PI 3.1416

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "out_and_back");

    ros::NodeHandle n;

    ros::Publisher twist_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

    int rate = 50;
    ros::Rate loop_rate(rate);

    float linear_speed = 0.2;
    float goal_distance = 1.0;
    float linear_duration = goal_distance / linear_speed;

    float angular_speed = 1.0;
    float goal_angle = PI;
    float angular_duration = goal_angle / angular_speed;

    int i = 2;
    while(ros::ok() && i > 0)
    {
        i--;
        geometry_msgs::Twist msg;

        msg.linear.x = linear_speed;

        int ticks = (int)(linear_duration * rate);

        for ( ; ticks>0; ticks-- ){
            twist_pub.publish(msg);
            loop_rate.sleep();
        }

        msg.linear.x = 0;
        twist_pub.publish(msg);
        sleep(1);

        msg.angular.z = angular_speed;
        ticks = (int)(angular_duration * rate);

        for ( ; ticks>0; ticks-- ){
            twist_pub.publish(msg);
            loop_rate.sleep();
        }

        msg.angular.z = 0;
        twist_pub.publish(msg);
        sleep(1);
    }

    return 0;
}
