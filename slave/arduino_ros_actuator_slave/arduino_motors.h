#include            <Servo.h>

//sterring motor setup
Servo steering_motor;
const int steering_motor_pin = 9; 
int current_steer = 0;

//velocity motor pins
Servo velocity_motor;
const int velocity_motor_pin = 10;    
int current_velocity = 0;      

//motor control function
void velocity_motor_move(int _velocity)
{
    if(current_velocity != _velocity)
    {
        current_velocity = _velocity;
        velocity_motor.writeMicroseconds(1500);
        delay(200);
        velocity_motor.writeMicroseconds(current_velocity);
        delay(50);
    }
}

//servo control function
void steer_motor_move(int _steer)
{
    if(current_steer != _steer)
    {
        current_steer = _steer;
        steering_motor.writeMicroseconds(current_steer);
    }
}

//setup function
void setup_motors()
{
    //setup motor pins
    velocity_motor.attach(velocity_motor_pin);
    steering_motor.attach(steering_motor_pin);

    //set motors to default state
    velocity_motor_move(1500);

}

//update function
void update_motors(int _direction, int _side)
{
    //brake
    if(_direction == 0)
    {
        velocity_motor_move(1500);
    }

    //move backward
    if(_direction <= -1)
    {
        velocity_motor_move(1400);
    }

    //move foward
    if(_direction >= 1)
    {
        velocity_motor_move(1600);
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

