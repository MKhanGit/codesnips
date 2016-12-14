//Mohsin Khan
//last edited: December 13th, 2016
//
//Firmware for bluetooth master analog remote

// Initialize speed control variables
int transmit_speed = 0;
int stick;
int istick;
int pstick = 0;
int speedmode = 100;
int icount=0;
int rampflag = 1;

int flashflag = 0;


void setup() 
{
  
  //pinMode(2,INPUT_PULLUP);
  //pinMode(3,INPUT_PULLUP);

  //attachInterrupt(digitalPinToInterrupt(2), TICKUP, FALLING);
  // attachInterrupt(digitalPinToInterrupt(3), TICKDOWN, FALLING);

  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
 
  pinMode(A7,INPUT);
  Serial.begin(115200);
  pstick = map(analogRead(A7), 500, 1000, 200, speedmode);

}


void loop()
{

  // if(flashflag){
  //   flashflag = 0;
  //   for (int i=0;i<4;i++){
  //   digitalWrite(4,!digitalRead(4));
  //   delay(100);
		// }
  //   }

  stick = map(analogRead(A7), 500, 1000, 200, speedmode);


  if (stick < 0){
    stick = 0;
    }
    
  if ((abs(stick - pstick) > 25)){
      for (int i=pstick;i<=stick;i+=5){
        istick = map(analogRead(A7), 500, 1000, 200, speedmode);
        if ((stick - istick) > 5) {
          stick=istick;
          break;
        }
      transmit(i);
      delay(450);
        }
      }
  else{    
  transmit(stick);
  }
  pstick = stick;
delay(10); 
}

void transmit(int tspeed){
    Serial.println(tspeed);
    delay(5);
}


// void TICKUP(){
//     icount++;
//     if(speedmode==100){
//       speedmode=180;
      
//       digitalWrite(4,HIGH);
      
//       }
//      else if (speedmode==180 && icount==2){
//       rampflag=0;
//       flashflag = 1;
//      }
//       else{
//         speedmode=100;
//         digitalWrite(4,LOW);
//         rampflag =1;
//         icount=0;
//         }
// }

//
//void TICKDOWN(){
//    rampflag = !rampflag;
//    for (int j = 0; j < 4; j++){
//    digitalWrite(4,!digitalRead(4));
//    delay(500);
//    }
//}


