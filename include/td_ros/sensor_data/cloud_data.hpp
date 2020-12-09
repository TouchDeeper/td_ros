/*
 * @Description:
 * @Author: Ren Qian
 * @Date: 2019-07-17 18:17:49
 */
#pragma once

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

namespace lidar_localization {
class CloudData {
  public:
    using POINT = pcl::PointXYZ;
    using CLOUD = pcl::PointCloud<POINT>;
    using CLOUD_PTR = CLOUD::Ptr;

  public:
    CloudData()
      :cloud_ptr(new CLOUD()) {
    }

  public:
    double time = 0.0;
    CLOUD_PTR cloud_ptr;
};
}
