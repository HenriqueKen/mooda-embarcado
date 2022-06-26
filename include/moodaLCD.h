#ifndef MOODALCD_H_INCLUDED
#define MOODALCD_H_INCLUDED
#include <LiquidCrystal_I2C.h>

class MoodaLCD {
  public:
  MoodaLCD();
  LiquidCrystal_I2C* lcd;


  /************************
  init
    inicializa componente

  show
    Mostra nível da planta

  off
    Limpa e desliga display
    
  saidas
    nenhuma
    display nível da planta
    
  *************************/
  void init(void);
  void show(int n);
  void off(void);
};

#endif // MOODALCD_H_INCLUDED
