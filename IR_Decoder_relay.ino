/*
 * IR Decoder for lighting Control, with motion proximity alert system
 * Mohsin Khan
 * August 16, 2016
 */

#include <IRLib.h>

int RECV_PIN = 11;

IRrecv My_Receiver(RECV_PIN);

IRdecode My_Decoder;
unsigned int Buffer[RAWBUF];
const int relaych1 = 12;
const int PIR = 10;
int armFlag = 0;
const int armLed = 2;
char inbyte;
//const int alertch1 = 13;
void setup()
{
  pinMode(armLed,OUTPUT);
  pinMode(relaych1,OUTPUT);
  pinMode(PIR,INPUT);
  //pinMode(alertch1,OUTPUT);
  digitalWrite(armLed,armFlag);
  digitalWrite(relaych1,HIGH);
  
  Serial.begin(9600);
  //delay(2000);while(!Serial);//delay for Leonardo
  My_Receiver.enableIRIn(); // Start the receiver
  My_Decoder.UseExtnBuf(Buffer);
}

void loop() {
  if (digitalRead(PIR) and armFlag){
    alert(relaych1,4);
    delay(1200);
    }
  
  if (Serial.available() > 0) {
    inbyte = Serial.read();
    
    if (inbyte == 'A' || inbyte == 'a'){
      toggleAlarm();
      }   //alert and toggle
      
    else if (inbyte == 'L' || inbyte == 'l'){
      ledToggle(relaych1);
      }
      
    }
  if (My_Receiver.GetResults(&My_Decoder)) {
    //Restart the receiver so it can be capturing another code
    //while we are working on decoding this one.
    My_Receiver.resume(); 
    My_Decoder.decode();
    //My_Decoder.DumpResults();
    Serial.println(My_Decoder.value,HEX);
    if (My_Decoder.value == 0xFF02FD){ //toggle light
      ledToggle(relaych1);
      delay(50);
      }
    if (My_Decoder.value == 0xFF827D){ //test alert
      toggleAlarm();
      delay(50);
      }
    if (My_Decoder.value == 0xFFE01F){
      Serial.println("ON!");
      digitalWrite(relaych1,LOW);
      }
    
    if (My_Decoder.value == 0xFF609F){
      Serial.println("OFF!");
      digitalWrite(relaych1,HIGH);
      }
    else {
      Serial.println(My_Decoder.value);    
      }
    }

}

void ledToggle(int ledPin){
  
  digitalWrite(ledPin,!digitalRead(ledPin));
    
  }

void alert(int alertPin, int repeats){
  for(int i = 0; i < repeats; i++){
    ledToggle(alertPin);
    delay(200);
    }
  }

void toggleAlarm(){
  armFlag = !armFlag;
  digitalWrite(armLed,armFlag);
      if (armFlag){ Serial.println("ARMED");}
      else{ Serial.println("DISARMED");}
  }


