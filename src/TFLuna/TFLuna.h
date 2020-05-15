#ifndef TF_LUNA_H__
#define TF_LUNA_H__

#include "TFBase.h"
#include <Arduino.h>


class TFLuna : public TFBase {
    public:
        void begin(void);
        uint8_t get_distance(void);
        uint8_t get_strength(void);
        uint8_t get_chip_temprature(void);
        uint8_t get_version(void);
        bool set_output_status(uint8_t * cmd);
        bool set_munication_mode(uint8_t * cmd);
        bool set_frame_rate(uint8_t * cmd);
        bool reset(uint8_t * cmd);
        bool factory_reset(uint8_t * cmd);
        bool save(uint8_t * cmd);
};
#endif