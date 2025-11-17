#include "Makerlabvn_I2C_Motor_Driver.h"

Makerlabvn_I2C_Motor_Driver myDriver(0);

int speed = 50; // tốc độ động cơ bằng 50%

void setup() {
  // put your setup code here, to run once:
  myDriver.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  myDriver.writeMA(1, speed);  //cặp bánh trái xoay ngược
  myDriver.writeMB(0, speed);  //cặp bánh phải xoay thuận
  // ==>> xe quẹo phải 
  delay(1000);
  
  myDriver.writeMA(0, speed);  //cặp bánh trái xoay thuận
  myDriver.writeMB(1, speed);  //cặp bánh phải xoay ngược
  // ==>> xe quẹo trái
  delay(1000);

  myDriver.writeMA(1, speed);  //cặp bánh trái xoay ngược
  myDriver.writeMB(1, speed);  //cặp bánh phải xoay ngược
  // ==>> xe đi thẳng
  delay(1000);

  myDriver.writeMA(0, speed);  //cặp bánh trái xoay ngược
  myDriver.writeMB(0, speed);  //cặp bánh phải xoay ngược
  // ==>> xe đi lùi
  delay(1000);
}
