#define ENCA 2 // YELLOW
#define ENCB 3 // WHITE
#define PWM A2
#define IN1 A1 
#define IN2 A0
//int pos = 0;
volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;
void setup() 
{
  Serial.begin(9600);

  pinMode(PWM,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  Serial.println("target pos");


}

void loop() 
{


}

void Steering(targ)
{
  
}
