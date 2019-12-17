//ros includes
#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/UInt8.h>

//ros node (only one possible on arduino)
ros::NodeHandle nodeHandle;

//ultrasoon publisher
const int ultrasoon_trigpin = 2;
const int ultrasoon_echopin = 4;
long ultrasoon_pub_timer = millis() + 1000;
std_msgs::UInt8 ultrasoon_msg;
ros::Publisher ultrasoon_pub("/arduino_slave/ultrasoon_sensor", &ultrasoon_msg);

//led state subscriber
int led1_pin = 13;
bool led1_state = false;
void messageCb( const std_msgs::Bool& msg)
{
  
  led1_state = msg.data;
}
ros::Subscriber<std_msgs::Bool> led1_sub("/arduino_slave/led1_actuator", &messageCb );

//ultrasoon routine function
void updateUltrasoon()
{
  if(millis() > ultrasoon_pub_timer)
  {
    //read ultrasoon
    long duration, distance;
    digitalWrite(ultrasoon_trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasoon_trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasoon_trigpin, LOW);
    duration=pulseIn(ultrasoon_echopin, HIGH);
    distance=duration*0.032/2;

    //publish data
    ultrasoon_msg.data = distance;
    millis();
    ultrasoon_pub.publish( &ultrasoon_msg );
    ultrasoon_pub_timer = millis() + 1000;
  }
}

//led 1 routine function
void updateLed1()
{
  //update led state
  digitalWrite(led1_pin, led1_state);
}

//arduino setup
void setup()
{
  //node init
  nodeHandle.initNode();

  //ultrasoon
  pinMode(ultrasoon_trigpin, OUTPUT);
  pinMode(ultrasoon_echopin, INPUT);
  nodeHandle.advertise(ultrasoon_pub);

  //setup led
  pinMode(led1_pin, OUTPUT);
  nodeHandle.subscribe(led1_sub);  
}

//routine
void loop()
{
  //update actuators
  updateLed1();

  //update sensors
  updateUltrasoon();

  //callback and send data
  nodeHandle.spinOnce();
}
