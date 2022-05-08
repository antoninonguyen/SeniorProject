
//DRIVING THE MOTOR TEST
int motor_forward = 9;  
int motor_backward = 8;
int speedPin = 10;

//analog pin 0,1,2
void setup() {


   //for motor 1

    pinMode(motor_forward,OUTPUT);
    pinMode(motor_backward,OUTPUT);
    pinMode(speedPin,OUTPUT);

    
  Serial.begin(9600);

}

void loop() {
  // turn on motors
    digitalWrite(motor_forward,HIGH);
    digitalWrite(motor_backward,LOW);
    analogWrite(speedPin,255);
    delay(1000);

 
    //digitalWrite(motor_forward,LOW);
    //digitalWrite(motor_backward, LOW);
    //analogWrite(speedPin,255);
    //delay(5000);
    digitalWrite(motor_forward,LOW);
    digitalWrite(motor_backward,HIGH);
    analogWrite(speedPin,255);
    delay(300);

        digitalWrite(motor_forward,LOW);
    digitalWrite(motor_backward,LOW);
    analogWrite(speedPin,255);
    delay(3000);

    digitalWrite(motor_forward,LOW);
    digitalWrite(motor_backward,HIGH);
    analogWrite(speedPin,255);
    delay(1000);

    digitalWrite(motor_forward,HIGH);
    digitalWrite(motor_backward,LOW);
    analogWrite(speedPin,255);
    delay(300);

    //digitalWrite(motor_forward,HIGH);
    //digitalWrite(motor_backward,LOW);
    //analogWrite(speedPin,255);
    //delay(1000);

    //digitalWrite(motor_forward,LOW);
    //digitalWrite(motor_backward,HIGH);
    //analogWrite(speedPin,255);
    //delay(300);
    digitalWrite(motor_forward,LOW);
    digitalWrite(motor_backward, LOW);
    analogWrite(speedPin,255);
    delay(5000);


}
