#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

void blinkLed()
{
  digitalWrite(7, HIGH);   // blink the led
  delay(500);
  digitalWrite(7, LOW);
}

//ros node
ros::NodeHandle nh;

//publisher exmpl
std_msgs::String str_msg;
ros::Publisher serial_publisher("arduino_slave_pub", &str_msg);

//subsriber exmpl
void messageCb( const std_msgs::Empty& toggle_msg){
  blinkLed();
}
ros::Subscriber<std_msgs::Empty> sub("arduino_slave_sub", &messageCb );

//ros
void setup()
{
  //led
  pinMode(7, OUTPUT);
  
  //node init
  nh.initNode();

  //subscriber
  nh.subscribe(sub);
}

//ros spin
void loop(){

  //publish data
  char txt[11] = "I am slave";
  str_msg.data = txt;
  serial_publisher.publish( &str_msg );

  //callback and send data
  nh.spinOnce();
  delay(1);
}
