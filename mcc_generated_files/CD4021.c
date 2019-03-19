/*
 * File:   CD4021.c
 * Author: user
 *
 * Created on March 19, 2019, 12:54 PM
 */


#include "CD4021.h"
#include "mcc.h"
static uint8_t CD4021Buffer;

void CD4021Driver(){
    uint8_t Data = 0x00; 
    CD4021_PS_LAT = LOW;
    NOP();
    CD4021_PS_LAT = HIGH;
    NOP();
    CD4021_PS_LAT = LOW;
    for(int i=0;i<16;i++){
        NOP();
        Data = (Data<<1);
        CD4021_Clock_LAT = LOW;
        Data |= (CD4021_Data_PORT & 0x01);
        NOP();
        CD4021_Clock_LAT = HIGH;
    }
    CD4021Buffer = Data;
    return;
}
uint8_t CD4021Read(){
    return CD4021Buffer;
}
