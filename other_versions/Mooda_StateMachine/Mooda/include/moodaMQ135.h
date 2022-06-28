#ifndef MOODAMQ135_H
#define MOODAMQ135_H
#include <MQUnifiedsensor.h>

class MoodaMQ135 {
  public:
  MoodaMQ135();
  ~MoodaMQ135();
  MQUnifiedsensor* MQ135;

  /************************
   get
    pega dados do sensor MQ135
  
  init
    inicializa componente
    
  saidas
    float concentração de CO2 [ppm]
    nenhuma
  *************************/
  void init(void);
  float get(void);
};

#endif // MOODAMQ135_H
