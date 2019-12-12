/* Custom timer implementation
 * authors : Mourad, Johan
 * date : 12-12-2019
 * description : Simple non blocking timer
 */

//timer variables
struct TimerConfig
{
  unsigned long start_time = 0;
  unsigned long max_time = 1000;
  bool timer_running = false;
  bool timer_done = false;
};

//timer start
void timer_start(TimerConfig &timer)
{
  //start timer if not running
  if(timer.timer_running == false && timer.timer_done == false)
  {
    timer.start_time = millis();
    timer.timer_running = true;
  }
}

//timer update
void timer_update(TimerConfig &timer)
{
  //get difference between start and now
  unsigned long current_time = millis();
  unsigned long diff = current_time - timer.start_time;

  //check until timer is done
  if(timer.timer_running == true && diff > timer.max_time)
  {
    timer.timer_done = true;
    timer.timer_running = false;
  }
}

//timer reset/done
bool timer_isDone(TimerConfig &timer)
{
  if(timer.timer_done)
  {
    timer.timer_done = false;
    return true;
  }
  else
  {
    return false;
  }
}
