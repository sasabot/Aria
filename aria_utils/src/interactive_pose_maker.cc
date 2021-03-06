#include <iostream>
#include <fstream>
#include "aria.h"
#include "../../aria_2ndparty/src/common/ssb_common_common.h"
#include "../../aria_2ndparty/src/utils/ssb_utils_model.h"
#include <sensor_msgs/Joy.h>

#define PS3_BUTTON_SELECT            0
#define PS3_BUTTON_STICK_LEFT        1
#define PS3_BUTTON_STICK_RIGHT       2
#define PS3_BUTTON_START             3
#define PS3_BUTTON_CROSS_UP          4
#define PS3_BUTTON_CROSS_RIGHT       5
#define PS3_BUTTON_CROSS_DOWN        6
#define PS3_BUTTON_CROSS_LEFT        7
#define PS3_BUTTON_REAR_LEFT_2       8
#define PS3_BUTTON_REAR_RIGHT_2      9
#define PS3_BUTTON_REAR_LEFT_1       10
#define PS3_BUTTON_REAR_RIGHT_1      11
#define PS3_BUTTON_ACTION_TRIANGLE   12
#define PS3_BUTTON_ACTION_CIRCLE     13
#define PS3_BUTTON_ACTION_CROSS      14
#define PS3_BUTTON_ACTION_SQUARE     15
#define PS3_BUTTON_PAIRING           16

#define PS3_AXIS_STICK_LEFT_LEFTWARDS    0
#define PS3_AXIS_STICK_LEFT_UPWARDS      1
#define PS3_AXIS_STICK_RIGHT_LEFTWARDS   2
#define PS3_AXIS_STICK_RIGHT_UPWARDS     3
#define PS3_AXIS_BUTTON_CROSS_UP         4
#define PS3_AXIS_BUTTON_CROSS_RIGHT      5
#define PS3_AXIS_BUTTON_CROSS_DOWN       6
#define PS3_AXIS_BUTTON_CROSS_LEFT       7
#define PS3_AXIS_BUTTON_REAR_LEFT_2      8
#define PS3_AXIS_BUTTON_REAR_RIGHT_2     9
#define PS3_AXIS_BUTTON_REAR_LEFT_1      10
#define PS3_AXIS_BUTTON_REAR_RIGHT_1     11
#define PS3_AXIS_BUTTON_ACTION_TRIANGLE  12
#define PS3_AXIS_BUTTON_ACTION_CIRCLE    13
#define PS3_AXIS_BUTTON_ACTION_CROSS     14
#define PS3_AXIS_BUTTON_ACTION_SQUARE    15
#define PS3_AXIS_ACCELEROMETER_LEFT      16
#define PS3_AXIS_ACCELEROMETER_FORWARD   17
#define PS3_AXIS_ACCELEROMETER_UP        18
#define PS3_AXIS_GYRO_YAW                19

#define SENSITIVITY 0.05

namespace vec = ssb_common_vec;
namespace mdl = ssb_utils_model;

class InteractivePoseMaker : Aria
{
public:
  InteractivePoseMaker(ros::NodeHandle &nh);
  void Main();
  int getFPS(){ return _fps_; };
private:
  // button action functions
  bool ButtonAction(const sensor_msgs::Joy::ConstPtr& joy, int ps3_key,
                    void (InteractivePoseMaker::*func)(
                        const sensor_msgs::Joy::ConstPtr& joy),
                    void (InteractivePoseMaker::*exception)(
                        const sensor_msgs::Joy::ConstPtr& joy)
                    = &InteractivePoseMaker::ActionNone);
  bool HoldAction(const sensor_msgs::Joy::ConstPtr& joy, int ps3_key,
                  void (InteractivePoseMaker::*func)(
                      const sensor_msgs::Joy::ConstPtr& joy),
                  void (InteractivePoseMaker::*exception)(
                      const sensor_msgs::Joy::ConstPtr& joy)
                  = &InteractivePoseMaker::ActionNone);
  void ActionNone(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionControlList(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionSavePose(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionSwitch2Menu(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionSwitch2Main(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionGripperLeft(const sensor_msgs::Joy::ConstPtr& joy);
  void ExceptionGripperLeft(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionGripperRight(const sensor_msgs::Joy::ConstPtr& joy);
  void ExceptionGripperRight(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionEye(const sensor_msgs::Joy::ConstPtr& joy);
  void ExceptionEye(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionGripperSpeed(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionEyeSpeed(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionAddGripperSpeed(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionSubGripperSpeed(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionAddEyeSpeed(const sensor_msgs::Joy::ConstPtr& joy);
  void ActionSubEyeSpeed(const sensor_msgs::Joy::ConstPtr& joy);
  // joy callback functions
  void (InteractivePoseMaker::*joyfunc_)(const sensor_msgs::Joy::ConstPtr& joy);
  void JoyMenuInit(const sensor_msgs::Joy::ConstPtr& joy);
  void JoyMainInit(const sensor_msgs::Joy::ConstPtr& joy);
  void JoyMenu(const sensor_msgs::Joy::ConstPtr& joy);
  void JoyMain(const sensor_msgs::Joy::ConstPtr& joy);
  void Callback(const sensor_msgs::Joy::ConstPtr& joy);
  void Read(const std_msgs::String::ConstPtr& msg);
  void Write(const std_msgs::Float32MultiArray::ConstPtr& msg);
  // member variables
  ros::Publisher publisher_;
  ros::Subscriber subscriber_;
  ros::Subscriber file_subscriber_;
  ros::Subscriber joy_subscriber_;
  int _fps_;
  std::vector<std::vector<float> > pose_;
  std::vector<float> time_;
  bool flags_[19];
  // second party controller variables
  vec::VecGripper gripper_accel_;
  vec::VecEye eye_accel_;
  vec::VecGripper gripper_;
  vec::VecEye eye_;
  boost::shared_ptr<mdl::GripperModel> gripper_model_;
  boost::shared_ptr<mdl::QuadOEyeModel> eye_model_;
  float gripper_speed_;
  float eye_speed_;
};


InteractivePoseMaker::InteractivePoseMaker(ros::NodeHandle &nh) :
    Aria(nh), gripper_(0, 0), eye_(0, 0),
    gripper_accel_(0, 0), eye_accel_(0, 0)
{
  _fps_ = 30;
  for (int i=0; i<19; ++i)
    flags_[i] = false;
  publisher_ = nh_.advertise<std_msgs::Float32MultiArray>(
      "/concatenate_request/flow", 1000);
  subscriber_ = nh_.subscribe<std_msgs::Float32MultiArray>(
      "/concatenate_request/stock", 1000, &InteractivePoseMaker::Write, this);
  file_subscriber_ = nh_.subscribe<std_msgs::String>(
      "/aria_web_ui/file_request", 1000, &InteractivePoseMaker::Read, this);
  joy_subscriber_ = nh_.subscribe<sensor_msgs::Joy>(
      "/joy", 1000, &InteractivePoseMaker::Callback, this);
  joyfunc_ = &InteractivePoseMaker::JoyMainInit;
  gripper_speed_ = 0.1;
  eye_speed_ = 1.0;
  // init second party
  gripper_model_
    = boost::shared_ptr<mdl::GripperModel>(new mdl::GripperModel(nh));
  eye_model_
    = boost::shared_ptr<mdl::QuadOEyeModel>(new mdl::QuadOEyeModel(nh));
  // get goal position
  setFeedback(2);
}

void InteractivePoseMaker::Main()
{
  // This is written here because Callback is only called
  // when there are key press differences.
  if (flags_[PS3_AXIS_BUTTON_REAR_LEFT_1]
      || flags_[PS3_AXIS_BUTTON_REAR_RIGHT_1]) {
    gripper_.left -= SENSITIVITY*gripper_accel_.left*3;
    if (gripper_.left > 3.0) gripper_.left = 3.0;
    else if (gripper_.left < -0.5) gripper_.left = -0.5;
    gripper_.right += SENSITIVITY*gripper_accel_.right*3;
    if (gripper_.right > 3.0) gripper_.right = 3.0;
    else if (gripper_.right < -0.5) gripper_.right = -0.5;
    gripper_model_->set_input(vec::VecGripper(gripper_));
    gripper_model_->Input2Output();
    gripper_model_->send();
  }
  if (flags_[PS3_AXIS_BUTTON_REAR_LEFT_2]) {
    if (eye_.horizontal > 1.0) eye_.horizontal = 1.0;
    else if (eye_.horizontal < -1.0) eye_.horizontal = -1.0;
    eye_.vertical += SENSITIVITY*eye_accel_.vertical;
    if (eye_.vertical > 1.0) eye_.vertical = 1.0;
    else if (eye_.vertical < -1.0) eye_.vertical = -1.0;
    eye_model_->set_input(vec::VecEye(eye_));
    eye_model_->Input2Output();
    eye_model_->send();
  }
}

void InteractivePoseMaker::
Callback(const sensor_msgs::Joy::ConstPtr& joy)
{
  (this->*joyfunc_)(joy);
}


void InteractivePoseMaker::
Read(const std_msgs::String::ConstPtr& msg)
{
  std::string line;
  std::ifstream myfile(msg->data.c_str());
  if (myfile.is_open()) {
    getline(myfile, line);
    std::stringstream ss0(line);
    float number_of_pose, joints;
    ss0 >> number_of_pose >> joints;
    pose_.resize(number_of_pose);
    int i = 0;
    while (getline(myfile, line)) {
      std::stringstream ss(line);
      pose_[i].resize(joints);
      for (int j=0; j<joints; ++j) {
	ss >> pose_[i].at(j);
      }
      i++;
    }
    for (int i=0; i<pose_.size(); ++i) {
      std_msgs::Float32MultiArray msg;
      msg.data.resize(pose_[i].size());
      msg.data = pose_[i];
      publisher_.publish(msg);
    }
  }
}

void InteractivePoseMaker::
Write(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
  std::ofstream myfile;
  std::vector<float> data;
  data.resize(msg->data[1]);
  float joints = msg->data[2];
  myfile.open(ofToString(static_cast<int>(msg->data[0])).c_str());
  myfile << msg->data[1] << " " << msg->data[2] << "\n";
  for (int i=0; i<data.size(); ++i) {
    for (int j=0; j<joints; ++j)
      myfile << msg->data[3+i*joints+j] << " ";
    myfile << "\n";
  }
  myfile.close();
  ROS_WARN("saved data %s",ofToString(static_cast<int>(msg->data[0])).c_str());
}


bool InteractivePoseMaker::
ButtonAction(const sensor_msgs::Joy::ConstPtr& joy,
             int ps3_key,
             void (InteractivePoseMaker::*func)(
                 const sensor_msgs::Joy::ConstPtr& joy),
             void (InteractivePoseMaker::*exception)(
                 const sensor_msgs::Joy::ConstPtr& joy))
{
  if ((joy->axes[ps3_key] < -0.5)) {
    if (flags_[ps3_key])
      return false;
    flags_[ps3_key] = true;
    (this->*func)(joy);
    return true;
  } else {
    flags_[ps3_key] = false;
    (this->*exception)(joy);
    return false;
  }
}

bool InteractivePoseMaker::
HoldAction(const sensor_msgs::Joy::ConstPtr& joy,
           int ps3_key,
           void (InteractivePoseMaker::*func)(
               const sensor_msgs::Joy::ConstPtr& joy),
           void (InteractivePoseMaker::*exception)(
               const sensor_msgs::Joy::ConstPtr& joy))
{
  if ((joy->axes[ps3_key] < -0.4)) {
    flags_[ps3_key] = true;
    (this->*func)(joy);
    return true;
  } else {
    flags_[ps3_key] = false;
    (this->*exception)(joy);
    return false;
  }
}

void InteractivePoseMaker::
ActionNone(const sensor_msgs::Joy::ConstPtr& joy)
{
}

void InteractivePoseMaker::
ActionSavePose(const sensor_msgs::Joy::ConstPtr& joy)
{
  std_msgs::Float32MultiArray msg;
  int data_size = c_.debug.size();
  msg.data.resize(data_size);
  msg.data = c_.debug;
  msg.data.resize(data_size+5);
  msg.data.at(data_size) = gripper_.left;
  msg.data.at(data_size+1) = gripper_.right;
  msg.data.at(data_size+2) = eye_.horizontal;
  msg.data.at(data_size+3) = eye_.vertical;
  msg.data.at(data_size+4) = 3.0; // extra element for time
  publisher_.publish(msg);
  ROS_WARN("saved pose");
}

void InteractivePoseMaker::
ActionSwitch2Menu(const sensor_msgs::Joy::ConstPtr& joy)
{
  joyfunc_ = &InteractivePoseMaker::JoyMenuInit;
}

void InteractivePoseMaker::
ActionSwitch2Main(const sensor_msgs::Joy::ConstPtr& joy)
{
  joyfunc_ = &InteractivePoseMaker::JoyMainInit;
}

void InteractivePoseMaker::
ExceptionGripperLeft(const sensor_msgs::Joy::ConstPtr& joy)
{
  gripper_accel_.left = 0;
}

void InteractivePoseMaker::
ExceptionGripperRight(const sensor_msgs::Joy::ConstPtr& joy)
{
  gripper_accel_.right = 0;
}

void InteractivePoseMaker::
ActionAddGripperSpeed(const sensor_msgs::Joy::ConstPtr& joy)
{
  gripper_speed_ += 0.1;
  ROS_WARN("%f", gripper_speed_);
}

void InteractivePoseMaker::
ActionSubGripperSpeed(const sensor_msgs::Joy::ConstPtr& joy)
{
  gripper_speed_ -= 0.05;
  ROS_WARN("%f", gripper_speed_);
}

void InteractivePoseMaker::
ActionAddEyeSpeed(const sensor_msgs::Joy::ConstPtr& joy)
{
  eye_speed_ += 1.0;
  ROS_WARN("%f", gripper_speed_);
}

void InteractivePoseMaker::
ActionSubEyeSpeed(const sensor_msgs::Joy::ConstPtr& joy)
{
  eye_speed_ -= 0.5;
  ROS_WARN("%f", gripper_speed_);
}


void InteractivePoseMaker::
ActionControlList(const sensor_msgs::Joy::ConstPtr& joy)
{
  ROS_INFO("%s\n %s\n %s\n %s\n %s\n %s\n",
           "control list:",
           " save pose: press [circle]",
           " move left gripper: hold [L1] tilt [left_stick]",
           " move right gripper: hold [R1] tilt [left_stick]",
           " move eye: tilt [right_stick]",
           " triangle: open config menu");
}

void InteractivePoseMaker::
ActionGripperLeft(const sensor_msgs::Joy::ConstPtr& joy)
{
  if (fabsf(joy->axes[PS3_AXIS_STICK_LEFT_LEFTWARDS]) < 0.5)
    gripper_accel_.left = 0;
  else
    gripper_accel_.left =
        gripper_speed_*joy->axes[PS3_AXIS_STICK_LEFT_LEFTWARDS]
        /fabsf(joy->axes[PS3_AXIS_STICK_LEFT_LEFTWARDS]);
}

void InteractivePoseMaker::
ActionGripperRight(const sensor_msgs::Joy::ConstPtr& joy)
{
  if (fabsf(joy->axes[PS3_AXIS_STICK_LEFT_LEFTWARDS]) < 0.5)
      gripper_accel_.right = 0;
  else
    gripper_accel_.right =
        gripper_speed_*joy->axes[PS3_AXIS_STICK_LEFT_LEFTWARDS]
        /fabsf(joy->axes[PS3_AXIS_STICK_LEFT_LEFTWARDS]);
}

void InteractivePoseMaker::
ActionEye(const sensor_msgs::Joy::ConstPtr& joy)
{
  eye_accel_.horizontal = -eye_speed_*joy->axes[PS3_AXIS_STICK_RIGHT_LEFTWARDS];
  eye_accel_.vertical = eye_speed_*joy->axes[PS3_AXIS_STICK_RIGHT_UPWARDS];
  eye_.horizontal += SENSITIVITY*eye_accel_.horizontal;
}

void InteractivePoseMaker::
ExceptionEye(const sensor_msgs::Joy::ConstPtr& joy)
{
  eye_accel_.horizontal = 0;
  eye_accel_.vertical = 0;
}

void InteractivePoseMaker::
ActionGripperSpeed(const sensor_msgs::Joy::ConstPtr& joy)
{
  ButtonAction(joy, PS3_AXIS_BUTTON_CROSS_RIGHT,
               &InteractivePoseMaker::ActionAddGripperSpeed);
  ButtonAction(joy, PS3_AXIS_BUTTON_CROSS_LEFT,
               &InteractivePoseMaker::ActionSubGripperSpeed);
}

void InteractivePoseMaker::
ActionEyeSpeed(const sensor_msgs::Joy::ConstPtr& joy)
{
  ButtonAction(joy, PS3_AXIS_BUTTON_CROSS_RIGHT,
               &InteractivePoseMaker::ActionAddEyeSpeed);
  ButtonAction(joy, PS3_AXIS_BUTTON_CROSS_LEFT,
               &InteractivePoseMaker::ActionSubEyeSpeed);
}

void InteractivePoseMaker::
JoyMenuInit(const sensor_msgs::Joy::ConstPtr& joy) {
  ROS_WARN("switched to menu");
  ROS_INFO("%s\n %s\n %s\n %s\n",
           "Menu:",
           " change left gripper speed: hold [L1]or[R1] press [<][>]",
           " change eye speed: hold [right_stick] press [<][>]",
           " triangle: return");
  joyfunc_ = &InteractivePoseMaker::JoyMenu;
}

void InteractivePoseMaker::
JoyMenu(const sensor_msgs::Joy::ConstPtr& joy) {
  ButtonAction(joy, PS3_AXIS_BUTTON_ACTION_TRIANGLE,
               &InteractivePoseMaker::ActionSwitch2Main);
  HoldAction(joy, PS3_AXIS_BUTTON_REAR_LEFT_1,
             &InteractivePoseMaker::ActionGripperSpeed);
  HoldAction(joy, PS3_AXIS_BUTTON_REAR_RIGHT_1,
             &InteractivePoseMaker::ActionGripperSpeed);
  HoldAction(joy, PS3_AXIS_BUTTON_REAR_LEFT_2,
             &InteractivePoseMaker::ActionEyeSpeed);
}

void InteractivePoseMaker::
JoyMainInit(const sensor_msgs::Joy::ConstPtr& joy) {
  ROS_WARN("switched to head and gripper");
  joyfunc_ = &InteractivePoseMaker::JoyMain;
}

void InteractivePoseMaker::
JoyMain(const sensor_msgs::Joy::ConstPtr& joy) {
  ButtonAction(joy, PS3_AXIS_BUTTON_ACTION_SQUARE,
               &InteractivePoseMaker::ActionControlList);
  ButtonAction(joy, PS3_AXIS_BUTTON_ACTION_TRIANGLE,
               &InteractivePoseMaker::ActionSwitch2Menu);
  ButtonAction(joy, PS3_AXIS_BUTTON_ACTION_CIRCLE,
               &InteractivePoseMaker::ActionSavePose);
  // Set gripper accel.
  HoldAction(joy, PS3_AXIS_BUTTON_REAR_LEFT_1,
	     &InteractivePoseMaker::ActionGripperLeft,
	     &InteractivePoseMaker::ExceptionGripperLeft);
  HoldAction(joy, PS3_AXIS_BUTTON_REAR_RIGHT_1,
	     &InteractivePoseMaker::ActionGripperRight,
	     &InteractivePoseMaker::ExceptionGripperRight);
  // Set eye accel.
  HoldAction(joy, PS3_AXIS_BUTTON_REAR_LEFT_2,
	     &InteractivePoseMaker::ActionEye,
	     &InteractivePoseMaker::ExceptionEye);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "second_party_controller");
  ros::NodeHandle nh;
  InteractivePoseMaker controller(nh);
  ros::Rate loop(controller.getFPS());
  while(ros::ok()) {
    controller.Main();
    ros::spinOnce();
    loop.sleep();
  }
};
