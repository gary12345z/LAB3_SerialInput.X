/*
 * File:   _4094.c
 * Author: user
 *
 * Created on March 19, 2019, 12:42 PM
 */


#include "CD4094.h"
#include "mcc.h"
union Buffer16{
    struct{
        uint8_t BufferH;
        uint8_t BufferL;
    };
    uint16_t Buffer;
};
static union Buffer16 CD4094Buffer;

void CD4094Driver(){
    uint16_t Data = CD4094Buffer.Buffer; 
    CD4094_Strobe_LAT = LOW;
    for(int i=0;i<16;i++){
        uint16_t pushBit = (Data&0x01);
        CD4094_Clock_LAT = LOW;
        CD4094_Data_LAT = (pushBit)?LOW:HIGH;  //LOW = Turn ON / HIGH = Turn OFF
        NOP();
        CD4094_Clock_LAT = HIGH;
        Data=(Data>>1);
        NOP();
    }
    CD4094_Clock_LAT = HIGH;
    CD4094_Strobe_LAT = HIGH;
    //Data DON'T CARE
    NOP();
    CD4094_Clock_LAT = HIGH;
    CD4094_Strobe_LAT = LOW;
    //Data DON'T CARE
    NOP();
    return;
}
void CD4094Write16(uint16_t Buffer){
    CD4094Buffer.Buffer = Buffer;
}
void CD4094WriteH(uint8_t BufferH){
    CD4094Buffer.BufferH = BufferH;
}
void CD4094WriteL(uint8_t BufferL){
    CD4094Buffer.BufferL = BufferL;
}