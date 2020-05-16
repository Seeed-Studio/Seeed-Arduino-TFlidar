#ifndef TF_LIDAR_H__
#define TF_LIDAR_H__

#include "TFBase.h"
#include <Arduino.h>

class TFLidar{
  public:
    TFLidar(TFBase *TF_Lidar);
    void begin(SoftwareSerial *TFSerial , uint16_t baud_rate = 115200);
    void begin(HardwareSerial *TFSerial , uint16_t baud_rate = 115200);
    uint16_t get_distance(void);
    uint16_t get_strength(void);
    uint16_t get_chip_temperature(void);
  private:
    TFBase *_TF_Lidar;
};
#endif