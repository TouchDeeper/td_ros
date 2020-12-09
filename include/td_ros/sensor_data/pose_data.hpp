/*
 * @Description: 存放处理后的IMU姿态以及GNSS位置
 * @Author: Ren Qian
 * @Date: 2020-02-27 23:10:56
 */
#pragma once

#include <Eigen/Dense>

namespace tdros {
class PoseData {
  public:
    Eigen::Matrix4f pose = Eigen::Matrix4f::Identity();
    double time = 0.0;

  public:
    Eigen::Quaternionf GetQuaternion();
};
}