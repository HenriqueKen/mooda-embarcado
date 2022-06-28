#include <Arduino.h>
#include "moodaPIR.h"

#define PIN_PIR 35 //Pino conectao ao sensor

MoodaPIR::MoodaPIR()
{
}

/************************
 MoodaPIR::init
init
    inicializa o sensor PIR
    
saidas
    nenhuma
*************************/

void MoodaPIR::init(void)
{
    pinMode(PIN_PIR, INPUT);    //define entrada do sensor como input
}

/************************
 MoodaPIR::get
 get
    pega dados do sensor PIR
    
saidas
    int presente
*************************/
int MoodaPIR::get(void)
{
    int presente = 0;

    if (digitalRead(PIN_PIR) == HIGH) { // check if the sensor is HIGH
        presente = 1;
    } 

    return presente;
}
