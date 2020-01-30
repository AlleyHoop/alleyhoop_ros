//ros includes
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/Bool.h>
#include <std_msgs/UInt8.h>
#include <sensor_msgs/Imu.h>

#include "arduino_imu.h"
#include "arduino_ultrasonic_sensor.h"
#include "arduino_linetracking_sensors.h"

//ros node (only one possible on arduino)
ros::NodeHandle nodeHandle;

//led1 data
const int led13_pin = 13;
bool led13_state = false;
const long cmd_led13_timer_rate = 200; 
long cmd_led13_timer = millis() + cmd_led13_timer_rate;  //timer to check if led data was updated
void messageCb( const std_msgs::Bool& msg)
{
  cmd_led13_timer = millis() + cmd_led13_timer_rate; //reset the timer since new data has arrived
  led13_state = msg.data;
}
ros::Subscriber<std_msgs::Bool> led13_sub("/arduino_sensor_slave/led13", &messageCb );

//ultrasonic data
const long ultrasonic_pub_rate = 100;
long ultrasonic_pub_timer = millis() + ultrasonic_pub_timer;
std_msgs::UInt8 ultrasonic_msg;
ros::Publisher ultrasonic_pub("/arduino_sensor_slave/ultrasonic_sensor", &ultrasonic_msg);

//imu data
const long imu_pub_rate = 200;
long imu_pub_timer = millis() + imu_pub_rate;
sensor_msgs::Imu imu_msg;
ros::Publisher imu_pub("/arduino_sensor_slave/imu_sensor", &imu_msg);

//linetracking sensors
std_msgs::Bool linetracker1_msg;
std_msgs::Bool linetracker2_msg;
const long linetrackers_pub_rate = 200;
long linetrackers_pub_timer = millis() + linetrackers_pub_rate;
ros::Publisher linetracker1_pub("/arduino_sensor_slave/linetracker_left", &linetracker1_msg);
ros::Publisher linetracker2_pub("/arduino_sensor_slave/linetracker_right", &linetracker2_msg);

//ultrasonic routine function
void update_sensors()
{
  //update ultrasonic data
  if(millis() > ultrasonic_pub_timer)
  {
    //update data
    update_ultrasonic_sensor();

    //set data
    ultrasonic_msg.data = ultrasonic_sensor_data;

    //publish data
    ultrasonic_pub.publish( &ultrasonic_msg );
    ultrasonic_pub_timer = millis() + ultrasonic_pub_rate;
  }

  //update imu data
  if(millis() > imu_pub_timer)
  {
    //update data
    update_imu();

    //set data
    imu_msg.header.frame_id = 0;
    imu_msg.header.stamp = nodeHandle.now();
    
    imu_msg.orientation_covariance[0] = -1;
    imu_msg.orientation.w = 1;
    imu_msg.orientation.x = Mxyz[0];
    imu_msg.orientation.y = Mxyz[1];
    imu_msg.orientation.z = Mxyz[2];

    imu_msg.linear_acceleration_covariance[0] = -1;
    imu_msg.linear_acceleration.x = Axyz[0];
    imu_msg.linear_acceleration.y = Axyz[1];
    imu_msg.linear_acceleration.z = Axyz[2];

    imu_msg.angular_velocity_covariance[0] = -1;
    imu_msg.angular_velocity.x = Gxyz[0];
    imu_msg.angular_velocity.y = Gxyz[1];
    imu_msg.angular_velocity.z = Gxyz[2];

    //publish data
    imu_pub.publish( &imu_msg );
    imu_pub_timer = millis() + imu_pub_rate;
  }

  //update line tracking sensors
  if(millis() > linetrackers_pub_timer)
  {
    //update data
    update_linetracking_sensors();

    //set data
    linetracker1_msg.data = linetracker1_data;
    linetracker2_msg.data = linetracker2_data;

    //publish data
    linetracker1_pub.publish( &linetracker1_msg );
    linetracker2_pub.publish( &linetracker2_msg );
    linetrackers_pub_timer = millis() + linetrackers_pub_rate;
  }
}

//led 1 routine function
void update_actuators()
{
  //update led state
  if(led13_state && millis() < cmd_led13_timer)
    digitalWrite(led13_pin, HIGH);
  else
    digitalWrite(led13_pin, LOW);
}

void setup()
{
  //node init
  nodeHandle.initNode();

  //setup ultrasonic sensor
  setup_ultrasonic_sensor();
  nodeHandle.advertise(ultrasonic_pub);

  //setup imu
  setup_imu();
  nodeHandle.advertise(imu_pub);

  //setup led
  pinMode(led13_pin, OUTPUT);
  nodeHandle.subscribe(led13_sub);  

  //setup linetracking sensors
  setup_linetracking_sensors();
  nodeHandle.advertise(linetracker1_pub);
  nodeHandle.advertise(linetracker2_pub);
}

void loop()
{
  //update actuators based subscribed data
  update_actuators();

  //update sensors and publish data
  update_sensors();

  //callback and send data
  nodeHandle.spinOnce();
}