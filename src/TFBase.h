#ifndef TF_BASE_H__
#define TF_BASE_H__

#include <stdbool.h>
#include <stdint.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#define RECV_HEADER 0X59
typedef struct {
    uint8_t header[2];
    uint8_t distance[2];
    uint8_t strength[2];
    uint8_t chip_temperature[2];
    uint8_t checksum;
} recv_package;

class TFBase {
    public:
        virtual void begin(SoftwareSerial *TFSerial , uint16_t baud_rate = 115200) = 0;
        virtual void begin(HardwareSerial *TFSerial , uint16_t baud_rate = 115200);
        virtual uint16_t get_distance(void) = 0;
        virtual uint16_t get_strength(void) = 0;
        virtual uint16_t get_chip_temperature(void) = 0;
        virtual uint16_t get_version(void) = 0;
        virtual bool set_output_status(uint8_t * cmd) = 0;
        virtual bool set_comunication_mode(uint8_t * cmd) = 0;
        virtual bool set_frame_rate(uint8_t * cmd) = 0;
        virtual bool reset(uint8_t * cmd) = 0;
        virtual bool factory_reset(uint8_t * cmd) = 0;
        virtual bool save(uint8_t * cmd) = 0;
    protected:
        virtual bool get_frame_data(recv_package *package);
        virtual bool check_header(recv_package *package);
        virtual bool verify_data(recv_package *package);
};
#include "TFLuna/TFLuna.h"
#endif