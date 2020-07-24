#include <td_ros/arm_moveit.h>
namespace tdros{
    void toJointSpace(const std::string& planning_group, const std::vector<double>& joint_space){
        // MoveIt! operates on sets of joints called "planning groups" and stores them in an object called
        // the `JointModelGroup`. Throughout MoveIt! the terms "planning group" and "joint model group"
        // are used interchangably.
        // The :move_group_interface:`MoveGroup` class can be easily
        // setup using just the name of the planning group you would like to control and plan for.
        moveit::planning_interface::MoveGroupInterface move_group(planning_group);

        // Raw pointers are frequently used to refer to the planning group for improved performance.
        const robot_state::JointModelGroup* joint_model_group =
                move_group.getCurrentState()->getJointModelGroup(planning_group);
        // Now, we call the planner to compute the plan and visualize it.
        // Note that we are just planning, not asking move_group
        // to actually move the robot.
        moveit::planning_interface::MoveGroupInterface::Plan my_plan;
        // To start, we'll create an pointer that references the current robot's state.
        // RobotState is the object that contains all the current position/velocity/acceleration data.
        move_group.setJointValueTarget(joint_space);
        bool success = false;
//        int count = 0;
//        while(!success){
            success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
//            ros::WallDuration(0.1).sleep();
//            count++;
//            if(count==10)
//                ROS_WARN("wait for the plan success");
//        }

        ROS_INFO_NAMED("tutorial", "Visualizing plan 2 (joint space goal) %s", success ? "" : "FAILED");
        if(success)
            move_group.move();

    }
}
