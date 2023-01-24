#include <SoftwareSerial.h> 
SoftwareSerial Bluetooth(2, 3);  // ((RX | TX))  ***(connect 2 to TX of bluetooth and 3 to RX of bluetooth )***


const int flexPin1 = A0;    
const int flexPin2 = A1;
const int flexPin3 = A2;                                               //initializing flex sensor pins
const int flexPin4 = A3;


const float VCC = 5;    
const float R_DIV = 47000.0; 
const float fr1 = 25000.0;                                               //calibrating each flex sensor
const float br1 = 120000.0; 
const float fr2 = 30000.0; 
const float br2 = 150000.0;
const float fr3 = 25000.0; 
const float br3 = 75000.0; 
const float fr4 = 20000.0; 
const float br4 = 130000.0;
/* 
 *  ACCELEROMETER 
 */
const int yInput = A4;
const int xInput = A5;                                                   //initializing acc pins


int RawMin = 0;
int RawMax = 5;  //reduce this for more precision of acc                                                    //for calculation of accelerometer
const int sampleSize = 10;

String temp = "0.0";                                                                      //for sending single message to bluetooth

void setup() {
  
  Serial.begin(9600);
  Bluetooth.begin(9600); 
  pinMode(flexPin1, INPUT);
  pinMode(flexPin2, INPUT);
  pinMode(flexPin3, INPUT);
  pinMode(flexPin4, INPUT);

}


void printfn(String cp)                //to avoid printing repeating symbols
{
if(cp!=temp)
{
Bluetooth.print(cp);
temp=cp;
}
}

void loop() {

  

  int v1 = analogRead(flexPin1);
  int v2 = analogRead(flexPin2);                                          //Flex sensor Inputs
  int v3 = analogRead(flexPin3);
  int v4 = analogRead(flexPin4);
 
  float Vf1 = v1 * VCC / 1023.0;
  float Vf2 = v2 * VCC / 1023.0;
  float Vf3 = v3 * VCC / 1023.0;
  float Vf4 = v4 * VCC / 1023.0;                                          //Flex sensor calculations

  float Rf1 = R_DIV * (VCC / Vf1 - 1.0);
  float Rf2 = R_DIV * (VCC / Vf2 - 1.0);
  float Rf3 = R_DIV * (VCC / Vf3 - 1.0);
  float Rf4 = R_DIV * (VCC / Vf4 - 1.0);
 
  float a1 = map(Rf1, fr1, br1, 0, 90.0);                                 //flex sensor bend angles
  float a2 = map(Rf2, fr2, br2, 0, 90.0);
  float a3 = map(Rf3, fr3, br3, 0, 90.0);
  float a4 = map(Rf4, fr4, br4, 0, 90.0);
/* 
 *  
 *  
 *  ACCELEROMETER 
 */
  int xRaw = ReadAxis(xInput);
  int yRaw = ReadAxis(yInput);                                            //Accelerometer Reading Input

  long xScaled = map(xRaw, RawMin, RawMax, -3000, 3000);                
  long yScaled = map(yRaw, RawMin, RawMax, -3000, 3000);
                                                                          //Accelerometer Calculations
  float xa = xScaled / 1000.0;        
  float ya = yScaled / 1000.0;                                        


  

  
 
  Serial.println("  Bend1 :  " + String(a1) + "  Bend2 :  " + String(a2) + "  Bend3 :  " + String(a3) + "  Bend4 :  " + String(a4) + "  X-acc -  " + String(xa) + "  Y-acc -  " + String(ya));
  Serial.println();

  delay(1000);


   if(((a1>=-10)&&(a1<=15))&&((a2>=-10)&&(a2<=16))&&((a3>=-10)&&(a3<=15))&&((a4>=-10)&&(a4<=15))&&((xa>=450))&&((xa<=510))&&((ya>=360)&&(ya<=410)))
   {
      printfn("Hi");
   }
  if(((a1>=-10)&&(a1<=20))&&((a2>=20)&&(a2<=90))&&((a3>=16)&&(a3<=80))&&((a4>=-10)&&(a4<=15))&&((xa>=440))&&((xa<=500))&&((ya>=350)&&(ya<=410)))
   {
      printfn("I love you");
   }
   if(((a1>=30)&&(a1<=80))&&((a2>=22)&&(a2<=75))&&((a3>=30)&&(a3<=80))&&((a4>=15)&&(a4<=70))&&((xa>=380))&&((xa<=435))&&((ya>=305)&&(ya<=345)))
   {
      printfn("Yes");
   }
   if(((a1>=20)&&(a1<=80))&&((a2>=22)&&(a2<=70))&&((a3>=30)&&(a3<=70))&&((a4>=15)&&(a4<=60))&&((xa>=360))&&((xa<=420))&&((ya>=470)&&(ya<=495)))
   {
      printfn("No");     
         }
   if(((a1>=-10)&&(a1<=20))&&((a2>=-10)&&(a2<=15))&&((a3>=21)&&(a3<=80))&&((a4>=16)&&(a4<=83))&&((xa>=450))&&((xa<=500))&&((ya>=350)&&(ya<=400)))
   {
      printfn("Victory");
   }
   if(((a1>=15)&&(a1<=70))&&((a2>=8)&&(a2<=70))&&((a3>=10)&&(a3<=73))&&((a4>=5)&&(a4<=68))&&((xa>=400))&&((xa<=450))&&((ya>=340)&&(ya<=400)))
   {
      printfn("Eat");
   }
  if(((a1>=-10)&&(a1<=20))&&((a2>=20)&&(a2<=90))&&((a3>=16)&&(a3<=80))&&((a4>=20)&(a4<=75))&&((xa>=440))&&((xa<=500))&&((ya>=350)&&(ya<=410)))
   {
      printfn("Up");
   }
   if(((a1>=20)&&(a1<=95))&&((a2>=-10)&&(a2<=16))&&((a3>=-10)&&(a3<=15))&&((a4>=-10)&&(a4<=15))&&((xa>=450))&&((xa<=510))&&((ya>=360)&&(ya<=410)))
   {
      printfn("Good Job");
   }

   


}-

int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
  reading += analogRead(axisPin);
  }
  return reading/sampleSize;
}
