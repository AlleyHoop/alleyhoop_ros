int ultrasonic_trigpin;
int ultrasonic_echopin;

void setup_ultrasonic_sensor()
{
    ultrasonic_trigpin = 2;
    ultrasonic_echopin = 4;
    pinMode(ultrasonic_trigpin, OUTPUT);
    pinMode(ultrasonic_echopin, INPUT);
}

void update_ultrasonic_sensor(long &distance)
{
    //read ultrasoon
    long duration;
    digitalWrite(ultrasonic_trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonic_trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonic_trigpin, LOW);
    duration=pulseIn(ultrasonic_echopin, HIGH);
    distance=duration*0.032/2;
}
