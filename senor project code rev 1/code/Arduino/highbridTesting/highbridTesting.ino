#define numOfValsRec 2
#define digitsPerValRec 3
#define numOfValsRecUSS 3

int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString = "";
bool stringComplete = false;
//sensor
int Echo1 = 2; //Left Echo
int Trig1 = 3; //Left Trig
int Echo2 = 4; //Center Echo
int Trig2 = 5; //Center Trig
int Echo3 = 6; //Right Echo
int Trig3 = 7; //Right Trig
int Left_Dist = 0, Right_Dist = 0, Center_Dist = 0;
//rear motor
int SpeedPin = 10;
int in1 = 9;
int in2 = 8;
//int Left_Dist = 0, Right_Dist = 0, Center_Dist = 0;

int inputValueUSS[numOfValsRecUSS]; //store read value
int outputPin = 13; //output pin activation port

String cartState = "";
String USSactivated = "";



void setup() {
  //ultrasonic sensors 1,2,3
  pinMode(Echo1, INPUT);
  pinMode(Trig1, OUTPUT);
  pinMode(Echo2, INPUT);
  pinMode(Trig2, OUTPUT);
  pinMode(Echo3, INPUT);
  pinMode(Trig3, OUTPUT);
  //led
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, HIGH);
  
  Serial.begin(9600);
  Serial.flush();
  Serial.end();
  delay(3000);
  Serial.begin(9600);
  while(!Serial)
    {
      ;
    }
  //this will send serial data until data is available to recieve it
  while (Serial.available()<=0)
  {
    sendStatus();
    delay (500);
  }

}

void loop() 
{
  //RECEIVED DATA PART
  if (Serial.available()>0) receiveData();
//  Serial.println("start of loop");
//  Serial.println(valsRec[0]);
//  Serial.println(valsRec[1]);
  if (stringComplete)
  {
    if (valsRec[0] == 000)
    {
      sendStatus();
    }
    else if (valsRec[0] == 255)
    {
      if (valsRec[1] == 255)
      {
        digitalWrite(13,HIGH);
        Serial.println("pin 13 is HIGH");
        
      }
      else if (valsRec[1] == 000)
      {
        digitalWrite(outputPin,LOW);
        Serial.println("led turned off");
      }
      else
      {
        Serial.println("invalid set reading");
      }
    }
    else
    {
      Serial.println("invalid command");
    }
  }
  //reset string
  stringComplete = false;
  receivedString = "";
  Serial.flush();
  delay(10); 
//  Serial.println("end of loop");
//  Serial.println(valsRec[0]);
//  Serial.println(valsRec[1]);
  Left_Dist = Left_test();
  delay(10);
  Center_Dist = Center_test();
  delay(10);
  Right_Dist = Right_test();
  delay(10);
  cartState = CartState(Left_Dist, Center_Dist, Right_Dist);
  Serial.print("Left_dist ");
  Serial.print(Left_Dist);
  Serial.print("Center_dist ");
  Serial.print(Center_Dist);
  Serial.print("Right_dist ");
  Serial.print(Right_Dist);
  Serial.print("cartState ");
  Serial.print(cartState);
}

String CartState(int Left_Dist, int Center_Dist, int Right_Dist)
{
  String cartState = "";
  String USSactivated = "";
  if(Center_Dist<=80)
        {
           cartState = _Stop();
           USSactivated = "CENTER";
           delay(500);
        }
  else if(Left_Dist<=80)
  {
     cartState = _Stop();
     USSactivated = "LEFT";
     delay(500);
  }
  else if(Right_Dist<=80)
  {
    cartState = _Stop();
    USSactivated = "RIGHT";
    delay(500);
  }
  else
  {
     cartState = _Forward();
  }
  String cartStateString = cartState + "\t" +USSactivated;
  return  cartStateString;
}

void sendStatus()
{
  char buffer[50];
//  inputValueUSS = [Left_test(),Center_test(),Right_test];
  sprintf (buffer, "leftSensor  %d  CenterSensor  %d  rightSensor  %d", Left_test(),Center_test(), Right_test());
  Serial.println(buffer);
}

void receiveData() 
{
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '$') {
      counterStart = true;
    }
    if (counterStart){
      if (counter < stringLength) {
      receivedString = String(receivedString + c);
      counter++;
      }
    }
    
    if (counter >= stringLength) {
      for (int i = 0; i < numOfValsRec; i++) {
        int num = (i * digitsPerValRec) + 1;
        valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
      }
      receivedString = "";
      counter = 0;
      counterStart = false;
      stringComplete = true;

    }
  }
}

//Distance Measurement

//Left Ultrasonic Sensor
int Left_test()
{
  digitalWrite(Trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig1, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig1, LOW);
  float Fdist = pulseIn(Echo1, HIGH);
  delay(10);
  Fdist = Fdist/ 29 / 2;
  return (int)Fdist;
}
//Center Ultrasonic Sensor
int Center_test()
{
  digitalWrite(Trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig2, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig2, LOW);
  float Fdist = pulseIn(Echo2, HIGH);
  delay(10);
  Fdist = Fdist/ 29 / 2;
  return (int)Fdist;
}
//Right Ultrasonic Sensor
int Right_test()
{
  digitalWrite(Trig3, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig3, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig3, LOW);
  float Fdist = pulseIn(Echo3, HIGH);
  delay(10);
  Fdist = Fdist/ 29 / 2;
  return (int)Fdist;
}

//Forward Drive Motor
String _Forward()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(SpeedPin,255);
  //Serial.println("MOVE_FORWARD");
  return "FORWARD";
}
//Backward Drive Motor
String _Back()
{ 
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(SpeedPin,255);
//  Serial.println("MOVE_BACKWARD"); 
  return "BACKWARD";
}
//Stop Drive Motor
String _Stop()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(SpeedPin,255);
//  Serial.println("MOVE_STOP");
  return "STOPPED"; 
}

//trash functions

//void serialEvent()
//{
//  while (Serial.available())
//  {
//    char inChar = (char)Serial.read();
//    inputString += inChar;
//    if (inChar == '\n')
//    {
//      stringComplete = true;
//    }
//  }
//}
