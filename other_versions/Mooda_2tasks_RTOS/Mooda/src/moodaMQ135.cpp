#include <Arduino.h>
#include "moodaMQ135.h"
#include <MQUnifiedsensor.h>

#define PLACA "ESP-32"             //Definição de placa utilizada
#define VOLTAGE_RESOLUTION 5       //Tensão conectada ao sensor
#define PIN 34                     //Pino conectao ao sensor
#define TYPE "MQ-135"              //Qual MQ está sendo utilizado
#define ADC_BIT_RESOLUTION 12      //Resolução da conversão ADC
#define RATIO_MQ135_CLEAN_AIR 3.6  //Relação de resistencia de referência  


MoodaMQ135::MoodaMQ135()
{
}

/************************
 MoodaMQ135::init
 init
    inicializa o sensor MQ135
    
saidas
    nenhuma
*************************/

void MoodaMQ135::init(void)
{
    // MQUnifiedsensor MQ135(PLACA, VOLTAGE_RESOLUTION, ADC_BIT_RESOLUTION, PIN, TYPE);
    MQ135 = new MQUnifiedsensor(PLACA, VOLTAGE_RESOLUTION, ADC_BIT_RESOLUTION, PIN, TYPE);
    MQ135 -> setRegressionMethod(1); //Define como regressão linear
    MQ135 -> init(); //Inicializa o componente

    float calcR0 = 0;
    for(int i = 1; i<=10; i ++)
    {
        MQ135 -> update(); //faz aquisição de dado inicial
        calcR0 += MQ135 -> calibrate(RATIO_MQ135_CLEAN_AIR);
    }
    MQ135 -> setR0(calcR0/10); //Define o valor da resistencia de referência
    MQ135 -> serialDebug(false);
}

/************************
 MoodaMQ135::get
 get
    pega dados do sensor MQ135
    
saidas
    float concentração de CO2 [ppm]
*************************/

float MoodaMQ135::get(void)
{
    float CO2 = 0;
    MQ135 -> update(); //faz aquisição de dados
 
    MQ135 -> setA(110.47); MQ135 -> setB(-2.862); //determina os valores para regressão linear
    //https://www.ecodebate.com.br/2021/03/17/a-concentracao-de-co2-e-a-mais-alta-em-milhoes-de-anos/
    CO2 = MQ135 -> readSensor() + 416;

    return CO2;
}

MoodaMQ135::~MoodaMQ135()
{
    delete MQ135;
}