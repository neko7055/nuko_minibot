/*
 Copyright 2018 NCU MATH.
 Developer: Kuo-Shih Tseng (kuoshih@math.ncu.edu.tw)
 Description: This code activate a node "main." 
 This node subscribes three topics -- imu_data, odom, and scan. 
 You can access data from three Callback functions.
 $Revision: 1.0 $,  2018.07.24 
 $Revision: 1.1 $,  2018.12.20, add a maker for users 
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
     http://www.apache.org/licenses/LICENSE-2.0
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

// %Tag(FULLTEXT)%
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/LaserScan.h"
#include <visualization_msgs/Marker.h>
#define RAD2DEG(x) ((x)*180./M_PI)

void callback1(const ros::TimerEvent&);
void init_marker(void);

visualization_msgs::Marker marker;
uint32_t shape = visualization_msgs::Marker::CYLINDER;
ros::Publisher marker_pub;
int counter=0;

void callback1(const ros::TimerEvent&)
{// update maker location and publish it. 
    //float x=1*cos(0.174*counter);
    //float y=1*sin(0.174*counter);
    //marker.pose.position.x = x;
    //marker.pose.position.y = y;
    //ROS_INFO("x=%f,y=%f\n",x,y);
    //counter++;

    //marker_pub.publish(marker);
}

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    //ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
}


void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    //int count = scan->scan_time / scan->time_increment;
    //printf("[YDLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
    /*
    printf("[YDLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));
 
    for(int i = 0; i < count; i++) 
    {
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
	    if(degree > -5 && degree< 5)
        {printf("[YDLIDAR INFO]: angle-distance : [%f, %f, %i]\n", degree, scan->ranges[i], i);}
    }
    */
    
}


int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "listener");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
  //ros::Rate r(1);

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */ 

  ros::Subscriber sub3 = n.subscribe("/odom", 1000, odomCallback);
  ros::Subscriber sub4 = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);

  // create a timer callback
  ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1);
  // create a topic "visualization_marker"
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  init_marker();

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */

  ros::spin();


  return 0;
}

void init_marker(void)
{
    // Initialize maker's setting.
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/target";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;
    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    // Tag(ACTION)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    //Tag(POSE)
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    //Tag(LIFETIME)
    marker.lifetime = ros::Duration();

}
