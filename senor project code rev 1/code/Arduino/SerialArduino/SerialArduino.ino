#define numOfValsRec 3
#define digitsPerValRec 3


int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString;

//front motor turn
int motor_left = A0;  
int motor_right = A1;
int SpeedPin1 = A2;

void setup() {
  //front motor turn
//  pinMode(motor_left,OUTPUT);
//  pinMode(motor_right,OUTPUT);
//  pinMode(SpeedPin1,OUTPUT);
  
  pinMode(13, OUTPUT);
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
  if (Serial.available()>0) receiveData();
  
  if (valsRec[2] == 27)
  {
    digitalWrite(13,HIGH);
  }
  else if (valsRec[0] == 26)
  {
    digitalWrite(13,LOW);
  }
  else if (valsRec[1] == 25)
  {
    digitalWrite(13,HIGH);
    
  }
  
  int i = 0;
  while (i=0,i<=2,i++)
  {
    valsRec[i]=0;
  }
//  Serial.flush();
//  digitalWrite(motor_left,LOW);
//  digitalWrite(motor_right,LOW);
//  digitalWrite(in1,LOW);
//  digitalWrite(in2,LOW);
//  receiveData();
//  if (valsRec[0] == 000)
//  {
//    _Forward();
////    _Forward();
//    steering(valsRec[1]);
//  }
//
//  else
//  {
//    steering(0);
//    _Stop();
//  }
//  
//

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
