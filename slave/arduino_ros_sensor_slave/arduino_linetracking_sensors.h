//pins
const int trackerPin1 = A0;
const int trackerPin2 = A1;

//exported data
int linetracker1_data = 0;
int linetracker2_data = 0;

//setup function
void setup_linetracking_sensors()
{

}

//update function
void update_linetracking_sensors()
{
    linetracker1_data = analogRead(trackerPin1);
    linetracker2_data = analogRead(trackerPin2);
}

