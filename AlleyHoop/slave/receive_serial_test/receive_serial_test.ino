String currentData = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  String txt = "";
  
  while (Serial.available())
  {
    delay(3);
    if (Serial.available() > 0)
    {
      char c = Serial.read();
      txt += c;
    }
  }
 
  if(txt.equals("true"))
  {
    digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(12, LOW);
  }
}
