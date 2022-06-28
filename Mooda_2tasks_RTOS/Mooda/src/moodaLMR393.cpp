#include <Arduino.h>
#include "moodaLM393.h"

#define SENSOR_PIN 36 //Pino conectado ao sensor

MoodaLM393::MoodaLM393()
{
}

/************************
 MoodaLM393::get
 get
    pega dados do sensor LM393
    
saidas
    int umidade do solo [%]
*************************/

int MoodaLM393::get(void)
{
    int value; 

    value= analogRead(SENSOR_PIN); //Faz leitura do valor do sensor
    value = map(value,4095,0,0,100); //Faz conversão para valor em porcentagem

    return value;
}
