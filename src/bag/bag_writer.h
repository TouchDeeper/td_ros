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
        /**
         * convert a txt imu file to bag
         * @param imu_file the txt path, each line: timestamp(sec),q.w(),q.x(),q.y(),q.z(),t(0),t(1),t(2),Gyr.x(),Gyr.y(),Gyr.z(),Acc.x(),vAcc.y(),vAcc.z().  the q and t are the orientation and translation from body to world, they are non-essential
         * @param topic
         * @param time_offset need a time_offset to exceed the ros::TIME_MIN, choice: 1.65e9
         * @return is write successful
         */
        bool WriteImu(std::string& imu_file, std::string topic, double time_offset);

        /**
         * convert a txt feature file to bag
         * @param base_file a base path, each line: p.x, p.y, p.z, 1, u, v
         * @param topic
         * @param time_offset need a time_offset to exceed the ros::TIME_MIN, choice: 1.65e9
         */
        void WriteFeature(std::string& base_file, std::string topic, double time_offset);
        rosbag::Bag bag_;

    };
}//namespace tdros



#endif //SRC_BAG_WRITER_H
