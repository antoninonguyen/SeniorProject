int Echo1 = 2; //Left Echo
int Trig1 = 3; //Left Trig

int inputValue = 0; //store read value
int outputPin = 13; //output pin activation port

String inputString = "";
boolean stringComplete = false;

void setup() {
  pinMode(Echo1, INPUT);
  pinMode(Trig1, OUTPUT);
  //pinMode(outputPin, OUTPUT);
  //digitalWrite(outputPin, HIGH);
  Serial.begin(9600);
  while(!Serial)
    {
      ;
    }
  //this will send serial data until data is available to recieve it
//  while (Serial.available()<=0)
//  {
//    sendStatus();
//    delay (500);
//  }

}

void loop() 
{
  if (stringComplete)
  {
    if (inputString.startsWith("status"))
    {
      sendStatus();
    }
    else if (inputString.startsWith("set"))
    {
      if (inputString.indexOf("on") > -1)
      {
        digitalWrite(outputPin,HIGH);
        Serial.println("led turned on");
        Serial.println(inputString.indexOf("on"));
      }
      else if (inputString.indexOf("off") > -1)
      {
        digitalWrite(outputPin,LOW);
        Serial.println("led turned off");
      }
      else
      {
        Serial.println("invalid set command");
      }
    }
    else
    {
      Serial.println("invalid command");
    }
  }
  //reset string
  stringComplete = false;
  inputString = "";
  delay(10); 
  
  if (Serial.available()>0) serialEvent();
}

void sendStatus()
{
  char buffer[50];
  inputValue = Left_test();
  sprintf (buffer, "Distance %d is %d", Left_test(), inputValue);
  Serial.println(buffer);
}

void serialEvent()
{
  while (Serial.available())
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }
}
int Left_test()
{
  int x = 1;
  return x;
//  digitalWrite(Trig1, LOW);
//  delayMicroseconds(2);
//  digitalWrite(Trig1, HIGH);
//  delayMicroseconds(20);
//  digitalWrite(Trig1, LOW);
//  float Fdist = pulseIn(Echo1, HIGH);
//  delay(10);
//  Fdist = Fdist/ 29 / 2;
//  return (int)Fdist;

}
