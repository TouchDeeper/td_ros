/*
 * @Description: odometry 信息发布
 * @Author: Ren Qian
 * @Date: 2020-02-06 21:05:47
 */
#pragma once

#include <string>

#include <Eigen/Dense>
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <gazebo_msgs/ModelState.h>

namespace tdros {
class GazeboPosePublisher {
  public:
    GazeboPosePublisher(ros::NodeHandle& nh,
                      std::string topic_name,
                      int buff_size);
    GazeboPosePublisher() = default;

    void Publish(const Eigen::Matrix4f& transform_matrix, const std::string& model_name);

    bool HasSubscribers();

  private:
    void PublishData(const Eigen::Matrix4f& transform_matrix, const std::string& model_name);

  private:
    ros::NodeHandle nh_;
    ros::Publisher publisher_;
    gazebo_msgs::ModelState model_pose_;
};
}