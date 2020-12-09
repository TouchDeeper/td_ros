/*
 * @Description: 
 * @Author: Ren Qian
 * @Date: 2020-02-28 18:50:16
 */
#include <td_ros/sensor_data/pose_data.hpp>
namespace tdros {
Eigen::Quaternionf PoseData::GetQuaternion() {
    Eigen::Quaternionf q;
    q = pose.block<3,3>(0,0);

    return q;
}
}