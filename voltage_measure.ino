#include <Servo.h>
Servo myservo;             
int initial_position = 0;   
int LDR1 = A3;          //connect The LDR1 on Pin A0
int LDR2 = A4;          //Connect The LDR2 on pin A1
int servopin=9; 
int total = 0;
void setup()
{
  Serial.begin(115200);
  myservo.attach(servopin);  
  pinMode(LDR1, INPUT);   
  pinMode(LDR2, INPUT);
  myservo.write(initial_position);   //Move servo at 90 degree
  delay(2000);
}

double Light (int RawADC0)
{
  double Vout=RawADC0*0.0048828125;
  int lux=500/(10*((5-Vout)/Vout));
  return lux;
}
void loop()
{
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println((String)"Voltage: "+voltage+"V");
  Serial.println((String)"Light Intensity: "+int(Light(analogRead(A1)))+"L");
  int temp = analogRead(A2);    //Read the analog pin
  temp = temp * 0.48828125;   // convert output (mv) to readable celcius
  Serial.print((String)"Temperature: "+temp+"F");
  int R1 = analogRead(LDR1); // read  LDR 1
  int R2 = 545; // read  LDR 2
  int diff1= abs(R1 - R2);   
  int diff2= abs(R2 - R1);
  
  if((diff1 <= error) || (diff2 <= error)) {
    
  } else {    
    if(R1 > R2)
    {
      initial_position = --initial_position;  
    }
    if(R1 < R2) 
    {
      initial_position = ++initial_position; 
    }
  }
  myservo.write(initial_position); 
  delay(1000);
}
