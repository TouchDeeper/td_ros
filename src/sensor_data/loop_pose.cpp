/*
 * @Description: 
 * @Author: Ren Qian
 * @Date: 2020-02-28 19:17:00
 */
#include <td_ros/sensor_data/loop_pose.hpp>

namespace tdros {
Eigen::Quaternionf LoopPose::GetQuaternion() {
    Eigen::Quaternionf q;
    q = pose.block<3,3>(0,0);

    return q;
}
}