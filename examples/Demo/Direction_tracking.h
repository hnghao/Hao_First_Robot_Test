#ifndef Direction_tracking_H
#define Direction_tracking_H

#include "Makerlabvn_I2C_Motor_Driver.h"

Makerlabvn_I2C_Motor_Driver myDriver(0);

void goahead(int speed){
  myDriver.writeMA(1, speed);
  myDriver.writeMB(1, speed);
  // ==>> xe đi thẳng
}

void goback(int speed){
  myDriver.writeMA(0, speed);
  myDriver.writeMB(0, speed);
  // ==>> xe đi lùi
}

void turntheleft(int speed){
  myDriver.writeMA(0, speed);
  myDriver.writeMB(1, speed);
  // ==>> xe đi trái
}

void turntheright(int speed){
  myDriver.writeMA(1, speed);
  myDriver.writeMB(0, speed);
  // ==>> xe đi phải
}

#endif