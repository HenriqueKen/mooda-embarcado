#ifndef MOODADHT_H_INCLUDED
#define MOODADHT_H_INCLUDED
#include "DHT.h"

class MoodaDHT {
  public:
  MoodaDHT();
  DHT* dht;


  /************************
  init
    inicializa componente

  getH
    pega dados de umidade do sensor DHT
  
  getT
    pega dados de temperatura do sensor DHT
    
  saidas
    nenhuma
    float umidade do ar [%]
    float temperatura [C]
  *************************/
  void init(void);
  float getH(void);
  float getT(void);
};

#endif // MOODADHT_H_INCLUDED
