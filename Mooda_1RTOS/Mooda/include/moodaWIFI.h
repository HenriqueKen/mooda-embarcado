#ifndef MOODAWIFI_H
#define MOODAWIFI_H

class MoodaWIFI {
  public:
  MoodaWIFI();

  /************************
  init
    inicializa Wi-Fi
  
  get
    pega dados do sensor Wi-Fi
    
  saidas
    nenhuma
    float felicidade
  *************************/
  void init(void);
  float get(float luminosity, float temperature, int soilMoisture, float airMoisture, float airQuality, int presence);
};

#endif // MOODAWIFI_H
