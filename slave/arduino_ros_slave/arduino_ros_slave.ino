#include <ros.h>
#include <std_msgs/String.h>

//ros node (only one possible on arduino)
ros::NodeHandle nodeHandle;

//publisher exmpl
std_msgs::String str_msg;
ros::Publisher serial_publisher("arduino_pub", &str_msg);

//subsriber exmpl
void messageCb( const std_msgs::String& toggle_msg){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}
ros::Subscriber<std_msgs::String> serial_subscriber("arduino_sub", &messageCb );

void setup()
{
  //setup led
  pinMode(7, OUTPUT);
  
  //node init
  nodeHandle.initNode();

  //subscriber
  nodeHandle.subscribe(serial_subscriber);
  nodeHandle.advertise(serial_publisher);
}

//ros spin
void loop(){

  //setup data to publish
  char txt[11] = "I am arduino";
  str_msg.data = txt;

  //callback and send data
  serial_publisher.publish( &str_msg );
  nodeHandle.spinOnce();
  delay(1);
}
