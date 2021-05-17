#!/bin/bash
rostopic echo -b rosbag.bag -p /ridgeback_velocity_controller/odom/twist/twist/linear/x > topic1.txt