#include "TFLidar.h"

#define SERIAL Serial

#if defined(ARDUINO_ARCH_SAMD)
    #define uart  Serial1
#else
    SoftwareSerial uart(2, 3);
#endif

TFLuna SeeedTFLuna;
TFLidar SeeedTFLidar(&SeeedTFLuna);

void setup() {
  // put your setup code here, to run once:
  SERIAL.begin(9600);
  while(!Serial);
  SeeedTFLidar.begin(&uart);
}

void loop() {
  // put your main code here, to run repeatedly:
  // SERIAL.print("dist = ");
  SeeedTFLidar.get_distance();
  // SERIAL.print(SeeedTFLidar.get_distance()); //output measure distance value of LiDAR
  // SERIAL.print('\t');
  // SERIAL.print("strength = ");
  // SERIAL.print(SeeedTFLidar.get_strength()); //output signal strength value
  // SERIAL.print("\t Chip Temprature = ");
  // SERIAL.print(SeeedTFLidar.get_chip_temperature());
  // SERIAL.println(" celcius degree"); //output chip temperature of Lidar
  delay(1000);
}