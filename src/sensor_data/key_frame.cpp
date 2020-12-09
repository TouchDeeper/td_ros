/*
 * @Description: 
 * @Author: Ren Qian
 * @Date: 2020-02-28 19:17:00
 */
#include <td_ros/sensor_data/key_frame.hpp>

namespace tdros {
Eigen::Quaternionf KeyFrame::GetQuaternion() {
    Eigen::Quaternionf q;
    q = pose.block<3,3>(0,0);

    return q;
}
}