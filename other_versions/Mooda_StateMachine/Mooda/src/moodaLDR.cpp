#include <Arduino.h>
#include "moodaLDR.h"

#define LDR_PIN                   39          //Pino conectado ao sensor
#define MAX_ADC_READING           4095        //Máximo valor de leitura de entrada ADC
#define ADC_REF_VOLTAGE           5.0         //Tensão conectada ao sensor
#define REF_RESISTANCE            10000       //Valor do resistor utilizado 
#define LUX_CALC_SCALAR           3129.73275  //Escalar do cálculo de lumen
#define LUX_CALC_EXPONENT         1.405       //Expoente do cálculo de lumen

MoodaLDR::MoodaLDR()
{
}

/************************
 MoodaLDR::get
 get
    pega dados do sensor LDR 
    
saidas
    float luminosidade [lux]
*************************/

float MoodaLDR::get(void)
{
    int   ldrRawData;
    float resistorVoltage, ldrVoltage;
    float ldrResistance;
    float ldrLux;
     
    ldrRawData = analogRead(LDR_PIN); //Pega dado do componente

    resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE; //Tensão sobre o resistor
    ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage; //Tensão sobre o LDR
    ldrResistance = ldrVoltage/resistorVoltage * REF_RESISTANCE; //Calculo da resistencia do LDR
    
    ldrLux = pow(ldrResistance, LUX_CALC_EXPONENT)/LUX_CALC_SCALAR; //Conta para obter em lumen
    
    return ldrLux;
}
