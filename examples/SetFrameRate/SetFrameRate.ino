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
    int buff[3] = {0};
    SeeedTFLidar.begin(&uart);
    SeeedTFLidar.set_frame_rate(SAMPLERATE_100HZ);
    if(SeeedTFLidar.save_config()){
        SERIAL.println("config successful");
    }
    else{
        SERIAL.println("config failed");
    }
    if(SeeedTFLidar.get_version(buff)){
        SERIAL.print("the version is : ");
        SERIAL.print(buff[0]);
        SERIAL.print(".");
        SERIAL.print(buff[1]);
        SERIAL.print(".");
        SERIAL.println(buff[2]);
    }
}
void loop() {
}