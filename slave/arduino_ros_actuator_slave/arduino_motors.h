//motor includes
#include            <Servo.h>

//steering motor
Servo steering_servo;
const int steering_motor_pin = 9;

//velocity motor pins
const int velocity_motor_forward_pin = 3;    
const int velocity_motor_backward_pin = 5;                                   

void setup_motors()
{
    //setup motor pins
    steering_servo.attach(steering_motor_pin);
    pinMode(velocity_motor_forward_pin,     OUTPUT);
    pinMode(velocity_motor_backward_pin,    OUTPUT);
}

void update_motors(int _velocity, int _steer, int _direction)
{
    //move steering motor
    steering_servo.writeMicroseconds(_steer);

    //move velocity motor
    if(_direction >= 1)
    {
        analogWrite(velocity_motor_backward_pin, 0); 
        analogWrite(velocity_motor_forward_pin, _velocity); 
    }
    else if(_direction <= -1)
    {
        analogWrite(velocity_motor_forward_pin, 0);   
        analogWrite(velocity_motor_backward_pin, _velocity); 
    }
    else if(_direction == 0)
    {
        analogWrite(velocity_motor_forward_pin, 0);
        analogWrite(velocity_motor_backward_pin, 0);
    }
}