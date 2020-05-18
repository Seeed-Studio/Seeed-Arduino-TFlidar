#include"TFLuna.h"

char getversion[4]={0x5a,0x04,0x01,0x5f};//Get firmware version
char reset[4]={0x5a,0x04,0x02,0x60};//reset
char enable[5]={0x5a,0x05,0x07,0x00,0x66};//Enable data output
char disable[5]={0x5a,0x05,0x07,0x01,0x67};//Disable data output 
char UART[5]={0x5a,0x05,0x0a,0x00,0x69};//Modify communication mode to UART
char I2C[5]={0x5a,0x05,0x0a,0x01,0x6a};//Modify communication mode to I2C
char samplerate_01[6]={0x5a,0x06,0x03,0x01,0x00,0x64};//Set the frame rate  to 1Hz  
char samplerate_10[6]={0x5a,0x06,0x03,0x0a,0x00,0x6d};//Set the frame rate  to 10Hz 
char samplerate_100[6]={0x5a,0x06,0x03,0x64,0x00,0xc7};//Set the frame rate  to 100Hz 
char factoryreset[4]={0x5a,0x04,0x10,0x6e};//Restore factory settings
char save[4]={0x5a,0x04,0x11,0x6f};//save

//The response of TFmini Plus. Note: Output frame rate, output enable switch, return command; Modify communication mode, no response, execute directly
//The response after getting firmware versions
int return_version[7]={0};
//The response after setting samplerate
int return_samplerate[6]={0};
//The response after setting enable switch
int return_switch[5]={0};
//The response after resetting
int return_reset[5]={0};
char reset_success[5]={0x5a,0x05,0x02,0x00,0x60};
char reset_fail[5]={0x5a,0x05,0x02,0x01,0x61};
//The response after restoring factory settings
int return_factoryreset[5]={0};
char factoryreset_success[5]={0x5a,0x05,0x10,0x00,0x6e};
char factoryreset_fail[5]={0x5a,0x05,0x10,0x01,0x6f};
//The response after saving
int return_save[5]={0};
char save_success[5]={0x5a,0x05,0x11,0x00,0x70};
char save_fail[5]={0x5a,0x05,0x11,0x01,0x71};

//prompt information
String info_getversion="get version ok";
String info_reset="reset ok";
String info_enable="enable ok";
String info_disable="get version ok";
String info_UART="UART ok";
String info_I2C="I2C ok";
String info_samplerate_01="samplerate_01 ok";
String info_samplerate_10="samplerate_10 ok";
String info_samplerate_100="samplerate_100 ok";
String info_factoryreset="factoryreset ok";
String info_save="save ok";

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
        Serial.print(_package->header[index],HEX);
        Serial.print(" ");
    }        
    for(uint8_t index = 0 ;index < 2 ;index++){
        Serial.print(_package->distance[index],HEX);
        Serial.print(" ");
    }
    for(uint8_t index = 0 ;index < 2 ;index++){
        Serial.print(_package->strength[index],HEX);
        Serial.print(" ");
    }        
    for(uint8_t index = 0 ;index < 2 ;index++){
        Serial.print(_package->chip_temperature[index],HEX);
        Serial.print(" ");
    }      
    Serial.println(_package->checksum & 0xff,HEX);
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

uint16_t TFLuna::get_version(){
    configure(getversion,sizeof(getversion),return_version\
    ,sizeof(return_version)/sizeof(int),info_getversion);
    return true;
}

bool TFLuna::set_output_status(bool status){
    if(status){
        if(configure(enable,sizeof(enable),return_switch,enable\
        ,sizeof(return_switch)/sizeof(int),info_enable)){
            return true;
        }
    }
    else{
        if(configure(disable,sizeof(disable),return_switch,disable\
        ,sizeof(return_switch)/sizeof(int),info_disable)){
            return true;
        }
    }
    return false;
}
bool TFLuna::set_frame_rate(samplerate_mode mode){
    if(SAMPLERATE_1HZ == mode){
        if(configure(samplerate_01,sizeof(samplerate_01),return_samplerate,samplerate_01 \
        ,sizeof(return_samplerate)/sizeof(int),info_samplerate_01)){
            return true;
        }
    }
    else if (SAMPLERATE_10HZ == mode){
        if(configure(samplerate_10,sizeof(samplerate_10),return_samplerate,samplerate_10 \
        ,sizeof(return_samplerate)/sizeof(int),info_samplerate_10)){
            return true;
        }
    }
    else if (SAMPLERATE_100HZ == mode){
        if(configure(samplerate_100,sizeof(samplerate_100),return_samplerate,samplerate_100 \
        ,sizeof(return_samplerate)/sizeof(int),info_samplerate_100)){
            return true;
        }
    }else
    {
        return false;
    }
    return false;
}

bool TFLuna::reset_device(){
    if(configure(reset,sizeof(reset),return_reset,\
    reset_success,sizeof(return_reset)/sizeof(int),info_reset)){
        return true;
    };
    return false;
}

bool TFLuna::factory_reset(){
    if(configure(factoryreset,sizeof(factoryreset),return_factoryreset,\
    factoryreset_success,sizeof(return_factoryreset)/sizeof(int),info_factoryreset)){
        return true;
    }
    return false;
}

bool TFLuna::save_config(){
    if(configure(save,sizeof(save),return_save,save_success,\
    sizeof(return_save)/sizeof(int),info_save)){
        return true;
    }
    return false;
}


bool TFLuna::configure(char down[],int n1,int buff[],char up[],int n2,String info){
    for(uint8_t i=0;i<n1;i++){
        _TFTransporter->write(down[i]);
    }
    uint8_t num=0;
    while(!_TFTransporter->available());
    while (_TFTransporter->available()){
        if(_TFTransporter->read()==0x5a){ //assess communication protocol frame header 0x5a
            buff[0]=0x5a;
            for(uint8_t i=1;i<n2;i++){
                buff[i]=_TFTransporter->read();
                #ifdef DEBUG_EN
                Serial.print(buff[i],HEX);
                Serial.print('\t');
                #endif
            }
            for(uint8_t i=0;i<n2;i++){
                #ifdef DEBUG_EN
                Serial.print(up[i],HEX);
                Serial.print('\t');
                #endif                
                if(buff[i]==up[i]){
                #ifdef DEBUG_EN
                Serial.print(buff[i],HEX);
                Serial.print('\t');
                #endif
                num++;
                }    
            }
            if(num==n2){
                num=0;
                #ifdef DEBUG_EN
                Serial.print(info);
                Serial.print('\n'); 
                #endif
                return true;
            }
            return false;
        }
    }  
}

bool TFLuna::configure(char down[],int n1,int buff[],int n2,String info)
{
    for(uint8_t i=0;i<n1;i++){
        _TFTransporter->write(down[i]);
    }
    while(!_TFTransporter->available());
    while(_TFTransporter->available()){
        if(_TFTransporter->read()==0x5a){ //assess communication protocol frame header 0x5a
            buff[0]=0x5a;
            for(uint8_t i=1;i<n2;i++){
                buff[i]=_TFTransporter->read();
            }
        #ifdef DEBUG_EN
        for(uint8_t i=0;i<n2;i++){
            Serial.print(buff[i],HEX);  
            Serial.print('\t');
        }
        Serial.print(info);
        Serial.print('\n');
        #endif 
        return true;
        }
    } 
}

bool TFLuna::configure(char down[],int n1,String info)
{
    for(uint8_t i=0;i<n1;i++){
        _TFTransporter->write(down[i]);
    } 
#ifdef DEBUG_EN
  Serial.print(info);
  Serial.print('\n');  
#endif 
    return true;
}