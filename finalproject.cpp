#include "rosbot_control/rosbot_class.h"
#include <cmath>
#include <ros/ros.h>
#include <math.h>
#include <string>

using namespace std;

class Rosbotmove {
public:
  Rosbotmove(string a) { left_right = a; }
  string left_right;
  RosbotClass rosbot;
  void avoid();
  float calc_distance(float x0, float y0, float x1, float y1);
};
void Rosbotmove::avoid() {
  float x0 = rosbot.get_position(1);
  float y0 = rosbot.get_position(2);
  ROS_INFO_STREAM("x0: " << rosbot.get_position(1));
  ROS_INFO_STREAM("y0: " << rosbot.get_position(2));
  rosbot.move_forward(1);

  while (rosbot.get_laser(0) > 2) {
    ROS_INFO_STREAM("Laser frontal reading: " << rosbot.get_laser(0));
    rosbot.move_forward(1);
  }
    ROS_INFO_STREAM("Laser frontal reading: " << rosbot.get_laser(0));

  if (left_right == "left") {

    rosbot.turn("counterclockwise", 3);
    rosbot.move_forward(2);
    rosbot.turn("clockwise", 3);

  } else if (left_right == "right") {

    rosbot.turn("clockwise", 3);
    rosbot.move_forward(2);
    rosbot.turn("counterclockwise", 3);

  } else {
    ROS_INFO_STREAM("Error: specify a direction for the movement: left or "
                    "right");
  }

  rosbot.stop_moving();

  float x1 = rosbot.get_position(1);
  float y1 = rosbot.get_position(2);

    float dist = calc_distance(x0,y0,x1,y1);
    while (dist < 5) {
  rosbot.move_forward(1);
  float x1 = rosbot.get_position(1);
  float y1 = rosbot.get_position(2);
  dist = calc_distance(x0,y0,x1,y1);
  }
  ROS_INFO_STREAM("x1: " << rosbot.get_position(1));
  ROS_INFO_STREAM("y1: " << rosbot.get_position(2));
  ROS_INFO_STREAM("dist: " << dist);

};

float Rosbotmove::calc_distance(float x0, float y0, float x1, float y1)
{
    return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "Rosbot_move_node");

  Rosbotmove rosbot_moves("right");
  rosbot_moves.avoid();
}