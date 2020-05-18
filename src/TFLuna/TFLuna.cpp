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
        package->header[index] = (uint8_t)_TFTransporter->read(); 
        if(RECV_HEADER != package->header[index]){
#ifdef DEBUG_EN
            Serial.println("failed");
#endif              
            return false;
        }
    }
#ifdef DEBUG_EN
    Serial.println("successful");
#endif     
    return true;
}

bool TFLuna::verify_data(recv_package *package){
    uint16_t checksum = package->header[0] + package->header[1]\
    + package->distance[0] + package->distance[1]     \
    + package->strength[0] + package->strength[1]     \
    + package->chip_temperature[0] + package->chip_temperature[1];
#ifdef DEBUG_EN
    Serial.print("verify_data ");
#endif 
    if((checksum & 0xff) == (uint16_t)(package->checksum)){
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

bool TFLuna::get_frame_data(void){
    if(!_TFTransporter->available()){
        return false;
    }  
    uint16_t check;
    if(!check_header(_package)){
        return false;
    }
    for (uint8_t i = 2; i < 9; i++) { //save data in array
        uart[i] = _TFTransporter->read();
    }
    _package->header[0] = RECV_HEADER;
    _package->header[1] = RECV_HEADER;
    _package->checksum = uart[8];
    _package->distance[0] = uart[2];
    _package->distance[1] = uart[3];
    _package->strength[0] = uart[4];
    _package->strength[1] = uart[5];
    _package->chip_temperature[0] = uart[6];
    _package->chip_temperature[1] = uart[7];
    if(!verify_data(_package)){
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
    uint16_t distance = _package->distance[0] + (uint16_t)_package->distance[1] * 255;
    return distance < 300 ? distance : 300;
}

uint16_t TFLuna::get_strength(){
    uint16_t strength = _package->strength[0] + (uint16_t)_package->strength[1] * 255;
    return strength;
}

uint8_t TFLuna::get_chip_temperature(){
    float chip_temperature = _package->chip_temperature[0] + (uint16_t)_package->chip_temperature[1] * 255;
    chip_temperature = (uint8_t)(chip_temperature / 8 - 256);
    return chip_temperature;
}
