#include <Arduino.h>
#include "moodaDHT.h"
#include "DHT.h"

#define DHTPIN     16     // Pino conectado ao sensor (tem que ser RX)
#define DHTTYPE    DHT11   // Definição do tipo do DHT (11 ou 22)

MoodaDHT::MoodaDHT()
{
}

/************************
 MoodaDHT::init
 init
    inicializa o sensor DHT
    
 saidas
    nenhuma
*************************/
void MoodaDHT::init(void)
{
    dht = new DHT(DHTPIN, DHTTYPE);
    dht -> begin();
}

/************************
 MoodaDHT::getT
 getT
    pega dados de temperatura do sensor DHT
    
 saidas
    float temperatura [C]
*************************/
float MoodaDHT::getT(void)
{
    float t = dht -> readTemperature(); //Pega temperatura em Celsius

    return t;
}

/************************
 MoodaDHT::getH
 getH
    pega dados de umidade do sensor DHT
    
 saidas
    float umidade do ar [%]
*************************/
float MoodaDHT::getH(void)
{
    float h = dht -> readHumidity(); //Pega dados de umidade do ar

    return h;
}