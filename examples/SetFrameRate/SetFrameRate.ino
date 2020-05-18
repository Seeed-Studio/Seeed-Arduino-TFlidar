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
  SeeedTFLidar.set_frame_rate(SAMPLERATE_100HZ);
  if(SeeedTFLidar.save_config()){
      SERIAL.println("config successful");
  }
  else{
      SERIAL.println("config failed");
  }
  
}
void loop() {

}