//pins
const int tracingPin1 = 7;
const int tracingPin2 = 6;

//exported data
bool linetracker1_data;
bool linetracker2_data;

//setup function
void setup_linetracking_sensors()
{
    pinMode(tracingPin1,   INPUT);
    pinMode(tracingPin2,  INPUT);
}

//update function
void update_linetracking_sensors()
{
    linetracker1_data = digitalRead(tracingPin1);
    linetracker2_data = digitalRead(tracingPin2);
}