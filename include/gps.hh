/*
  * Copyright 2012 Open Source Robotics Foundation
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
 */
 
 /*
  * Desc: 3D position interface for ground truth.
  * Author: Sachin Chitta and John Hsu
  * Date: 1 June 2008
  */
 
 #ifndef GAZEBO_ROS_P3D_HH
 #define GAZEBO_ROS_P3D_HH
 
 #include <string>
 
 #include <boost/thread.hpp>
 #include <boost/thread/mutex.hpp>
 
 #include <ros/ros.h>
 #include <nav_msgs/Odometry.h>
 
 #include <ros/callback_queue.h>
 #include <ros/advertise_options.h>
 
 #include <gazebo/physics/physics.hh>
 #include <gazebo/transport/TransportTypes.hh>
 #include <gazebo/common/Time.hh>
 #include <gazebo/common/Plugin.hh>
 #include <gazebo/common/Events.hh>
 
 #include <gazebo_plugins/PubQueue.h>
 
 namespace gazebo
 {
   class GazeboRosOdom : public ModelPlugin
   {
     public: GazeboRosOdom();
 
     public: virtual ~GazeboRosOdom();
 
     public: void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);
 
     protected: virtual void UpdateChild();
 
     private: physics::WorldPtr world_;
     private: physics::ModelPtr model_;
 
     private: physics::LinkPtr link_;
 
     private: physics::LinkPtr reference_link_;
 
 
     private: ros::NodeHandle* rosnode_;
     private: ros::Publisher pub_;
     private: PubQueue<nav_msgs::Odometry>::Ptr pub_Queue;
 
     private: nav_msgs::Odometry pose_msg_;
 
     private: std::string link_name_;
 
     private: std::string topic_name_;
 
     private: std::string frame_name_;
     private: std::string tf_frame_name_;
 
     private: ignition::math::Pose3d offset_;
 
     private: boost::mutex lock;
 
     private: common::Time last_time_;
     private: ignition::math::Vector3d last_vpos_;
     private: ignition::math::Vector3d pos_noise_sum;
     private: ignition::math::Vector3d last_veul_;
     private: ignition::math::Vector3d eul_noise_sum;
     private: ignition::math::Vector3d apos_;
     private: ignition::math::Vector3d aeul_;
     private: ignition::math::Vector3d last_frame_vpos_;
     private: ignition::math::Vector3d last_frame_veul_;
     private: ignition::math::Vector3d frame_apos_;
     private: ignition::math::Vector3d frame_aeul_;
 
     // rate control
     private: double update_rate_;
 
     private: double gaussian_noise_;
     private: double gaussian_bias_;
 
     private: double GaussianKernel(double mu, double sigma);
 
     private: std::string robot_namespace_;
 
    private: ros::CallbackQueue p3d_queue_;
     private: void QueueThread();
     private: boost::thread callback_queue_thread_;
 

     // Pointer to the update event connection
     private: event::ConnectionPtr update_connection_;
 
     // ros publish multi queue, prevents publish() blocking
     private: PubMultiQueue pmq;

     private: int sign(double x) { return x < 0 ? -1 : 1; };
   };
 }
 #endif