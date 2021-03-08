//
// Created by td on 2021/3/8.
//

#include "bag_writer.h"
namespace tdros{
    bool BagWriter::WriteImu(std::string& imu_file, std::string topic, double time_offset){
        std::ifstream ifs_imu;
        ifs_imu.open(imu_file.c_str());
        if (!ifs_imu.is_open())
        {
            std::cerr << "Failed to open imu file! " << imu_file << std::endl;
            return false;
        }

        std::string sImu_line;
        double dStampSec = 0.0;
        Eigen::Vector3d vAcc;
        Eigen::Vector3d vGyr;
        while (std::getline(ifs_imu, sImu_line) && !sImu_line.empty()) // read imu data
        {
            std::istringstream ssImuData(sImu_line);
            Eigen::Quaterniond q;
            Eigen::Vector3d t;
            sensor_msgs::Imu imu;
            ssImuData >> dStampSec >> q.w() >> q.x() >> q.y() >> q.z() >> t(0) >> t(1) >> t(2) >> vGyr.x() >> vGyr.y() >> vGyr.z() >> vAcc.x() >> vAcc.y() >> vAcc.z();
            imu.header.stamp = ros::Time(dStampSec + time_offset);
            imu.angular_velocity.x = vGyr[0];
            imu.angular_velocity.y = vGyr[1];
            imu.angular_velocity.z = vGyr[2];
            imu.linear_acceleration.x = vAcc[0];
            imu.linear_acceleration.y = vAcc[1];
            imu.linear_acceleration.z = vAcc[2];
            std::cout << "Imu t: " << std::fixed << imu.header.stamp.toSec() << " gyr: " << vGyr.transpose() << " acc: " << vAcc.transpose() << std::endl;

            bag_.write(topic, imu.header.stamp, imu);
        }
        ifs_imu.close();
    }
    void BagWriter::WriteFeature(std::string& base_file, std::string topic, double time_offset){
        int i=0;
        while (true) {
            std::string feature_file = base_file + "_" + std::to_string(i) + ".txt";
            std::ifstream ifs_feature;
            ifs_feature.open(feature_file.c_str());
            if (!ifs_feature.is_open())
            {
                std::cerr << "Failed to open feature file! " << feature_file << std::endl;
                break;
            }
            std::string sFeature_line;
            double dStampSec = 0.0;
            Eigen::Vector3d vAcc;
            Eigen::Vector3d vGyr;
            sensor_msgs::PointCloud features;
            while (std::getline(ifs_feature, sFeature_line) && !sFeature_line.empty()) // read imu data
            {
                std::istringstream ssFeatureData(sFeature_line);
                Eigen::Quaterniond q;
                Eigen::Vector3d t;
                geometry_msgs::Point32_<std::allocator<void>> feature;
                Eigen::Vector4d point;//useless
                ssFeatureData >> point(0) >> point(1) >> point(2) >> point(3) >> feature.x >> feature.y >> dStampSec;
                features.points.push_back(feature);
            }
            features.header.stamp = ros::Time(dStampSec+time_offset);
            bag_.write(topic, features.header.stamp, features);
            std::cout << "features t: " << std::fixed << features.header.stamp.toSec() << std::endl;
            ifs_feature.close();
            i++;
        }
    }
}//namespace tdross