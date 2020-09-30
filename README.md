# Overview
This is a persoal ROS library include the commonly used functions in development.
## Dependencies
- Sophus
```asm
sudo apt-get install ros-kinetic-sophus
```
# Getting Started
- clone
```
git clone https://github.com/TouchDeeper/td_ros.git [your_workspace]/src
```


- Modify the CMakeLists.txt of the package which depend on td_ros:
    1. add `td_ros` to `find_package(... td_ros)`
    2. add 'td_ros' to `catkin_package(... CATKIN_DEPENDS ... to_ros)`
    3. add `<build_depend>td_ros</build_depend>` and `<exec_depend>td_ros</exec_depend>` in package.xml

