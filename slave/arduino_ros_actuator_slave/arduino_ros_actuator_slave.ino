//ros includes
#include <ros.h>
#include <std_msgs/Bool.h>

//ros node (only one possible on arduino)
ros::NodeHandle nodeHandle;

//led1 data
int led13_pin = 13;
bool led13_state = false;
void messageCb( const std_msgs::Bool& msg)
{
  led13_state = msg.data;
}
ros::Subscriber<std_msgs::Bool> led13_sub("/arduino_actuator_slave/led13", &messageCb );


//led 1 routine function
void update_actuators()
{
  //update led state
  if(led13_state)
    digitalWrite(led13_pin, HIGH);
  else
    digitalWrite(led13_pin, LOW);
}

//arduino setup
void setup()
{
  //node init
  nodeHandle.initNode();

  //setup led
  pinMode(led13_pin, OUTPUT);
  nodeHandle.subscribe(led13_sub);  

}

//routine
void loop()
{
  //update actuators based subscribed data
  update_actuators();

  //callback and send data
  nodeHandle.spinOnce();

}