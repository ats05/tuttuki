#include <Servo.h>

#define STATUS_STOP       0
#define STATUS_FORWORD    100
#define STATUS_RIGHT      101
#define STATUS_LEFT       102
#define STATUS_BACK       200
#define STATUS_BACK_RIGHT 201
#define STATUS_BACK_LEFT  202
#define STATUS_TUTTUKI    500


Servo servoL;
Servo servoR;
Servo servo3;
int status = 100;
int statusCount = 0;
int rotate = 0;

// 進行方向を右とか左とかランダムにする
int directionOffset = 0;
const int distancePin = A0;
const float Vcc = 3.5;

void setup() {

  Serial.begin(9600);


  servoL.attach(5);
  servoR.attach(3);


  servo3.attach(8);
  servo3.write(30);

  //  servoL.write(90);
  //  servoR.write(90);


}

/**
   pin ピン番号
   return センチメートル
*/
int readDistance(int pin) {
  float dist = Vcc * analogRead(pin) / 1023;
  dist = 26.549 * pow(dist, -1.2091);
  Serial.print(status);
  Serial.print(" ");
  Serial.print(statusCount);
  Serial.print(" ");
  Serial.print(dist);
  Serial.print("\n");
  return dist;
}

void loop() {

  // 障害物
  float dist = readDistance(distancePin);
  if (dist < 20 && dist > 15) {
    changeStatus(STATUS_BACK);
  }
  // 動くもの
  else if (dist < 15 && dist > 5) {
    if (status != STATUS_TUTTUKI) changeStatus(STATUS_TUTTUKI);
  }
  else {
    if (status != STATUS_FORWORD){
      // きょろきょろ
      kyoroKyoro();
      changeStatus(STATUS_FORWORD);
    }

  }

  float r = 10;
  float l = 10;
  switch (status) {
    case STATUS_FORWORD:


      runServo(10, 10);
      if (statusCount > 80 and random(0, 1)) {
        changeStatus(STATUS_FORWORD);
      }
      break;
    case STATUS_BACK:
      runServo(random(5, 30) * -1, random(5, 10) * -1);
      delay(200);
      break;

    case STATUS_TUTTUKI:
      tuttuki();
      changeStatus(STATUS_BACK);
      
      break;

  }


  statusCount++;
}

/**
   speedR: integer -100~100
   speedL: integer -100~100
*/
void runServo(int speedR, int speedL) {

  // 確実に止める
  if (speedR == 0 && speedL == 0) {
    servoR.write(88);
    servoL.write(95);
    return;
  }
  //TODO: アングルの実装

  // 270  →90:180

  float r = 90 - ((speedR * 0.01) * 90) + 2;
  float l = 90 + ((speedL * 0.01) * 90);


  // 停止:90 全力前進:0 に制御 . 2:誤差
  servoR.write(r);

  // 停止:90 全力前進:180 に制御
  servoL.write(l);


}

void changeStatus(int num) {
//  if(statusCount < 10) return;
  statusCount = 0;
  status = num;
  if(random(0,1)){
    runServo(0, 0);
    delay(random(5, 20) * 100);
  }
} 

void kyoroKyoro() {
  int rnd = random(0, 3);
  for(int i = 0; i < rnd; i++){
    float spd = random(0,50) - 25;

    runServo(spd, -spd);
    delay(random(1, 2) * 100);
    runServo(0, 0);
    delay(random(2, 5) * 100);

  }
}

void tuttuki(){
  int rnd = random(10, 20);
  for(int i = 0; i < rnd; i++){
    runServo(random(1, 8), random(1, 8));
  }
  
  rnd = random(0, 4);
  runServo(0, 0);
  for(int i = 0; i < rnd; i++){
    delay(random(10, 30) * 100);
    servo3.write(80);
    // runServo(10, 0);
    delay(300);
    servo3.write(30);
    // runServo(-10, 0);
    delay(300);
    servo3.write(80);
    // runServo(10, 0);
    delay(300);
    servo3.write(30);
    // runServo(-10, 0);
  }

}

