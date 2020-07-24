# Overview
This is a persoal ROS library include the commonly used functions in development.
## Dependencies
- Sophus
```asm
sudo apt-get install ros-kinetic-sophus
```
# Getting Started
clone
```
git clone https://github.com/TouchDeeper/TdRosLib.git your_path/
```

CMakeLists.txt
```
set(TdRosLib_PATH "your_path")
add_library(TdRosLib SHARED ${TdRosLib_PATH}/src/tool.cpp ${TdRosLib_PATH}/src/arm_moveit.cpp)
target_link_libraries(TdRosLib PRIVATE ${catkin_LIBRARIES} ${Boost_LIBRARIES})
include_directories(${TdRosLib_PATH}/include)

target_link_libraries(your_target TdRosLib)
```
