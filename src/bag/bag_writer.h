//
// Created by td on 2021/3/8.
//

#ifndef SRC_BAG_WRITER_H
#define SRC_BAG_WRITER_H

#include <ros/ros.h>
#include <rosbag/bag.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/Imu.h>
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
namespace tdros{
    class BagWriter {
    public:
        BagWriter(std::string& path){
            bag_.open(path, rosbag::bagmode::Write);
        }
        ~BagWriter(){
            bag_.close();
        }
        bool WriteImu(std::string& imu_file, std::string topic, double time_offset);
        void WriteFeature(std::string& base_file, std::string topic, double time_offset);
        rosbag::Bag bag_;

    };
}//namespace tdros



#endif //SRC_BAG_WRITER_H
