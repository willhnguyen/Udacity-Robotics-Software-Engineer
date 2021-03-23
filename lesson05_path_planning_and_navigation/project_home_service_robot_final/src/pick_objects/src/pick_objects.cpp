#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -8.0; // -6.8;
  goal.target_pose.pose.position.y = 2.6; // -2.4;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base moved to the pick up zone");
  }
  else
    ROS_INFO("The base failed to move to the pick up zone for some reason");

  // Wait 5 seconds for pick up
  ros::Duration(5.0).sleep();
  ROS_INFO("The robot picked up package");

  // Move to Drop off zone
  move_base_msgs::MoveBaseGoal second_goal;

  second_goal.target_pose.header.frame_id = "map";
  second_goal.target_pose.header.stamp = ros::Time::now();

  second_goal.target_pose.pose.position.x = 8.89;
  second_goal.target_pose.pose.position.y = 5.39;
  second_goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal to drop off zone");
  ac.sendGoal(second_goal);
  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base moved to drop off zone");
  }
  else
    ROS_INFO("The base failed to move to the drop off zone for some reason");

  // Wait 5 seconds for drop off
  ros::Duration(5.0).sleep();
  ROS_INFO("The robot dropped off package");

  // Wait 10 seconds for user to read
  ros::Duration(10.0).sleep();

  return 0;
}
