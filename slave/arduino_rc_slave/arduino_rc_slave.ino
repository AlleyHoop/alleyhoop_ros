#include <Servo.h>
#include <ros.h>
#include <std_msgs/String.h>

//motors
Servo                myservo;
Servo                    esc;

//tracing pins
const int tracingPin =     7;
const int tracingPin1 =    6;

//variables
int steer             = 1500;
int velocity          = 1500;

//ros
ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char txt[10] = "I am slave";

void setup()
{
 //tracing pins
 pinMode(tracingPin, INPUT);
 pinMode(tracingPin1, INPUT);

 //servo init
 myservo.attach(8);
 esc.attach(9);

 //communication
 Serial.begin (9600);
}

void linetracking()
{
   if(digitalRead(tracingPin) == true && digitalRead(tracingPin1) == true)
  {
    steer = 1500;
    velocity = 1600;
  }
  if(digitalRead(tracingPin) == false && digitalRead(tracingPin1) == true)
  {
    steer = 1750;
    velocity = 1600;
  }
  if(digitalRead(tracingPin) == true && digitalRead(tracingPin1) == false)
  {
    steer = 1250;
    velocity = 1600;
  }
  if(digitalRead(tracingPin) == false && digitalRead(tracingPin1) == false)
  {
    steer = 1500;
    velocity = 1500;
  }
}

void loop(){
  //control motors
  esc.writeMicroseconds(velocity);
  myservo.writeMicroseconds(steer);

  //update line tracker
  linetracking();

  //ros spin
  str_msg.data = txt;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1000);
}
