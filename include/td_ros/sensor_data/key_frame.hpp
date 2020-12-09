/*
 * @Description: 关键帧，在各个模块之间传递数据
 * @Author: Ren Qian
 * @Date: 2020-02-28 19:13:26
 */
#pragma once

#include <Eigen/Dense>

namespace tdros {
class KeyFrame {
  public:
    double time = 0.0;
    unsigned int index = 0;
    Eigen::Matrix4f pose = Eigen::Matrix4f::Identity();

  public:
    Eigen::Quaternionf GetQuaternion();
};
}
