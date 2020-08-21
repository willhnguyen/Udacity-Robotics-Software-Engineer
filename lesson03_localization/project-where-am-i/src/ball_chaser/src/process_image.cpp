#include <sensor_msgs/Image.h>
#include "ball_chaser/DriveToTarget.h"
#include "ros/ros.h"

namespace ball_chaser
{
struct BallSearchState
{
  bool found;
  uint64_t center;
  uint64_t n_pixels;
};

class Chaser
{
public:
  Chaser()
  {
    client_ = n_.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
    sub_ = n_.subscribe("/camera/rgb/image_raw", 10, &Chaser::process_image_callback, this);
  }
  ~Chaser()
  {
  }

  void process_image_callback(const sensor_msgs::Image img)
  {
    const BallSearchState ball_search_state = find_ball(img);

    // Move ball according to ball center x position
    // Stop ball if not visible or takes up 1/4 of the view
    uint32_t limit_left = img.width / 3;
    uint32_t limit_right = limit_left * 2;
    if (!ball_search_state.found)
      drive_stop();
    else if (ball_search_state.center < limit_left)
      drive_left();
    else if (ball_search_state.center > limit_right)
      drive_right();
    // else if (ball_search_state.n_pixels > ((img.height >> 1) * (img.width >> 1)))
    //   drive_stop();
    else
      drive_forward();
  }

private:
  ros::NodeHandle n_;
  ros::ServiceClient client_;
  ros::Subscriber sub_;

  void drive_robot(float lin_x, float ang_z)
  {
    ROS_INFO("Moving robot with linear_x %1.2f and angular_z %1.2f", lin_x, ang_z);

    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client_.call(srv))
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

  const BallSearchState find_ball(const sensor_msgs::Image img)
  {
    BallSearchState state;
    state.found = false;
    state.center = 0;

    std::vector<uint32_t> white_pixel_x_positions;
    white_pixel_x_positions.reserve(img.height * img.width);

    // Aggregate all white pixel x coordinate values
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
          state.found = true;
        }
      }
    }
    ROS_DEBUG_STREAM("Done Processing Image");

    // Determine x center
    state.n_pixels = white_pixel_x_positions.size();
    if (state.n_pixels != 0)
    {
      for (auto x : white_pixel_x_positions)
        state.center += x;
      state.center /= state.n_pixels;
    }
    else
      state.found = false;

    return state;
  }
};
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  ball_chaser::Chaser chaser;
  ros::spin();

  return 0;
}