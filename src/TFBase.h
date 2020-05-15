#ifndef TF_BASE_H_
#define TF_BASE_H_

#include <stdbool.h>
#include <stdint.h>
class TFBase{
    public:
        virtual void begin(void) = 0;
        virtual uint8_t get_distance(void) = 0;
        virtual uint8_t get_strength(void) = 0;
        virtual uint8_t get_chip_temprature(void) = 0;
        virtual uint8_t get_version(void) = 0;
        virtual bool set_output_status(uint8_t * cmd) = 0;
        virtual bool set_munication_mode(uint8_t * cmd) = 0;
        virtual bool set_frame_rate(uint8_t * cmd) = 0;
        virtual bool reset(uint8_t * cmd) = 0;
        virtual bool factory_reset(uint8_t * cmd) = 0;
        virtual bool save(uint8_t * cmd) = 0;
}
#include "TFLuna/TFLuna.h"
#endif