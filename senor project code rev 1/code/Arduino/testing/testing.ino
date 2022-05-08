#define numOfValsRec 2
#define digitsPerValRec 3

int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString = "";
bool stringComplete = false;

int Echo1 = 2; //Left Echo
int Trig1 = 3; //Left Trig
int Echo2 = 4; //Center Echo
int Trig2 = 5; //Center Trig
int Echo3 = 6; //Right Echo
int Trig3 = 7; //Right Trig

int SpeedPin = 10;
int in1 = 9;
int in2 = 8;
int Left_Dist = 0, Right_Dist = 0, Center_Dist = 0;


void setup() {
  //led
  pinMode(13, OUTPUT);
  //ultra sonic sensor
  pinMode(Echo1, INPUT);
  pinMode(Trig1, OUTPUT);
  pinMode(Echo2, INPUT);
  pinMode(Trig2, OUTPUT);
  pinMode(Echo3, INPUT);
  pinMode(Trig3, OUTPUT);
  //motor pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(SpeedPin, OUTPUT);
  Serial.begin(9600);
  while(!Serial)
    {
      ;
    }
  //this will send serial data until data is available to recieve it
  while (Serial.available()<=0)
  {
    sendStatus();
    delay (300);
  }
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
      //stringComplete = true;

    }
  }
}

void sendStatus()
{
  
  Left_Dist = Left_test();
  delay(10);
  Center_Dist = Center_test();
  delay(10);
  Right_Dist = Right_test();
  delay(10);
  Serial.println("Left_Dist\tCenter_Dist\tRigth_Dist\tStatus\n");
  Serial.print(Left_Dist);
  Serial.print("cm\t\t");
  Serial.print(Center_Dist);
  Serial.print("cm\t\t");
  Serial.print(Right_Dist);
  Serial.print("cm\t\t");
}

//Forward Drive Motor
void _Forward()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(SpeedPin,255);
  Serial.println("MOVE_FORWARD");
}
//Backward Drive Motor
void _Back()
{ 
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(SpeedPin,255);
  Serial.println("MOVE_BACKWARD"); 
}
//Stop Drive Motor
void _Stop()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(SpeedPin,255);
  Serial.println("MOVE_STOP"); 
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

void loop() 
{
  if(stringComplete)
  {
    
    if (valsRec[1] == 255)
    {
    digitalWrite(13,HIGH);
    Serial.println("pin 13 is HIGH");
    }
    else if (valsRec[1] == 000)
    {
      digitalWrite(13,LOW);
      Serial.println("pin 13 is LOW");
    }
  }

  //RESET STRING
  stringComplete = false;
  


 
}

    //if (Serial.available()>0 receiveData();
