#include"TFLuna.h"

void TFLuna::begin(SoftwareSerial *TFSerial,unsigned long baud_rate){
    TFSerial->begin(baud_rate);
    _TFTransporter = TFSerial;
}

void TFLuna::begin(HardwareSerial *TFSerial,unsigned long baud_rate){
    TFSerial->begin(baud_rate);
    _TFTransporter = TFSerial;
}

bool TFLuna::check_header(recv_package *package){
    uint8_t recv_data;
#ifdef DEBUG_EN
    Serial.print("check_header ");
#endif  
    for(uint8_t index = 0; index < 2; index++){
        recv_data = (uint8_t)_TFTransporter->read(); 
        if(RECV_HEADER != recv_data){
#ifdef DEBUG_EN
            Serial.println("failed");
#endif              
            return false;
        }
        package->header[index] = recv_data;
    }
#ifdef DEBUG_EN
    Serial.println("successful");
#endif     
    return true;
}

bool TFLuna::verify_data(recv_package *package){
    package->checksum = package->header[0] + package->header[1]\
    + package->distance[0] + package->distance[1]     \
    + package->strength[0] + package->strength[1]     \
    + package->chip_temperature[0] + package->chip_temperature[1];
#ifdef DEBUG_EN
    Serial.print("verify_data ");
#endif 
    if((package->checksum & 0xff) == (uint8_t)(_TFTransporter->read())){
#ifdef DEBUG_EN
    Serial.println("successful");
#endif
        return true;
    }
#ifdef DEBUG_EN
    Serial.println("failed");
#endif
    return false;    
}

bool TFLuna::get_frame_data(recv_package *package){
    if(!_TFTransporter->available()){
        return false;
    }
    if(!check_header(package)){
        return false;
    }    
    for(uint8_t index = 0 ;index < 2 ;index++){
        package->distance[index] = (uint8_t)(_TFTransporter->read());
    }
    for(uint8_t index = 0 ;index < 2 ;index++){
        package->strength[index] = (uint8_t)(_TFTransporter->read());
    }      
    for(uint8_t index = 0 ;index < 2 ;index++){
        package->chip_temperature[index] = (uint8_t)(_TFTransporter->read());
    }
    if(!verify_data(package)){
#ifdef DEBUG_EN
    Serial.print("UART <= ");
    for(uint8_t index = 0 ;index < 2 ;index++){
        Serial.print(package->header[index],HEX);
        Serial.print(" ");
    }        
    for(uint8_t index = 0 ;index < 2 ;index++){
        Serial.print(package->distance[index],HEX);
        Serial.print(" ");
    }
    for(uint8_t index = 0 ;index < 2 ;index++){
        Serial.print(package->strength[index],HEX);
        Serial.print(" ");
    }        
    for(uint8_t index = 0 ;index < 2 ;index++){
        Serial.print(package->chip_temperature[index],HEX);
        Serial.print(" ");
    }      
    Serial.println(package->checksum & 0xff,HEX);
#endif        
        return false;
    }

    return true;
}

uint16_t TFLuna::get_distance(){
    while(!get_frame_data(_package)){
        delay(5);      
    }
    return _package->distance[0] + (uint16_t)_package->distance[1] * 255;
}

uint16_t TFLuna::get_strength(){
    while(!get_frame_data(_package)){
        delay(5);
    }
    return _package->strength[0] | (uint16_t)_package->strength[1] * 255;
}

uint16_t TFLuna::get_chip_temperature(){
    uint16_t chip_temperature;
    while(!get_frame_data(_package)){
        delay(5);
    }
    chip_temperature = _package->chip_temperature[0] | (uint16_t)_package->chip_temperature[1] * 255;
    chip_temperature = chip_temperature / 8 - 256;
    return chip_temperature;
}
