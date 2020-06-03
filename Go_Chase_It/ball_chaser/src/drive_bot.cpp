#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <std_msgs/Float64.h>
#include "ball_chaser/DriveToTarget.h"


ros::Publisher motor_command_publisher;

bool handle_drive_callback(ball_chaser::DriveToTarget::Request& req,
    ball_chaser::DriveToTarget::Response& res)
{  
    
    geometry_msgs::Twist cmd_motor;
    
    cmd_motor.linear.x = req.linear_x;
    cmd_motor.angular.z = req.angular_z;
    
    motor_command_publisher.publish(cmd_motor);

    res.msg_feedback = "Drive to target request set - linear_x: " + std::to_string(req.linear_x) + ", angular_z: " + std::to_string(req.angular_z);
    ROS_INFO_STREAM(res.msg_feedback);
    return true;
}

int main(int argc, char** argv)
{
   
    ros::init(argc, argv, "drive_bot");


    ros::NodeHandle n;

    
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    
    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_callback);
    ROS_INFO("Robot is ready to receive velocitices.");

    
    ros::spin();

    return 0;
}
