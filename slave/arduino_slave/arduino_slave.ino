#include <Servo.h>

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
const int defaultVal = 1500;
const int fowardVal = 1600;
const int backwardVal = 1400;
const int leftVal = 1250;
const int rightVal = 1750;


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
 currentConf.velocity = defaultVal;
 currentConf.steer = defaultVal;
 currentConf.brake = false;
 
 //communication
 Serial.begin (9600);
}

CarConfig makeDecision(bool ultrasoon, bool tracker1, bool tracker2)
{
  CarConfig conf;
  conf.velocity = defaultVal;
  conf.steer = defaultVal;
  conf.brake = false;

  // 1: do nothing
  if(!ultrasoon && !tracker1 && !tracker2)
  {
    conf.velocity = defaultVal;
    conf.steer = defaultVal;
    return conf;
  }

  // 2: go backwards
  if(ultrasoon && !tracker1 && !tracker2)
  {
    conf.velocity = backwardVal;
    conf.steer = defaultVal;
    return conf;
  }

  // 3: go fowards left
  if(!ultrasoon && tracker1 && !tracker2)
  {
    conf.velocity = fowardVal;
    conf.steer = leftVal;
    return conf;
  }

  // 4: go backwards right
  if(ultrasoon && tracker1 && !tracker2)
  {
    conf.velocity = backwardVal;
    conf.steer = rightVal;
    return conf;
  }

  // 5: go fowards right
  if(!ultrasoon && !tracker1 && tracker2)
  {
    conf.velocity = fowardVal;
    conf.steer = rightVal;
    return conf;
  }

  // 6: go backwards left
  if(ultrasoon && !tracker1 && tracker2)
  {
    conf.velocity = backwardVal;
    conf.steer = leftVal;
    return conf;
  }

  // 7: go fowards
  if(!ultrasoon && tracker1 && tracker2)
  {
    conf.velocity = fowardVal;
    conf.steer = defaultVal;
    return conf;
  }

  // 8: go backwards
  if(ultrasoon && tracker1 && tracker2)
  {
    conf.velocity = backwardVal;
    conf.steer = defaultVal;
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
  if(newConf.velocity > defaultVal && currentConf.velocity < defaultVal)
  { 
    newConf.brake = true;
  }
  if(newConf.velocity < defaultVal && currentConf.velocity > defaultVal)
  {
    newConf.brake = true;
  }

  //set new config
  currentConf = newConf;

  //control motors
  if(!currentConf.brake)
  {
    //move car
    esc.writeMicroseconds(currentConf.velocity);
    myservo.writeMicroseconds(currentConf.steer);
  }
  else
  {
    //brake and wait alittle
    esc.writeMicroseconds(defaultVal);
    myservo.writeMicroseconds(defaultVal); 
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
}
