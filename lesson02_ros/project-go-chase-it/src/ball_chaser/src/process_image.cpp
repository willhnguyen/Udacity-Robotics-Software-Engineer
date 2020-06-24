#include <sensor_msgs/Image.h>
#include "ball_chaser/DriveToTarget.h"
#include "ros/ros.h"

ros::ServiceClient client;

void drive_robot(float lin_x, float ang_z)
{
  ROS_INFO("Moving robot with linear_x %1.2f and angular_z %1.2f", lin_x, ang_z);

  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;

  if (!client.call(srv))
    ROS_ERROR("Failed to call service command_robot");
}

inline void drive_right()
{
  ROS_DEBUG_STREAM("Moving robot right");
  drive_robot(0.0, -0.5);
}
inline void drive_left()
{
  ROS_DEBUG_STREAM("Moving robot left");
  drive_robot(0.0, 0.5);
}
inline void drive_forward()
{
  ROS_DEBUG_STREAM("Moving robot forward");
  drive_robot(0.5, 0.0);
}
inline void drive_stop()
{
  ROS_DEBUG_STREAM("Stopping robot");
  drive_robot(0.0, 0.0);
}

void process_image_callback(const sensor_msgs::Image img)
{
  bool ball_found = false;
  std::vector<uint32_t> white_pixel_x_positions;
  white_pixel_x_positions.reserve(img.height * img.width);

  // Find x coordinate of center pixel value
  uint32_t channels = img.step / img.width;

  uint64_t i = 0;
  for (int h = 0; h < img.height; ++h)
  {
    for (uint32_t w = 0; w < img.width; ++w)
    {
      // White is when all 3 channels is 255
      bool is_white = true;
      for (uint32_t c = 0; c < channels; ++c)
      {
        if (img.data[i] != 255)
          is_white = false;
        ++i;
      }
      if (is_white)
      {
        white_pixel_x_positions.push_back(w);
        ball_found = true;
      }
    }
  }
  ROS_DEBUG_STREAM("Done Processing Image");

  // Determine x center
  uint64_t x_center = 0;
  uint64_t n_pixels = white_pixel_x_positions.size();
  if (n_pixels != 0)
  {
    for (auto x : white_pixel_x_positions)
      x_center += x;
    x_center /= n_pixels;
  }
  else
    ball_found = false;

  // Move ball according to ball center x position
  uint32_t limit_left = img.width / 3;
  uint32_t limit_right = limit_left * 2;
  if (!ball_found)
    drive_stop();
  else if (x_center < limit_left)
  {
    drive_left();
  }
  else if (x_center > limit_right)
  {
    drive_right();
  }
  // Stop if ball takes up more than half the center view
  else if (n_pixels > ((img.height >> 1) * (img.width >> 1)))
    drive_stop();
  else
    drive_forward();
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

  ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

  // Handle ROS communication events
  ros::spin();

  return 0;
}