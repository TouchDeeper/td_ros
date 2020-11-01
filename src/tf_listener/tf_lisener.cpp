/*
 * @Description: tf监听模块
 * @Author: Ren Qian
 * @Date: 2020-02-06 16:10:31
 */
#include <td_ros/tf_listener/tf_listener.hpp>

#include <Eigen/Geometry>

namespace tdros {
TFListener::TFListener(ros::NodeHandle& nh, std::string base_frame_id, std::string child_frame_id) 
    :nh_(nh), base_frame_id_(base_frame_id), child_frame_id_(child_frame_id) {
    if(!listener_.waitForTransform(base_frame_id_,child_frame_id_,ros::Time(0),ros::Duration(3.0)))
        ROS_INFO("no transformation");
}

bool TFListener::LookupData(Eigen::Matrix4d& transform_matrix) {
    if(!CheckExist())
        return false;
    try {
        tf::StampedTransform transform;
        listener_.lookupTransform(base_frame_id_, child_frame_id_, ros::Time(0), transform);
        TransformToMatrix(transform, transform_matrix);
        return true;
    } catch (tf::TransformException &ex) {
        ROS_INFO("TransformException");
        return false;
    }
}
bool TFListener::CheckExist(){
    if(!listener_.frameExists(base_frame_id_))
    {
        ROS_INFO("can't get the %s",base_frame_id_.c_str());
        return false;
    }
    if(!listener_.frameExists(child_frame_id_))
    {
        ROS_INFO("can't get the %s",child_frame_id_.c_str());
        return false;
    }
    return true;


}
bool TFListener::TransformToMatrix(const tf::StampedTransform& transform, Eigen::Matrix4d& transform_matrix) {
    Eigen::Translation3d tl_btol(transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ());
    
    double roll, pitch, yaw;
    tf::Matrix3x3(transform.getRotation()).getEulerYPR(yaw, pitch, roll);
    Eigen::AngleAxisd rot_x_btol(roll, Eigen::Vector3d::UnitX());
    Eigen::AngleAxisd rot_y_btol(pitch, Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd rot_z_btol(yaw, Eigen::Vector3d::UnitZ());

    // 此矩阵为 child_frame_id 到 base_frame_id 的转换矩阵
    transform_matrix = (tl_btol * rot_z_btol * rot_y_btol * rot_x_btol).matrix();

    return true;
}
}