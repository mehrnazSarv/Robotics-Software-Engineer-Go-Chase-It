# Go Chase It Project  
This is the 2nd project in the Robotics Software Engineer Nanodegree Program by Udacity.
  
## Project Description  
In this project, I created two ROS packages inside my `catkin_ws/src`:  
1. `my_robot`:  
holds a robot designed with the Unified Robot Description Format, a white-colored ball, and a gazebo world.  
2. `ball_chaser`:  
contains two C++ ROS nodes (`drive_bot` & `process_image`) to interact with the robot and make it chase the white ball.  
    - `drive_bot`:  
    provides a `ball_chaser/command_robot` service to drive the robot by controlling its linear x and angular z velocities.  
    The service publishes to the wheel joints and return back the requested velocities.  
    - `process_image`  
    reads my robot’s camera image, analyzes it to determine the presence and position of a white ball.  
    If a white ball exists in the image, my node requests a service via a client to drive the robot towards it.  
 
## Step to test `process_image`
### Step 1 Launch the robot inside the world 
```sh
$ cd (your workspace)/catkin_ws/  
$ source devel/setup.bash  
$ roslaunch my_robot world.launch
```
### Step 2 Run `drive_bot` and `process_image.cpp`  
```sh
$ cd (your workspace)/catkin_ws/  
$ source devel/setup.bash  
$ roslaunch ball_chaser ball_chaser.launch
```
Now place the white ball at different positions in front of the robot and see if the robot is capable of chasing the ball.

 

