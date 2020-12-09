/*
 * @Description: 里程计信息发布
 * @Author: Ren Qian
 * @Date: 2020-02-06 21:11:44
 */
#include <td_ros/publisher/gazebo_pose_publisher.hpp>
#include <td_ros/tool.h>

namespace tdros {
GazeboPosePublisher::GazeboPosePublisher(ros::NodeHandle& nh,
                                     std::string topic_name,
                                     int buff_size)
    :nh_(nh) {

    publisher_ = nh_.advertise<gazebo_msgs::ModelState>(topic_name, buff_size);
}

void GazeboPosePublisher::Publish(const Eigen::Matrix4f& transform_matrix, const std::string& model_name) {
    SetPosition(publisher_,model_name,transform_matrix,60,80);
}


//void GazeboPosePublisher::PublishData(const Eigen::Matrix4f& transform_matrix, const std::string& model_name) {
//    model_pose_.model_name = model_name;
//    //set the position
//    model_pose_.pose.position.x = transform_matrix(0,3);
//    model_pose_.pose.position.y = transform_matrix(1,3);
//    model_pose_.pose.position.z = transform_matrix(2,3);
//
//    Eigen::Quaternionf q;
//    q = transform_matrix.block<3,3>(0,0);
//    model_pose_.pose.orientation.x = q.x();
//    model_pose_.pose.orientation.y = q.y();
//    model_pose_.pose.orientation.z = q.z();
//    model_pose_.pose.orientation.w = q.w();
//
//    publisher_.publish(model_pose_);
//}

bool GazeboPosePublisher::HasSubscribers() {
    return publisher_.getNumSubscribers() != 0;
}
}