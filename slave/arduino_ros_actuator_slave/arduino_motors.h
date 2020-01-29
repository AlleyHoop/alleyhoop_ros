#include            <Servo.h>

//sterring motor setup
Servo steering_motor;
const int steering_motor_pin = 9; 
int current_steer = 0;

//velocity motor pins
const int velocity_motor_pin = 10;    
int current_velocity = 0;                            

void setup_motors()
{
    //setup motor pins
    steering_motor.attach(steering_motor_pin);
    pinMode(velocity_motor_pin, OUTPUT);

}

void update_motors(int _direction, int _side)
{
    //brake
    if(_direction == 0)
    {
        velocity_motor_move(0);
    }

    //move backward
    if(_direction <= -1)
    {
        velocity_motor_move(250);
    }

    //move foward
    if(_direction >= 1)
    {
        velocity_motor_move(100);
    }


    //dont turn
    if(_side == 0)
    {
        steer_motor_move(1500);
    }

    //turn left
    if(_side >= 1)
    {
        steer_motor_move(1600);
    }

    //turn left
    if(_side <= -1)
    {
        steer_motor_move(1400);
    }


}

void velocity_motor_move(int _velocity)
{
    if(current_velocity != _velocity)
    {
        current_velocity = _velocity;
        analogWrite(velocity_motor_pin, 0);
        delay(200);
        analogWrite(velocity_motor_pin, current_velocity);
        delay(100);
    }
}

void steer_motor_move(int _steer)
{
    steering_motor.write(_steer);
}