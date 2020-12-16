#pragma once
#include "ros/ros.h"
#include "gazebo_msgs/ModelState.h"
#include "gazebo_msgs/ModelStates.h"
#include "gazebo_msgs/SpawnModel.h"
#include <fstream>

#include <std_srvs/Empty.h>

#include <Eigen/Core>
#include "sophus/se3.hpp"
namespace tdros{
    /**
     * set position of model
     * @param chatter_pub the gazebo_msgs::ModelState publisher
     * @param model_name
     * @param w_T_object the pose of object in world
     * @param loop_rate_
     * @param count_sum the publish count
     */
    void SetPosition(const ros::Publisher &chatter_pub, const std::string& model_name, const Sophus::SE3d& w_T_object, int loop_rate_, int count_sum );
    void SetPosition(const ros::Publisher &chatter_pub, const std::string& model_name, const Eigen::Matrix4f& transform_matrix, int loop_rate_, int count_sum );
// pause the gazebo
    void PauseGazebo(ros::NodeHandle &n);
    void SpawnModel(ros::NodeHandle& nh, const std::string& path, const std::string& model_name);
}
