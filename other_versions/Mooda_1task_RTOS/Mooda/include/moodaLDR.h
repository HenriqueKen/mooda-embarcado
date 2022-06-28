#ifndef MOODALDR_H
#define MOODALDR_H

class MoodaLDR {
  public:
  MoodaLDR();

  /************************
  get
    pega dados do sensor LDR
    
  saidas
    nenhuma
    luminosidade [lux]
  *************************/
  float get(void);
};

#endif // MOODALDR_H
