#include <Arduino.h>
#include "moodaWIFI.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <Regexp.h>
#include "esp_wpa2.h"

// #define NETWORK_TYPE 1 // Empresarial: 1; Doméstica: 0
// #define EAP_IDENTITY "" // Somente empresarial
// #define EAP_PASSWORD "" // Empresarial: senha única USP; Doméstica: senha da rede
#define NETWORK_TYPE 0 // Empresarial: 1; Doméstica: 0
#define EAP_IDENTITY "" // Somente empresarial
#define EAP_PASSWORD "" // Empresarial: senha única USP; Doméstica: senha da rede
#define SERVER "https://mood-a.herokuapp.com/api/sensors" // "http://192.168.0.52:3001/api/sensors";

MoodaWIFI::MoodaWIFI()
{
}

/************************
 MoodaWIFI::init
 init
    inicializa WIFI
    
saidas
    nenhuma
*************************/

void MoodaWIFI::init(void)
{
    const char* ssid = "Lamparina300%"; // Empresarial: eduroam; Doméstica: nome da rede

    WiFi.mode(WIFI_STA);  //Station Mode

    WiFi.disconnect(true); // Assegura que não há conexões

    if (NETWORK_TYPE) {
        WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_IDENTITY, EAP_IDENTITY, EAP_PASSWORD);
    } else {
        WiFi.begin(ssid, EAP_PASSWORD);
    }
}

/************************
 MoodaWIFI::get
 get
    envia os dados de luminosidade, temperatura, umidade do solo, umidade relativa do ar, concentração de CO2, presença e recebe felicidade
    
saidas
    float felicidade
*************************/

float MoodaWIFI::get(float luminosity, float temperature, int soilMoisture, float airMoisture, float airQuality, int presence)
{
    float happiness;
    
    if (WiFi.localIP().toString() != "0.0.0.0") {
    // Converte leituras para strings
    String lm = String(luminosity, DEC);
    String tp = String(temperature, DEC);
    String sm = String(soilMoisture, DEC);
    String am = String(airMoisture, DEC);
    String aq = String(airQuality, DEC);
    String ps = String(presence, DEC);

    // Cria string para POST
    String toSend = "luminosity="   + lm + "&"
                    "temperature="  + tp + "&"
                    "soilMoisture=" + sm + "&"
                    "airMoisture="  + am + "&"
                    "airQuality="   + aq + "&"
                    "presence="     + ps;

    // Variáveis auxiliares
    char httpResponseBuff[800];
    char regexMatchBuff[5];
    
    // Inicializa e configura cliente HTTP para POST
    HTTPClient http;
    http.begin(SERVER);
    http.addHeader("Content-Type", "text/plain");

    int httpResponseCode = http.POST(toSend);

    if (httpResponseCode > 0) {

      // Obtém e armazena resposta do servidor
      http.getString().toCharArray(httpResponseBuff, 800);

      // Extrai felicidade
      MatchState regex;
      regex.Target(httpResponseBuff);
      char matchResult = regex.Match("(\"overall\":([0-9].[0-9]*))");

      if (matchResult == REGEXP_MATCHED) {
        // Armazena felicidade (correspondência de nível 1)
        regex.GetCapture(regexMatchBuff, 1);
      }

      // Converte felicidade para float
      happiness = String(regexMatchBuff).toFloat();

    } 

    http.end();
  } 

  return happiness;
}
