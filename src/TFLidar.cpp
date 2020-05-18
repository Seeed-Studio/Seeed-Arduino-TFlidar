#include "TFLidar.h"

TFLidar::TFLidar(TFBase *TF_Lidar){
    _TF_Lidar = TF_Lidar;
}

void TFLidar::begin(SoftwareSerial *TFSerial,unsigned long baud_rate){
    _TF_Lidar->begin(TFSerial,baud_rate);
}

void TFLidar::begin(HardwareSerial *TFSerial,unsigned long baud_rate){
    _TF_Lidar->begin(TFSerial,baud_rate);
}

uint16_t TFLidar::get_distance(){
    return _TF_Lidar->get_distance();
}

uint16_t TFLidar::get_strength(){
    return _TF_Lidar->get_strength();
}

uint16_t TFLidar::get_chip_temperature(){
    return _TF_Lidar->get_chip_temperature();
}