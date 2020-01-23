//pins
const int ultrasonic_trigpin = 2;
const int ultrasonic_echopin = 4;

//export data
long ultrasonic_sensor_data = 0;

//setup function
void setup_ultrasonic_sensor()
{
    pinMode(ultrasonic_trigpin, OUTPUT);
    pinMode(ultrasonic_echopin, INPUT);
}

//update function
void update_ultrasonic_sensor()
{
    //read ultrasoon
    long duration;
    digitalWrite(ultrasonic_trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonic_trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonic_trigpin, LOW);
    duration=pulseIn(ultrasonic_echopin, HIGH);
    ultrasonic_sensor_data=duration*0.032/2;
}
