#include"TFLuna.h"

void TFLuna::begin(SoftwareSerial *TFSerial,uint16_t baud_rate){
    TFSerial->begin(baud_rate);
    _TFTransporter = TFSerial;
}

void TFLuna::begin(HardwareSerial *TFSerial,uint16_t baud_rate){
    TFSerial->begin(baud_rate);
    _TFTransporter = TFSerial;
}

bool TFLuna::check_header(recv_package *package){
    for(uint8_t index = 0 ;index < 2 ;index++){
        if(RECV_HEADER !=_TFTransporter->read())
            return false;
        package->header[index] = RECV_HEADER;
    }
    return true;
}

bool TFLuna::verify_data(recv_package *package){
    uint16_t check_sum = 0;
    check_sum = package->header[0] + package->header[1]\
    + package->distance[0] + package->distance[1]     \
    + package->strength[0] + package->strength[1]     \
    + package->chip_temperature[0] + package->chip_temperature[1];
    if((check_sum & 0xff) == _TFTransporter->read()){
        return true;
    }
    return false;    
}

bool TFLuna::get_frame_data(recv_package *package){
    if(_TFTransporter->available()){
        if(!check_header(package)){
            return false;
        }
        for(uint8_t index = 0 ;index < 2 ;index++){
            package->distance[index] = _TFTransporter->read();
        }
        for(uint8_t index = 0 ;index < 2 ;index++){
            package->strength[index] = _TFTransporter->read();
        }        
        for(uint8_t index = 0 ;index < 2 ;index++){
            package->chip_temperature[index] = _TFTransporter->read();
        }      
        if(!verify_data(package)){
            return false;
        }
        return true;
    }
}

uint16_t TFLuna::get_distance(){
    while(!get_frame_data(_package));
    return _package->distance[0] | (uint16_t)_package->distance[1] * 255;
}

uint16_t TFLuna::get_strength(){
    while(!get_frame_data(_package));
    return _package->strength[0] | (uint16_t)_package->strength[1] * 255;
}

uint16_t TFLuna::get_chip_temperature(){
    uint16_t chip_temperature;
    while(!get_frame_data(_package));
    chip_temperature = _package->chip_temperature[0] | (uint16_t)_package->chip_temperature[1] * 255;
    chip_temperature = chip_temperature / 8 - 256;
    return chip_temperature;
}
