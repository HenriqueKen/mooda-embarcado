#ifndef MOODAPIR_H
#define MOODAPIR_H

class MoodaPIR {
  public:
  MoodaPIR();

  /************************
  init
    inicializa componente
  
  get
    pega dados do sensor PIR
  
  saidas
    nenhuma
    int presente
  *************************/
  void init(void);
  int get(void);
};

#endif // MOODAPIR_H
