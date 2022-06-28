#ifndef MOODALM393_H_INCLUDED
#define MOODALM393_H_INCLUDED

class MoodaLM393 {
  public:
  MoodaLM393();

  /************************
   get
    pega dados do sensor LM393
    
  saidas
    int umidade do solo [%] 
  *************************/
  int get(void);
};

#endif // MOODALM393_H_INCLUDED
