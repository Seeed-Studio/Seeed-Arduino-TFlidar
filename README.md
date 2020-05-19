# Seeed_Arduino_TFlidar  [![Build Status](https://travis-ci.com/Seeed-Studio/Seeed-Arduino-TFlidar.svg?branch=master)](https://travis-ci.com/Seeed-Studio/Seeed-Arduino-TFlidar)

## Introduction
Seeed Arduino lidar is a seeed's library that aim is to drive all lidar of TF.this library having development for now.

## Usage

```c++
#include "TFLidar.h"

// #define USETFMINI
#define USETFLUNA

#define SERIAL Serial

#if defined(ARDUINO_ARCH_SAMD)
    #define uart  Serial1
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
  SeeedTFLidar.begin(&uart);
}

void loop() {
  while(!SeeedTFLidar.get_frame_data()){
      delay(1);
  }
  // put your main code here, to run repeatedly:
  SERIAL.print("dist = ");
  SERIAL.print(SeeedTFLidar.get_distance()); //output measure distance value of LiDAR
  SERIAL.print('\t');
  SERIAL.print("strength = ");
  SERIAL.print(SeeedTFLidar.get_strength()); //output signal strength value
  SERIAL.print("\t Chip Temprature = ");
#ifdef USETFLUNA
  SERIAL.print(SeeedTFLidar.get_chip_temperature());
  SERIAL.print(" celcius degree"); //output chip temperature of Lidar
#endif
  SERIAL.println(" ");
}
```


This software is written by downey  for seeed studio<br>
Email:baozhu.zuo@gmail.com
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>