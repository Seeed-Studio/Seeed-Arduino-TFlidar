#ifndef TF_LIDAR_H__
#define TF_LIDAR_H__

#include "TFBase.h"
#include <Arduino.h>

class TFLidar{
  public:
        TFLidar(TFBase *TF_Lidar);
        void begin(SoftwareSerial *TFSerial , unsigned long baud_rate = 115200);
        void begin(HardwareSerial *TFSerial , unsigned long baud_rate = 115200);
        uint16_t get_distance(void);
        uint16_t get_strength(void);
        uint8_t get_chip_temperature(void);
        uint16_t get_version(void);
        bool get_frame_data(void);

        bool set_output_status(bool status);
        bool set_frame_rate(samplerate_mode mode);
        bool reset_device(void);
        bool factory_reset(void);
        bool save_config(void);
        // bool set_baud_rate(void);
        
  private:
    TFBase *_TF_Lidar;
};
#endif