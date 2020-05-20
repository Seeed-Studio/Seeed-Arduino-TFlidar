#include "TFLidar.h"

#define USETFMINI
// #define USETFLUNA

#define SERIAL Serial

#if defined(SEEED_XIAO_M0)
    #define uart  Serial1
#elif defined(SEEED_WIO_TERMINAL)
    SoftwareSerial uart(0, 1);
#else
    SoftwareSerial uart(2, 3);
#endif

#ifdef USETFLUNA
TFLuna SeeedTFLuna;
TFLidar SeeedTFLidar(&SeeedTFLuna);
#endif

#ifdef USETFMINI
TFMini SeeedTFMini;
TFLidar SeeedTFLidar(&SeeedTFMini);
#endif 


void setup() {
  // put your setup code here, to run once:
  SERIAL.begin(9600);
  while(!Serial);
#if defined(SEEED_WIO_TERMINAL)  
  SeeedTFLidar.begin(&uart,9600);
#else
  SeeedTFLidar.begin(&uart,115200);
#endif 
}

void loop() {
  while(!SeeedTFLidar.get_frame_data()){
  #if defined(SEEED_WIO_TERMINAL)  
      delay(20); 
  #else
      delay(1); 
  #endif
  }
  // put your main code here, to run repeatedly:
  SERIAL.print("dist = ");
  SERIAL.print(SeeedTFLidar.get_distance()); //output measure distance value of LiDAR
  SERIAL.print('\t');
  SERIAL.print("strength = ");
  SERIAL.print(SeeedTFLidar.get_strength()); //output signal strength value
#ifdef USETFLUNA
  SERIAL.print("\t Chip Temprature = ");
  SERIAL.print(SeeedTFLidar.get_chip_temperature());
  SERIAL.print(" celcius degree"); //output chip temperature of Lidar
#endif
  SERIAL.println(" ");
  // delay(1000);
}