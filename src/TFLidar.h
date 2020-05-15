#ifndef TF_LIDAR_h
#define TF_LIDAR_h

#include <Arduino>
#include "TFBase.h"

class TFLidar{
  public:
    
    TFLidar(TFBase *TF_Lidar);
    int get_data(void);
  private:
  
};
#endif