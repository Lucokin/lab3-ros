#include "ros/ros.h"
#include <stdlib.h>
#include <geometry_msgs/Twist.h>

#include <Kinematics.h>
#include <RotationMatrix.h>
#include <TranslationMatrix.h>
#include <TransformationMatrix.h>
#include "opencv2/opencv.hpp"

#include <lab3/ik.h>

using namespace std;

Kinematics k;


bool mdib(lab3::ik::Request &req, lab3::ik::Response &res){
  cv::Mat kk = cv::Mat::ones(3,1,CV_64F);

  kk.at<float>(0,0) = req.x;
  kk.at<float>(0,1) = req.y;
  kk.at<float>(0,2) = req.z;

  cout << kk.at<float>(2,0) <<endl;
  k.inverseKinematics(kk);
  vector<double> vec;
  vec = k.getQiValues();
  res.j1 = vec.at(0);
  res.j2 = vec.at(1);
  res.j3 = vec.at(2);
  res.j4 = vec.at(3);
  res.j5 = vec.at(4);
  return true;
}

int main(int argc, char**argv){
  ros::init(argc,argv,"ik_server");
  k.loadDHParameters("/home/rohit-linux-pc/catkin_ws/src/lab3/config/poppy_dh.yaml");
  k.loadIKParameters("/home/rohit-linux-pc/catkin_ws/src/lab3/config/poppy_ik.yaml");


  ros::NodeHandle nh;
  ros::ServiceServer service = nh.advertiseService("ik_service", mdib);

  ros::spin();
}
