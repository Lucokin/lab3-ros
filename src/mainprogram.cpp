#include <ros/ros.h>
#include <stdlib.h>                        //all the dependerncies imported
//#include </home/rohit-linux-pc/toolkit-dynamixel/src/DynamixelHandler.h>
#include <geometry_msgs/Twist.h>
#include <vector>
#include <sensor_msgs/JointState.h>

using namespace std;

int main(int argc, char**argv){
	ros::init(argc,argv,"lab3");
	ros::NodeHandle nh;
	ros::Rate loopRate(10);
	ros::Publisher jointCmdPublisher = nh.advertise<sensor_msgs::JointState>("joint_states", 1); // To move the virtual bot
	//ros::Publisher move = nh.advertise<geometry_msgs::Twist>("joint_position",1);           // publisher Object for real robot
  //ros::Subscriber sub_joint = nh.subscribe("joint_cmd",1,joint_call);             // subscriber Object for real robot

	std::vector<double> jointCmdValueArray = {0,0,0,0,0,45};
	std::vector<std::string> jointCmdNameArray = {"m1", "m2", "m3", "m4", "m5", "m6"};
	while(ros::ok()){
		sensor_msgs::JointState jointCmdMsg;
		jointCmdMsg.header.stamp = ros::Time::now();
		jointCmdMsg.header.seq++;
		jointCmdMsg.position = jointCmdValueArray;
		jointCmdMsg.name = jointCmdNameArray;
		jointCmdPublisher.publish(jointCmdMsg);
		ros::spinOnce();
		loopRate.sleep();
	}
	return 0;
}
