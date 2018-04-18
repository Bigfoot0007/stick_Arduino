/*
  PRO MINI-----------GYUS42
  VCC ---------- 5V
  GND  --------- GND
  A5 -------- RC (SCL)
  A4 -------- TD (SDA)
  D3 --------  None source speaker
  D9 --------  Source Speaker
  盲杖，一共三个传感器，其I2C地址为 0x20,0x30和0x40,GY-US42默认是0x70,通过changeaddress进行修改
*/
#include "Wire.h"
#define Sensor1Address byte(0x70)
#define Sensor2Address byte(0x30)
#define Sensor3Address byte(0x40)
#define RangeCommand byte(0x51)  // 发送探测命令

#define rangetimesolt 50  // 等待返回的时间间隔，50毫秒
#define warringdistance 150 // 开始报警距离
int PIN_SPEAKER = 9;   // Speeker Pin D3，有源蜂鸣器。
int distance = 20; // Global distance 记录最小距离

/////////////////////////////////////////////////
// 初始化开始生硬
void notice(int delayms){
    digitalWrite(PIN_SPEAKER, LOW);
    digitalWrite(PIN_SPEAKER, HIGH); //发声音
    delay(delayms);
    digitalWrite(PIN_SPEAKER, LOW);
    delay(delayms);
}

////////  SETUP()
void setup() {
  pinMode(PIN_SPEAKER, OUTPUT);
  Serial.begin(9600); //Open serial connection at 9600 baud
  Wire.begin();
  notice(200);
  notice(200);
}
void loop() {
  word range1 = getRangebyAddress(Sensor1Address);
  Serial.print("Range1: "); Serial.print(range1); Serial.print(" , ");
  distance = range1;
  word range2 = getRangebyAddress(Sensor2Address);
  Serial.print("Range2: "); Serial.print(range2); Serial.print(" , ");
  if (range2 < distance) distance = range2;
  word range3 = getRangebyAddress(Sensor3Address);
  Serial.print("Range3: "); Serial.print(range3);
  // 距离只获取三个中最小的
  if (range3 < distance) distance = range3;
  // 这里需要处理 20cm ~ 200cm 的报警
  Serial.print("  Mini distance: "); Serial.print(distance);
  unsigned long now = millis();
  Serial.print("  now "); Serial.print(now);
  if (distance <= warringdistance && distance >= 20) {
     //  计算报警时间间隔
     
    
    Serial.print(",M:"); Serial.print(now % distance); Serial.print(",W: "); Serial.print(100*distance/warringdistance);
    digitalWrite(PIN_SPEAKER, HIGH); //发声音
    delay(100*distance/warringdistance);
    digitalWrite(PIN_SPEAKER, LOW);
    delay(100*distance/warringdistance);
  } else {
    // tone(PIN_SPEAKER,30);
    digitalWrite(PIN_SPEAKER, LOW); //不发声音
  }
  Serial.println();
}

// 获得Sensor的探测结果
word getRangebyAddress(byte SensorAddress) {
  Wire.beginTransmission(SensorAddress); //Start addressing
  Wire.write(RangeCommand); //send range command
  Wire.endTransmission(); //Stop and do something else now
  delay(rangetimesolt); // Wait for sensor to finish
  Wire.requestFrom(SensorAddress, byte(2));
  if (Wire.available() >= 2) { //Sensor responded with the two bytes
    byte HighByte = Wire.read(); //Read the high byte back
    byte LowByte = Wire.read(); //Read the low byte back
    word range = word(HighByte, LowByte); //Make a 16-bit word out of the two bytes for the range
    return range;
  } else {
    return word(0); //Else nothing was received, return 0
  }
}

