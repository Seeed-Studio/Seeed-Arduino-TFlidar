#ifndef TF_LIDAR_H__
#define TF_LIDAR_H__

#include "TFBase.h"
#include <Arduino.h>


class TFLidar{
  public:
    TFLidar(TFBase *TF_Lidar);
    uint8_t get_data(void);
  
};
#endif