//ros includes
#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int16.h>

#include "arduino_motors.h"

//ros node (only one possible on arduino)
ros::NodeHandle nodeHandle;

//led1 data
const int led13_pin = 13;
bool led13_state = false;
void ledMessageCb( const std_msgs::Bool& msg)
{
  led13_state = msg.data;
}
ros::Subscriber<std_msgs::Bool> led13_sub("/arduino_actuator_slave/led13", &ledMessageCb );

//steering data
int side = 0;
bool cmd_side = false;
void sideMessageCb( const std_msgs::Int16& msg)
{
  cmd_side = true;
  side = msg.data;
}
ros::Subscriber<std_msgs::Int16> side_sub("/arduino_actuator_slave/side", &sideMessageCb );

//velocity data
int direction = 0;
bool cmd_direction = false
void directionMessageCb( const std_msgs::Int16& msg)
{
  cmd_direction = true;
  direction = msg.data;
}
ros::Subscriber<std_msgs::Int16> direction_sub("/arduino_actuator_slave/direction", &directionMessageCb );


//led 1 routine function
void update_actuators()
{
  //update led state
  if(led13_state)
  {
    digitalWrite(led13_pin, HIGH);
  }
  else
  {
    digitalWrite(led13_pin, LOW);
  }

  //update motors if received messages
  if(cmd_direction && cmd_side)
  {
    update_motors(direction, side);
  }
  else
  {
    //stop motors
    update_motors(0, 0);
  }
  
}

//arduino setup
void setup()
{
  //node init
  nodeHandle.initNode();

  //setup led
  pinMode(led13_pin, OUTPUT);
  nodeHandle.subscribe(led13_sub);  

  //setup motors
  setup_motors();
  nodeHandle.subscribe(direction_sub);
  nodeHandle.subscribe(side_sub);
}

//routine
void loop()
{
  //update actuators based subscribed data
  update_actuators();

  //callback and make sure received important messages
  cmd_direction = false;
  cmd_side = false;
  nodeHandle.spinOnce();

}