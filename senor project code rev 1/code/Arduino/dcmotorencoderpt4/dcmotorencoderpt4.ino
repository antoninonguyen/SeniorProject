#define ENCA 2 // YELLOW
#define ENCB 3 // WHITE
#define PWM A2
#define IN1 A1 
#define IN2 A0
int pos = 0;
volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;
//int target = 0;
void setup() {
  Serial.begin(9600);
//  pinMode(ENCA,INPUT);
//  pinMode(ENCB,INPUT);
//  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
  
  pinMode(PWM,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  Serial.println("target pos");
}

void loop() {

  // set target position
  int target = 0;
//  int target = 255*sin(prevT/1e6);
  //Serial.print("target: ");
  //Serial.print(target);
//  int target = Serial.parseInt();
  // PID constants
  float kp = 1;
  float kd = 0.055;
  float ki = 0.0;

  // time difference
  long currT = micros();
  long T = millis();
  long t = T/1000;
  Serial.println(t);
  float deltaT = ((float) (currT - prevT))/( 1.0e6 );
  prevT = currT;

//  // Read the position
  int pos = 0; 
//  noInterrupts(); // disable interrupts temporarily while reading
  pos = posi;
//  interrupts(); // turn interrupts back on
  
  // error
  int e = pos - target;

  // derivative
  float dedt = (e-eprev)/(deltaT);

  // integral
  eintegral = eintegral + e*deltaT;

  // control signal
  float u = kp*e + kd*dedt + ki*eintegral;
//  Serial.print("pwr");
//  Serial.println(u);
  // motor power
  float pwr = fabs(u);
  if( pwr > 255 ){
    pwr = 255;
  }
  //Serial.println(pwr);
//  Serial.println(pwr);
  // motor direction
  int dir = 1;
  if(u<0){
    dir = -1;
  }

  // signal the motor
  setMotor(dir,pwr,PWM,IN1,IN2);


  // store previous error
  eprev = e;
  readEncoder();
  //Serial.println();
  //Serial.print("pos");
  //Serial.print(pos);
  //Serial.println();
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }  
}

void readEncoder(){
//  int b = digitalRead(ENCB);
  if(IN1 ==HIGH){
    posi++;
  }
  else{
    posi--;
  }
 
}
