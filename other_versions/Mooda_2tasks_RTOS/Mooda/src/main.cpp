#define NUM_ESTADOS 2
#define NUM_EVENTOS 3

#include <Arduino.h>

#include "moodaDHT.h"
#include "moodaLDR.h"
#include "moodaLM393.h"
#include "moodaMQ135.h"
#include "moodaPIR.h"
#include "moodaWIFI.h"
#include "moodaLCD.h"


/***********************************************************************
 Componentes
 ***********************************************************************/
MoodaDHT mdht;
MoodaLDR mldr;
MoodaLM393 mlm393;
MoodaMQ135 mmq135;
MoodaPIR mpir;
MoodaWIFI mwifi;
MoodaLCD mlcd;


// -------------------------------------------------------
// Variáveis globais
float luminosity= 0; 
float temperature = 0;
int soilMoisture = 0;
float airMoisture = 0;
float airQuality = 0;
int presence = 0;
int happiness = 0;

double sumLuminosity = 0;
double sumTemperature = 0;
double sumSoilmoisture = 0;
double sumAirmoisture = 0;
double sumAirquality = 0;
double sumPresence = 0;

float display_luz = 0;
float display_co2 = 0;
int display_agua = 0;
float display_temperatura = 0;

int leituraAntiga = 0;
int leituraAtual = 0;
int numeroAquisicoes = 0;
int sendNow = 1;

// -------------------------------------------------------
//FreeRTOS
 
void taskMaqEstados(void *pvParameters);
void taskObterEvento(void *pvParameters);
void taskEnvio(void *pvParameters);
QueueHandle_t xQueue;
SemaphoreHandle_t xBinarySemaphore;
TaskHandle_t xTaskMaqEstados, xTaskObterEvento, xTaskEnvio;


// -------------------------------------------------------
// Enums

// Cria tipo de dado
enum state
{
    DISPLAY_STATUS,
    IDLEE
};
state estado = IDLEE; // Cria variável do tipo de dado criado

enum event
{
    NENHUM_EVENTO = -1,
    DETECTOU_PRESENCA,
    MONITORACAO,
    ATINGIU_5_MIN
};
event evento;

enum action
{
    NENHUMA_ACAO = -1,
    LIGAR_DISPLAY_STATUS,
    DESLIGAR_DISPLAY_STATUS,
    AQUISICAO_E_ENVIO
};
action acao;

// -------------------------------------------------------
// Structs 

typedef struct transition // Cria tipo de dado
{
    state proximoEstado;
    action acao;
} transition;

// Cria variável do tipo de dado criado
transition matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS] = {
    {{DISPLAY_STATUS, NENHUMA_ACAO}, {DISPLAY_STATUS, AQUISICAO_E_ENVIO}, {IDLEE, DESLIGAR_DISPLAY_STATUS}},
    {{DISPLAY_STATUS, LIGAR_DISPLAY_STATUS}, {IDLEE, AQUISICAO_E_ENVIO}, {IDLEE, NENHUMA_ACAO}}};

// -------------------------------------------------------
// Declara Funções (são definidas posteriormente)
event obterEvento();
action obterAcao(state estado, event evento);
state obterProximoEstado(state estado, event evento);
void executarAcao(action acao);

/***********************************************************************
 Tasks
 ***********************************************************************/

/************************************************************************
 taskMaqEstados
 Task principal de controle que executa a maquina de estados
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void taskMaqEstados(void *pvParameters) {

  for( ;; ) {

    evento = obterEvento();

    if (evento != NENHUM_EVENTO)
    {
        acao = obterAcao(estado, evento);
        estado = obterProximoEstado(estado, evento);
        executarAcao(acao);
    }

    }
    
}

/************************************************************************
 taskEnvio
 Task que envia os dados periodicamente a cada 10min
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void taskEnvio(void *pvParameters) {
  TickType_t xLastWakeTime;
  const TickType_t xDelay10min = pdMS_TO_TICKS( 30000 ); //600000

  for( ;; ) {
    xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
    xLastWakeTime = xTaskGetTickCount();

    vTaskDelayUntil( &xLastWakeTime, xDelay10min );
    
    sendNow = 1;

  }
}



// =========================================================================================
// Setup

void setup()
{
    pinMode(2, OUTPUT);
    Serial.begin(115200);
    mdht.init();
    mmq135.init();
    mpir.init();
    mwifi.init();
    mlcd.init();


    // configure tasks
    xBinarySemaphore = xSemaphoreCreateBinary();
    
    if(xBinarySemaphore != NULL)
    {
        xTaskCreate(taskMaqEstados,"taskMaqEstados", 100000, NULL, 1, &xTaskMaqEstados);
        xTaskCreate(taskEnvio,"taskEnvio", 100000, NULL, 2, &xTaskEnvio);
    }
    else
    {
        /* The queue or semaphore could not be created. */
    }

}

// =========================================================================================
// Loop
void loop(){
}

// =========================================================================================
// Funções

event obterEvento()
{
    leituraAtual = mpir.get();
    if ((leituraAtual) && (!leituraAntiga) ){
        leituraAntiga = leituraAtual;
        return DETECTOU_PRESENCA;
    }

    if ((!leituraAtual) && (leituraAntiga)){
        leituraAntiga = leituraAtual;
        return ATINGIU_5_MIN;
    }

    leituraAntiga = leituraAtual;
    return MONITORACAO;

}

action obterAcao(state estado, event evento)
{
    return matrizTransicaoEstados[estado][evento].acao;
};

state obterProximoEstado(state estado, event evento)
{
    return matrizTransicaoEstados[estado][evento].proximoEstado;
};

void executarAcao(action acao)
{
    if (acao == NENHUMA_ACAO)
        return;

    switch (acao)
    {
    case LIGAR_DISPLAY_STATUS:
        mlcd.init();
        mlcd.show(happiness, display_luz, display_co2, display_agua, display_temperatura);
        break;
    case DESLIGAR_DISPLAY_STATUS:
        mlcd.off();
        break;
    case AQUISICAO_E_ENVIO:
        luminosity= mldr.get(); 
        temperature = mdht.getT();
        soilMoisture = mlm393.get();
        airMoisture = mdht.getH();
        airQuality = mmq135.get();
        presence = mpir.get();
        
        sumLuminosity += luminosity;
        sumTemperature += temperature;
        sumSoilmoisture += soilMoisture;
        sumAirmoisture += airMoisture;
        sumAirquality += airQuality;
        sumPresence += presence;
 
        display_luz = luminosity; 
        display_co2 = airQuality;
        display_agua = soilMoisture;
        display_temperatura = temperature;

        numeroAquisicoes +=1;

        if (sendNow){
            luminosity = sumLuminosity/numeroAquisicoes;
            temperature = sumTemperature/numeroAquisicoes;
            soilMoisture = sumSoilmoisture/numeroAquisicoes;
            airMoisture = sumAirmoisture/numeroAquisicoes;
            airQuality = sumAirquality/numeroAquisicoes;
            presence = round(sumPresence/numeroAquisicoes);

            happiness = mwifi.get(luminosity, temperature, soilMoisture, airMoisture, airQuality, presence);

            sumLuminosity = 0;
            sumTemperature = 0;
            sumSoilmoisture = 0; 
            sumAirmoisture = 0;
            sumAirquality = 0;
            sumPresence = 0;

            numeroAquisicoes = 0;
            sendNow = 0;
            xSemaphoreGive( xBinarySemaphore);
        }
        
        break;
    }
}
