// INCLUDE LIBRARIES
#include "Makerlabvn_I2C_Line_Follower_Sensor.h"
#include "Direction_tracking.h"

// OBJECT INITIALIZATION
Makerlabvn_I2C_Line_Follower_Sensor LineFollowSensor;

void setup() {
  myDriver.begin();
  delay(2000);
  LineFollowSensor.setup(0x2A);
}

void loop() {
  LineFollowSensor.getData();
  uint8_t t = LineFollowSensor.getValue();

  if((t==31)) goahead(60);
  else if((t==15) ||  (t==30)){
    turntheright(45);
    delay(10);
    turntheleft(45);
    delay(10);
  } else if(t==7) turntheleft(50);
  else if(t==28)  turntheright(50);
  else if(t == 14) goahead(60);
  else if((t==3)  ||  (t==6)) turntheleft(60);
  else if((t==12) ||  (t==24))  turntheright(60);
  else if((t==1)  ||  (t==2)) turntheleft(70);
  else if((t==8)  ||  (t==16))  turntheright(70);
  else if(t==4) goahead(60);
  // else goback(50);
  else {
    // Nếu mất line → thực hiện quy trình tìm line
    // gồm: dừng → xoay trái → xoay phải → lùi → lặp lại

    while (t == 0) {

      // 1. DỪNG LẠI 1 CHÚT
      goahead(0);
      delay(200);

      // 2. XOAY TRÁI 1 GIÂY
      turntheleft(60);
      delay(1000);
      LineFollowSensor.getData();
      t = LineFollowSensor.getValue();
      if (t != 0) break;

      // 3. XOAY PHẢI 1 GIÂY
      turntheright(60);
      delay(1000);
      LineFollowSensor.getData();
      t = LineFollowSensor.getValue();
      if (t != 0) break;

      // 4. LÙI 1 GIÂY
      goback(60);
      delay(1000);
      LineFollowSensor.getData();
      t = LineFollowSensor.getValue();
      if (t != 0) break;

      // Nếu vẫn chưa tìm được line → tiếp tục vòng lặp
    }
  }
}
