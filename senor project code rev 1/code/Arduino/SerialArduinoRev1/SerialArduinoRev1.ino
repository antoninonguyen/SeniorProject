#define numOfValsRec 3
#define digitsPerValRec 3


int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString;

//front motor turn
int motor_left = A1;  
int motor_right = A0;
int SpeedPin1 = A2;
int SteeringCount = 0;
void setup() {
  //front motor turn
  pinMode(motor_left,OUTPUT);
  pinMode(motor_right,OUTPUT);
  pinMode(SpeedPin1,OUTPUT);
  
  Serial.begin(9600);
}

void receiveData() 
{
  while (Serial.available()) 
  {
    char c = Serial.read();
    if (c == '$') 
    {
      counterStart = true;
    }
    if (counterStart)
    {
      if (counter < stringLength) 
      {
      receivedString = String(receivedString + c);
      counter++;
      }
    }
    
      if (counter >= stringLength) 
      {
        for (int i = 0; i < numOfValsRec; i++) 
        {
          int num = (i * digitsPerValRec) + 1;
          valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
        }
        receivedString = "";
        counter = 0;
        counterStart = false;
        
      }
  }
}


void loop() 
{
  if (Serial.available()>0) 
  {
    receiveData();
    steering(valsRec[0]);
    Serial.print("helo jetson");
  }
   
  
//  Serial.println(valsRec[0]);
//  print(valsRec[0]);
//  Serial.begin(9600);
//  if (valsRec[0] == 0)
////    Serial.println(valsRec[0]);
////    Serial.flush();
//    if (Serial.available()>0) receiveData();
//    if (valsRec[1] == 1)
//    {
//      steering(valsRec[2]);
//      Serial.println(valsRec[2]);
//      Serial.end();
////      SteeringCount++;
////      Serial.print(counter);
//    }
////  Serial.println(valsRec[2]);
  
}

void steering(int cx)
{
  if (cx < 480)
  {
    digitalWrite(motor_left,HIGH);
    digitalWrite(motor_right,LOW);
    analogWrite(SpeedPin1,255);
  } 
  else if (cx > 480)
  {
    digitalWrite(motor_left,LOW);
    digitalWrite(motor_right,HIGH);
    analogWrite(SpeedPin1,255);
  }
  else
  {
    cx = 0;
    digitalWrite(motor_left,LOW);
    digitalWrite(motor_right,LOW);
    analogWrite(SpeedPin1,255);
  }
}
