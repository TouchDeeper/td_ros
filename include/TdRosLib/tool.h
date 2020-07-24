#pragma once
#include "ros/ros.h"
#include "gazebo_msgs/ModelState.h"
#include "gazebo_msgs/ModelStates.h"
#include "gazebo_msgs/SpawnModel.h"
#include <fstream>

#include <std_srvs/Empty.h>

#include <Eigen/Core>
#include <sophus/se3.hpp>
namespace tdros{
    void SetPosition(ros::Publisher &chatter_pub, std::string model_name, Sophus::SE3d w_T_object, int loop_rate_ );
// pause the gazebo
    void PauseGazebo(ros::NodeHandle &n);
}
