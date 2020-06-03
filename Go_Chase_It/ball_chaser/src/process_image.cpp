#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>


ros::ServiceClient client;


void drive_robot(float lin_x, float ang_z)
{
    
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    
    if (!client.call(srv)) {
        ROS_ERROR("Call service failed.");
    }
}


void process_image_callback(const sensor_msgs::Image img)
{

 
    int wh_pix_s = -1;
    float line_x = 0;
    float angl_z = 0;
    bool ball_found = false;

    for (int i = 0; i < img.height * img.step; i += 3) {
	if (img.data[i] == 255 && img.data[i + 1] == 255 && img.data[i + 2] == 255) {
	    ball_found = true;
	    wh_pix_s = i % img.step;
		if (wh_pix_s < img.step / 3 ) { 
		line_x = 0.0;
    		angl_z = 0.5;
  		}
		
		else if (wh_pix_s > img.step * 2 / 3) {
		line_x = 0.0;
		angl_z = -0.5;
		} 

		else {
		line_x = 0.5;
		angl_z = 0.0;
		}


	    break;
	    }
	}
	
	
	
             
   
	        
    drive_robot(line_x, angl_z);
}

int main(int argc, char** argv)
{
    
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    
    ros::spin();

    return 0;
}
