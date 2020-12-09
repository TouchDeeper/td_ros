#include <td_ros/tool.h>

namespace tdros{


    void SetPosition(const ros::Publisher &chatter_pub, const std::string& model_name, const Sophus::SE3d& w_T_object, int loop_rate_, int count_sum ){

        std::cout<<"set "<<model_name<<" in "<<w_T_object.log().transpose()<<std::endl;
        Eigen::Vector3d w_t_object = w_T_object.translation();
        Eigen::Quaternion<double> w_Q_object = Eigen::Quaternion<double>(w_T_object.rotationMatrix());
        ros::Rate loop_rate(loop_rate_);
        int count = 0;
        while (count <count_sum)
        {
            // the position of falling
            gazebo_msgs::ModelState modelState;
            modelState.model_name = model_name;
            modelState.pose.position.x = w_t_object[0];
            modelState.pose.position.y = w_t_object[1];
            modelState.pose.position.z = w_t_object[2];
            modelState.pose.orientation.w = w_Q_object.w();
            modelState.pose.orientation.x = w_Q_object.x();
            modelState.pose.orientation.y = w_Q_object.y();
            modelState.pose.orientation.z = w_Q_object.z();

            // 发布消息
//                ROS_INFO("goal pose: %lf, %lf, %lf, %lf, %lf, %lf ",modelState.pose.position.x, modelState.pose.position.y, modelState.pose.position.z);
            chatter_pub.publish(modelState);

            // 循环等待回调函数
            ros::spinOnce();

            // 按照循环频率延时
            loop_rate.sleep();
            ++count;
        }
    }
    void SetPosition(const ros::Publisher &chatter_pub, const std::string& model_name, const Eigen::Matrix4f& transform_matrix, int loop_rate_, int count_sum ){

        std::cout<<"set "<<model_name<<" in \n"<<transform_matrix<<std::endl;

        Eigen::Quaternionf w_Q_object;
        w_Q_object = transform_matrix.block<3,3>(0,0);
        ros::Rate loop_rate(loop_rate_);
        int count = 0;
        while (count <count_sum)
        {
            // the position of falling
            gazebo_msgs::ModelState modelState;
            modelState.model_name = model_name;
            modelState.pose.position.x = transform_matrix(0,3);
            modelState.pose.position.y = transform_matrix(1,3);
            modelState.pose.position.z = transform_matrix(2,3);
            modelState.pose.orientation.w = w_Q_object.w();
            modelState.pose.orientation.x = w_Q_object.x();
            modelState.pose.orientation.y = w_Q_object.y();
            modelState.pose.orientation.z = w_Q_object.z();

            // 发布消息
//                ROS_INFO("goal pose: %lf, %lf, %lf, %lf, %lf, %lf ",modelState.pose.position.x, modelState.pose.position.y, modelState.pose.position.z);
            chatter_pub.publish(modelState);

            // 循环等待回调函数
            ros::spinOnce();

            // 按照循环频率延时
            loop_rate.sleep();
            ++count;
        }
    }
    void PauseGazebo(ros::NodeHandle &n){
        ros::ServiceClient pauseGazebo = n.serviceClient<std_srvs::Empty>("/gazebo/pause_physics");
        std_srvs::Empty pauseSrv;
        pauseGazebo.call(pauseSrv);
        bool continueInput = true;
        // call the script program
        while (continueInput && ros::ok())
        {
            std::cout<<"enter y to continue"<<std::endl;
            char key;
            std::cin>>key;
            if('y' == key)
            {
                pauseGazebo.shutdown();
                ros::ServiceClient unpauseGazebo = n.serviceClient<std_srvs::Empty>("/gazebo/unpause_physics");
                std_srvs::Empty unpauseSrv;
                unpauseGazebo.call(unpauseSrv);
                std::cout<<"y is pushed"<<std::endl;
                continueInput = false;
            }
        }
    }
    void SpawnModel(ros::NodeHandle& nh, const std::string& path, const std::string& model_name){
        std::ifstream file;
        file.open(path);
        if(!file){
            std::cout<<"can't open "<<path<<std::endl;
            exit(-1);
        }
        gazebo_msgs::SpawnModel model;
        ros::ServiceClient client_spwn = nh.serviceClient< gazebo_msgs::SpawnModel> ("/gazebo/spawn_urdf_model");
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                model.request.model_xml+=line;
            }
            file.close();
        }

        model.request.model_name = model_name;
        model.request.initial_pose.position.x = 4;
        model.request.initial_pose.position.y = 4;
        model.request.initial_pose.position.z = 4;
        client_spwn.call(model);
    }
}
