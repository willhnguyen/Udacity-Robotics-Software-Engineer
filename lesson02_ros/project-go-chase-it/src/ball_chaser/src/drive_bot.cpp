#include "ball_chaser/DriveToTarget.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"

namespace ball_chaser
{
class BotDriver
{
public:
  BotDriver()
  {
    pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    service_ = n_.advertiseService("/ball_chaser/command_robot", &BotDriver::handle_drive_request, this);
  }
  ~BotDriver()
  {
  }

  bool handle_drive_request(ball_chaser::DriveToTarget::Request &req, ball_chaser::DriveToTarget::Response &res)
  {
    ROS_INFO("DriveToTargetRequest received - linear_x:%1.2f, angular_z:%1.2f", (float)req.linear_x,
             (float)req.angular_z);

    // Create & publish message with requested parameters for linear x and angular z
    geometry_msgs::Twist motor_command;
    motor_command.linear.x = req.linear_x;
    motor_command.angular.z = req.angular_z;

    pub_.publish(motor_command);

    // Give robot time to move
    ros::Duration(0.1).sleep();

    // Return response message
    res.msg_feedback = "DriveToTarget set - linear_x: " + std::to_string(motor_command.linear.x) + " , angular_z: " +
                       std::to_string(motor_command.angular.z);
    ROS_INFO_STREAM(res.msg_feedback);

    return true;
  }

private:
  ros::NodeHandle n_;
  ros::Publisher pub_;
  ros::ServiceServer service_;
};
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "drive_bot");
  ros::NodeHandle n;

  ball_chaser::BotDriver bot_driver;
  ros::spin();

  return 0;
}