#define numOfValsRec 3
#define digitsPerValRec 3
//sensor
//int Echo1 = 2; //Left Echo
//int Trig1 = 3; //Left Trig
//int Echo2 = 4; //Center Echo
//int Trig2 = 5; //Center Trig
//int Echo3 = 6; //Right Echo
//int Trig3 = 7; //Right Trig
//int Left_Dist = 0, Right_Dist = 0, Center_Dist = 0;
//rear motor
//int SpeedPin = 10;
//int in1 = 9;
//int in2 = 8;


char left = 'l';
char right = 'r';
int motor_left = A0;  
int motor_right = A1;
int SpeedPin1 = A2;
int SteeringCount = 0;


void setup() {
  //ultrasonic sensors 1,2,3
//  pinMode(Echo1, INPUT);
//  pinMode(Trig1, OUTPUT);
//  pinMode(Echo2, INPUT);
//  pinMode(Trig2, OUTPUT);
//  pinMode(Echo3, INPUT);
//  pinMode(Trig3, OUTPUT);
  //rear motor
//  pinMode(in1,OUTPUT);
//  pinMode(in2,OUTPUT);
//  pinMode(SpeedPin,OUTPUT);



  
  pinMode(motor_left,OUTPUT);
  pinMode(motor_right,OUTPUT);
  pinMode(SpeedPin1,OUTPUT);
  Serial.begin(9600);

}

void loop() 
{
//  steering('l');
//  delay(3000);
//  steering('r');
//  delay(3000);
  while (Serial.available()) 
  {
    String value = "";
    char c = Serial.read();
    steering(c);
    c='e';
//    
////    Serial.print("data = ");
////    Serial.print(c);
////    Serial.println();
////    Serial.flush();
//    
  }
}

void steering(char steeringVal)
{
  char value = steeringVal;
  if (value == 'l')
  {
    Serial.print("l");
    Serial.println();
    Serial.flush();
    digitalWrite(motor_left,HIGH);
    digitalWrite(motor_right,LOW);
    analogWrite(SpeedPin1,255);
  } 
  
  else if (value == 'r')
  {
    Serial.print('r');
    Serial.println();
    Serial.flush();
    digitalWrite(motor_left,LOW);
    digitalWrite(motor_right,HIGH);
    analogWrite(SpeedPin1,255);
  }
  else if (value == 's')
  {
    Serial.print("s");
    Serial.println();
    Serial.flush();
    digitalWrite(motor_left,LOW);
    digitalWrite(motor_right,LOW);
    analogWrite(SpeedPin1,255);
  }
  else
  {
    return;
  }
}


//void sendStatus()
//{
//  char buffer[50];
////  inputValueUSS = [Left_test(),Center_test(),Right_test];
//  sprintf (buffer, "leftSensor  %d  CenterSensor  %d  rightSensor  %d", Left_test(),Center_test(), Right_test());
//  Serial.println(buffer);
//}

//void receiveData() 
//{
//  while (Serial.available()) {
//    char c = Serial.read();
//    if (c == '$') {
//      counterStart = true;
//    }
//    if (counterStart){
//      if (counter < stringLength) {
//      receivedString = String(receivedString + c);
//      counter++;
//      }
//    }
//    
//    if (counter >= stringLength) {
//      for (int i = 0; i < numOfValsRec; i++) {
//        int num = (i * digitsPerValRec) + 1;
//        valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
//      }
//      receivedString = "";
//      counter = 0;
//      counterStart = false;
//      stringComplete = true;
//
//    }
//  }
//}

////Left Ultrasonic Sensor
//int Left_test()
//{
//  digitalWrite(Trig1, LOW);
//  delayMicroseconds(2);
//  digitalWrite(Trig1, HIGH);
//  delayMicroseconds(20);
//  digitalWrite(Trig1, LOW);
//  float Fdist = pulseIn(Echo1, HIGH);
//  delay(10);
//  Fdist = Fdist/ 29 / 2;
//  return (int)Fdist;
//}
////Center Ultrasonic Sensor
//int Center_test()
//{
//  digitalWrite(Trig2, LOW);
//  delayMicroseconds(2);
//  digitalWrite(Trig2, HIGH);
//  delayMicroseconds(20);
//  digitalWrite(Trig2, LOW);
//  float Fdist = pulseIn(Echo2, HIGH);
//  delay(10);
//  Fdist = Fdist/ 29 / 2;
//  return (int)Fdist;
//}
////Right Ultrasonic Sensor
//int Right_test()
//{
//  digitalWrite(Trig3, LOW);
//  delayMicroseconds(2);
//  digitalWrite(Trig3, HIGH);
//  delayMicroseconds(20);
//  digitalWrite(Trig3, LOW);
//  float Fdist = pulseIn(Echo3, HIGH);
//  delay(10);
//  Fdist = Fdist/ 29 / 2;
//  return (int)Fdist;
//}
//
////Forward Drive Motor
//String _Forward()
//{
//  digitalWrite(in1,HIGH);
//  digitalWrite(in2,LOW);
//  analogWrite(SpeedPin,255);
//  //Serial.println("MOVE_FORWARD");
//  return "FORWARD";
//}
////Backward Drive Motor
//String _Back()
//{ 
//  digitalWrite(in1,LOW);
//  digitalWrite(in2,HIGH);
//  analogWrite(SpeedPin,255);
////  Serial.println("MOVE_BACKWARD"); 
//  return "BACKWARD";
//}
