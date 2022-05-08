#define numOfValsRec 2
#define digitsPerValRec 3

int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString;

//rear motor
int SpeedPin = 10;
int in1 = 9;
int in2 = 8;

//front motor turn
int motor_left = A0;  
int motor_right = A1;
int SpeedPin1 = A2;


//constants
int cx = 0;

void setup() {
  //rear motor
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(SpeedPin,OUTPUT);

  //front motor turn
  pinMode(motor_left,OUTPUT);
  pinMode(motor_right,OUTPUT);
  pinMode(SpeedPin1,OUTPUT);
  
  digitalWrite(motor_left,LOW);
  digitalWrite(motor_right,LOW);
  analogWrite(SpeedPin1,255);
  _Stop();
  
  Serial.begin(9600);
}

void receiveData() {
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

    }
  }



}

void loop() {

  digitalWrite(motor_left,LOW);
  digitalWrite(motor_right,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  receiveData();
  if (valsRec[0] == 000)
  {
    _Forward();
//    _Forward();
    steering(valsRec[1]);
  }

  else
  {
    steering(0);
    _Stop();
  }
  


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

//Forward Drive Motor
String _Forward()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(SpeedPin,200);
  //Serial.println("MOVE_FORWARD");
  return "FORWARD";
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
