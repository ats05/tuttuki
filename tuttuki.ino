#include <Servo.h>

Servo servoL;
Servo servoR;
int status = 100;
int rotate = 0;

void setup() {
 
  Serial.begin(9600);

  servoL.attach(3);
  servoR.attach(2);

  
}

void loop() {  

  runServo(100, 0);
//  switch(status){
//    case 100:
//      random();
//      break;
//  }

  
//  delay(8000) ; //8秒間停止
//  servo01.writeMicroseconds(544); //パルス幅値を代入：544~2400
//  delay(8000) ; //8秒間停止

}

/**
 * speed: integer 0~100
 * angle: integer 0~360
 */
void runServo(int spd, int ang){

  //TODO: アングルの実装
  
  // 停止:90 全力前進:0 に制御
  servoR.write(90 - ((spd * 0.01) * 90));

  // 停止:90 全力前進:180 に制御
  servoL.write(90 + ((spd * 0.01) * 90));

  
}

//
//void random(){
//  
//
//}


