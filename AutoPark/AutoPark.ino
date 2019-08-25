#include<SoftwareSerial.h>
#include<Servo.h>
int TxD=11;
int RxD=10;
#define rled 3
#define gled 5
#define bled 6
Servo myservo;
SoftwareSerial bluetooth(TxD,RxD);
char *keys[] = {"1023","3241","2231","1121"};
int i;

void up()
{
   for (int pos = 0; pos <= 90; pos += 1) { 
        myservo.write(pos); 
        colour(255,255,0);
        delay(15);                     
    }
}
void dwn()
{
   for (int pos = 90; pos >= 0; pos -= 1) { 
        myservo.write(pos);   
      colour(255,255,0);
      delay(15);                       
    }
}
void colour(int red,int green,int blue)
{ 
  
  
  analogWrite(rled,red);
  analogWrite(gled,green);
  analogWrite(bled,blue);
}
void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
  pinMode(rled,OUTPUT);
  pinMode(gled,OUTPUT);
  pinMode(bled,OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  colour(255,0,0);
  if(bluetooth.available())
   { 
     String val=bluetooth.readString();
     bluetooth.println(val);
    int flag=0;
      for(i=0;i<3;i++)
      { 
        if(val==keys[i])
        {
          flag=1;
          up();
          colour(0,255,0);
          delay(3000);
          dwn();
          
        }
      }
      if(flag==0)
      bluetooth.println("UNAUTHORIZED");
   }
}
