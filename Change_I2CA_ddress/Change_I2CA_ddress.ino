/*
PRO MINI-----------GYUS42
VCC     ---------- 5V
GND     ---------- GND
A5      ---------- RC (SCL)
A4      ---------- TD (SDA)
*/
#include "Wire.h"  
#define SensorAddress byte(0x70) // GY-US42 默认I2C地址 0x70
#define RangeCommand byte(0x51)  // 发送测试距离指令
#define ChangeAddressCommand1 byte(0xAA)  // 修改 I2C Address的指令，必须顺序执行
#define ChangeAddressCommand2 byte(0xA5)


void setup() {
    Serial.begin(9600); //Open serial connection at 9600 baud
    Wire.begin(); 
    //  修改 I2C 地址 （旧地址，新地址，是否7位表示）
    changeAddress(0x20,0x40,1);
}

void loop(){

}


//  修改 I2C 地址 （旧地址，新地址，是否7位表示）
void changeAddress(byte oldAddress, byte newAddress, boolean SevenBitHuh){
  Wire.beginTransmission(oldAddress); //Begin addressing
  Wire.write(ChangeAddressCommand1); //Send first change address command
  Wire.write(ChangeAddressCommand2); //Send second change address command
  byte temp;
  if(SevenBitHuh){ temp = newAddress << 1; } //The new address must be written to the sensor
  else { temp = newAddress; } //in the 8bit form, so this handles automatic shifting
  Wire.write(temp); //Send the new address to change to
  Wire.endTransmission();
}
