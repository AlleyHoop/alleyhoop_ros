#include <Servo.h>
//#include <ros.h>
//#include <std_msgs/String.h>

//structs
struct CarConfig
{
  int steer;
  int velocity;
  bool brake;
};

//motors
Servo                myservo;
Servo                    esc;

//ultrasoon
int trigPin = 2;
int echoPin = 4;

//tracing pins
const int tracingPinLeft =     7;
const int tracingPinRight =    6;

//variables
CarConfig currentConf;

//ros
/*ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char txt[10] = "I am slave";
*/

void setup()
{
 //ultrasoon
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
  
 //tracing pins
 pinMode(tracingPinLeft, INPUT);
 pinMode(tracingPinRight, INPUT);

 //servo init
 myservo.attach(8);
 esc.attach(9);

 //configuration
 currentConf.velocity = 1500;
 currentConf.steer = 1500;
 currentConf.brake = false;
 
 //communication
 Serial.begin (9600);
}

CarConfig makeDecision(bool ultrasoon, bool tracker1, bool tracker2)
{
  CarConfig conf;
  conf.velocity = 1500;
  conf.steer = 1500;
  conf.brake = false;

  // 1: do nothing
  if(!ultrasoon && !tracker1 && !tracker2)
  {
    conf.velocity = 1500;
    conf.steer = 1500;
    return conf;
  }

  // 2: go backwards
  if(ultrasoon && !tracker1 && !tracker2)
  {
    conf.velocity = 1400;
    conf.steer = 1500;
    return conf;
  }

  // 3: go fowards left
  if(!ultrasoon && tracker1 && !tracker2)
  {
    conf.velocity = 1600;
    conf.steer = 1250;
    return conf;
  }

  // 4: go backwards right
  if(ultrasoon && tracker1 && !tracker2)
  {
    conf.velocity = 1400;
    conf.steer = 1750;
    return conf;
  }

  // 5: go fowards right
  if(!ultrasoon && !tracker1 && tracker2)
  {
    conf.velocity = 1600;
    conf.steer = 1750;
    return conf;
  }

  // 6: go backwards left
  if(ultrasoon && !tracker1 && tracker2)
  {
    conf.velocity = 1400;
    conf.steer = 1250;
    return conf;
  }

  // 7: go fowards
  if(!ultrasoon && tracker1 && tracker2)
  {
    conf.velocity = 1600;
    conf.steer = 1500;
    return conf;
  }

  // 8: go fowards
  if(ultrasoon && tracker1 && tracker2)
  {
    conf.velocity = 1400;
    conf.steer = 1500;
    return conf;
  }

  return conf;
}

bool ultrasoon(int val)
{
  long duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance=duration*0.032/2;
  delay(10);

  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance < val)
  {
    return true;
  }

  return false;
}

void loop(){
  
  // make decision
  CarConfig newConf = makeDecision(ultrasoon(30), digitalRead(tracingPinLeft), digitalRead(tracingPinRight));

  //brake when direction switch
  if(newConf.velocity > 1500 && currentConf.velocity < 1500)
  { 
    newConf.brake = true;
  }
  if(newConf.velocity < 1500 && currentConf.velocity > 1500)
  {
    newConf.brake = true;
  }

  //set new config
  currentConf = newConf;

  //control motors
  if(!currentConf.brake)
  {
    esc.writeMicroseconds(currentConf.velocity);
    myservo.writeMicroseconds(currentConf.steer);
  }
  else
  {
    esc.writeMicroseconds(1500);
    myservo.writeMicroseconds(1500); 
    delay(1000);
  }

  //debug data
  Serial.println("configuration:");
  Serial.println(currentConf.velocity);
  Serial.println(currentConf.steer);
  if(currentConf.brake) 
  {
      Serial.println("brake"); 
  }
  else 
  {
      Serial.println("free");
  }
  
  
  //ros spin
  /*
  str_msg.data = txt;
  chatter.publish( &str_msg );
  nh.spinOnce();
  */
}
