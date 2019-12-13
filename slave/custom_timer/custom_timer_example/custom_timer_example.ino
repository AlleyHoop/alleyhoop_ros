#include "custom_arduino_timer.h"

TimerConfig timer1;
bool state = false;

//arduino setup
void setup() {

  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  //setup timer
  timer1.max_time = 1000;
}

 
//loop
void loop() {

  //run timer
  timer_start(timer1);
  timer_update(timer1);

  //check if timer done then reset
  if(timer_isDone(timer1))
  {
    if(state)
    {
      state = false;
    }
    else
    {
      state = true;
    }
    timer_reset(timer1);
  }

  digitalWrite(13, state);

}
