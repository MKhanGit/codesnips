//Mohsin Khan
//last edited: December 13th, 2016
//
//Firmware for electric longboard

#include <Servo.h>
Servo primary_motor;

int MIN_SPEED = 1000;
int MAX_SPEED = 1500;
String serin = "200200";
String datasend = "200";
int transmission = 0;

unsigned long timestamp;
unsigned long timeout = 3000UL;
void setup() 
{
  pinMode(2,INPUT_PULLUP);
  
  primary_motor.attach(7);
  Serial.begin(9600);
  Serial.println("BOOTUP");
  primary_motor.writeMicroseconds(MIN_SPEED);
  if (!digitalRead(2)){
    Serial.println("Boosted Mode Enabled");
    MAX_SPEED = 2000;
    }
}

void loop()
{
  timestamp = millis();
  while ((millis() - timestamp) < timeout){
    
  if (Serial.available()){
    serin = String(Serial.parseInt());
    datasend = "";
    datasend.concat(serin[0]);
    datasend.concat(serin[1]);
    datasend.concat(serin[2]);
    transmission = map(datasend.toInt(),200,100,MIN_SPEED,MAX_SPEED);
    
    if (transmission < 0 || transmission > 2100){
      transmission = 700;
      Serial.println("Defaulting");
      }
      
    Serial.print(datasend);
    Serial.print("\t");
    Serial.println(transmission);
    primary_motor.writeMicroseconds(transmission);
    
    timestamp = millis();
    }
    
    delay(25);
}
  primary_motor.writeMicroseconds(MIN_SPEED);
  while(!Serial.available()){
    
    //wait until communication restored
    Serial.println("Waiting for input...");
    delay(1000);
    }
  
}

