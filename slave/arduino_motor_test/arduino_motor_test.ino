int motor_pin_p = 5;
int motor_pin_m = 6;

int enable_motor_pin = 11;

void setup()
{
  pinMode(motor_pin_p, OUTPUT); 
  pinMode(motor_pin_m, OUTPUT); 
  pinMode(enable_motor_pin, OUTPUT); 
}


void loop()
{
digitalWrite(enable_motor_pin, HIGH);
digitalWrite(motor_pin_p, LOW); 
digitalWrite(motor_pin_m, HIGH);

}
