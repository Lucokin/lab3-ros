#include "ros/ros.h"
#include <stdlib.h>
#include <lab3/ik.h>
#include <sensor_msgs/JointState.h>
using namespace std;


double deg2rad(double angle){
  return -angle / 180.0 * M_PI;

}


int main(int argc, char**argv){
  ros::init(argc,argv,"ik_client");
  ros::NodeHandle nh;
  ros::ServiceClient client = nh.serviceClient<lab3::ik>("ik_service");
  ros::Publisher jointCmdPublisher = nh.advertise<sensor_msgs::JointState>("joint_states", 1);
  lab3::ik srv;
  ros::Rate loopRate(100);
  srv.request.x = atof(argv[1]);
  srv.request.y = atof(argv[2]);
  srv.request.z = atof(argv[3]);

  if (client.call(srv)){
    ROS_INFO("%s", "Was Called successfully");
    ROS_INFO("J1: %f, J2: %f, J3: %f, J4: %f, J5: %f",srv.response.j1,srv.response.j2,srv.response.j3,srv.response.j4,srv.response.j5);
    std::vector<double> jointCmdValueArray = {deg2rad(srv.response.j1),
                                              deg2rad(srv.response.j2),
                                              deg2rad(srv.response.j3),
                                              deg2rad(srv.response.j4),
                                              deg2rad(srv.response.j5),0};

    ROS_INFO("J1: %f, J2: %f, J3: %f, J4: %f, J5: %f",deg2rad(srv.response.j1),
                                              deg2rad(srv.response.j2),
                                              deg2rad(srv.response.j3),
                                              deg2rad(srv.response.j4),
                                              deg2rad(srv.response.j5));
    std::vector<std::string> jointCmdNameArray = {"m1", "m2", "m3", "m4", "m5", "m6"};
    sensor_msgs::JointState jointCmdMsg;
    jointCmdMsg.header.stamp = ros::Time::now();
    jointCmdMsg.header.seq++;
    jointCmdMsg.position = jointCmdValueArray;
    jointCmdMsg.name = jointCmdNameArray;
    jointCmdPublisher.publish(jointCmdMsg);

  }
  else{
    ROS_ERROR("Failed to call service srv");
    return 1;
  }
  ros::spin();
  loopRate.sleep();
  return 0;
}
