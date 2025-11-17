#include "Makerlabvn_I2C_Line_Follower_Sensor.h"
#include "Direction_tracking.h"

Makerlabvn_I2C_Line_Follower_Sensor LineFollowSensor;

void setup() {
  myDriver.begin();
  delay(1500);

  // 5 sensor mặc định
  LineFollowSensor.setup(0x2A);
  LineFollowSensor.setBlack();   // line màu đen
}

void loop() {

  LineFollowSensor.getData();
  uint8_t t = LineFollowSensor.getValue();   // trả về dạng bitmask

  // ỔN ĐỊNH GIÁ TRỊ T
  static uint8_t stable_t = 0;
  static uint8_t last_raw_t = 0;

  if (t != 0) {
    if (t == last_raw_t) {
      stable_t = t;        // chỉ nhận khi 2 lần liên tiếp giống nhau
    }
    last_raw_t = t;
  }

  // LƯU HƯỚNG CUỐI CÙNG THẤY LINE
  static int lastDir = 1;     // 1 = phải | -1 = trái

  //MẤT LINE → TỰ TÌM LINE LẠI
  if (t == 0) {

    int searchSpeed = 55;

    // Xoay theo hướng cuối cùng còn thấy line
    if (lastDir > 0)
      turntheright(searchSpeed);
    else
      turntheleft(searchSpeed);

    delay(80);

    LineFollowSensor.getData();
    uint8_t tt = LineFollowSensor.getValue();
    if (tt != 0) {   // tìm lại được line
      stable_t = tt;
      return;
    }

    // Lùi nhẹ nếu xoay không thấy line
    goback(50);
    delay(80);

    return;
  }

  //SOFT-STEERING – GIÚP BÁM LINE MƯỢT HƠN

  int speedBase      = 55;  
  int speedTurn      = 60;
  int speedHardTurn  = 72;

  // ======= Đi thẳng =======
  if (stable_t == 4 || stable_t == 14 || stable_t == 30 || stable_t == 28) {
    goahead(speedBase);
    lastDir = 1;
  }

  // ======= Lệch trái nhẹ =======
  else if (stable_t == 2 || stable_t == 6 || stable_t == 7) {
    turntheleft(speedTurn);
    lastDir = -1;
  }

  // ======= Lệch trái mạnh =======
  else if (stable_t == 1 || stable_t == 3) {
    turntheleft(speedHardTurn);
    lastDir = -1;
  }

  // ======= Lệch phải nhẹ =======
  else if (stable_t == 8 || stable_t == 12 || stable_t == 28) {
    turntheright(speedTurn);
    lastDir = 1;
  }

  // ======= Lệch phải mạnh =======
  else if (stable_t == 16 || stable_t == 24) {
    turntheright(speedHardTurn);
    lastDir = 1;
  }

  // ======= Fallback: đi thẳng =======
  else {
    goahead(speedBase);
  }

  delay(5);   // giảm rung nhẹ
}
