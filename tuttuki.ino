#include <Servo.h>

#define STATUS_FORWORD 100
#define STATUS_BACK 200

Servo servoL;
Servo servoR;
Servo servo3;
int status = 100;
int rotate = 0;
const int distancePin = A0;
const float Vcc = 3.5; 

void setup() {
 
  Serial.begin(9600);

  servoL.attach(2);
  servoR.attach(3);
//  servo3.attach(6);

//  servoL.write(90);
//  servoR.write(90);

  
}

/**
 * pin ピン番号
 * return センチメートル
 */
int readDistance(int pin){
  float dist = Vcc * analogRead(pin) / 1023;  
  dist = 26.549 * pow(dist, -1.2091); 

  Serial.println(dist);

  return dist;
}

void loop() {  

  if(readDistance(distancePin) < 15 && readDistance(distancePin) > 5) {
    if(status == STATUS_FORWORD) {
      // 障害物があるとちょっと考え込む
      runServo(0, 0);
//      delay(2000);
    }
    status = STATUS_BACK;
  }
  else{
    status = STATUS_FORWORD;
  }


  switch(status){
    case STATUS_FORWORD:
      runServo(10, 10);
      break;
    case STATUS_BACK:
      runServo(-2, -8);
      break;
      
  }
  
  

}

/**
 * speedR: integer -100~100
 * speedL: integer -100~100
 */
void runServo(int speedR, int speedL){
  //TODO: アングルの実装
  
  // 270  →90:180
  
  // 停止:90 全力前進:0 に制御
  servoR.write(90 - ((speedR * 0.01) * 90));

  // 停止:90 全力前進:180 に制御
  servoL.write(90 + ((speedL * 0.01) * 90));

  
}

//
//void random(){
//  
//
//}


