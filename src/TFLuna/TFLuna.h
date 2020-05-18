#ifndef TF_LUNA_H__
#define TF_LUNA_H__

#include "TFBase.h"
#include <Arduino.h>

class TFLuna : public TFBase {
    public:
        void begin(SoftwareSerial *TFSerial , unsigned long baud_rate = 115200);
        void begin(HardwareSerial *TFSerial , unsigned long baud_rate = 115200);
        uint16_t get_distance(void);
        uint16_t get_strength(void);
        uint8_t get_chip_temperature(void);
        uint16_t get_version(void){};
        bool set_output_status(uint8_t * cmd){};
        bool set_comunication_mode(uint8_t * cmd){};
        bool set_frame_rate(uint8_t * cmd){};
        bool reset(uint8_t * cmd){};
        bool factory_reset(uint8_t * cmd){};
        bool save(uint8_t * cmd){};
        bool get_frame_data(void);
    private:
        Stream *_TFTransporter;
        recv_package *_package = (recv_package*) malloc(sizeof(recv_package));
        uint8_t uart[9];  //save data measured by LiDAR
    protected:
        bool check_header(recv_package *package);
        bool verify_data(recv_package *package);
};
#endif