#include <Arduino.h>
#include "moodaLCD.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

MoodaLCD::MoodaLCD()
{
}

/************************
 MoodaLCD::init
get
    inicializa o lcd 
    
saidas
    nenhuma
*************************/

void MoodaLCD::init(void)
{
    lcd = new LiquidCrystal_I2C(0x27, 20, 4); //endereço 0x27, display 16x2
    lcd -> init(); 
    lcd -> backlight(); //liga a luz de fundo
}

/************************
 MoodaLCD::off
off
    limpa e desliga a luz do lcd 
    
saidas
    nenhuma
*************************/

void MoodaLCD::off(void)
{
    lcd -> clear(); //limpa a tela
    lcd -> noBacklight(); //desliga a luz de fundo
}

/************************
 MoodaLCD::show
show
    coloca o nível da planta no display 
    
saidas
    nenhuma
*************************/

void MoodaLCD::show(int happiness, float display_luz, float display_co2, int display_agua, float display_temperatura)
{
    int index = happiness+1;
    lcd -> clear(); //limpa a tela
    lcd -> backlight(); //liga a luz de fundo 

     //Cria os bytes
    byte vaso[] = {
    B00100, B00101, B00111, B00100,
    B11111, B01110, B01110, B01110 };
    
    byte cinco_1[] = {
    B00000, B00000, B00001, B00001,
    B00110, B01000, B10001, B10010 };
    byte cinco_2[] = {
    B01110, B10001, B00000, B00000,
    B00000, B00000, B10001, B01010 };
    byte cinco_3[] = {
    B00000, B00000, B10000, B10000,
    B01100, B00010, B10001, B01001 };
    byte cinco_4[] = {
    B10000, B10000, B01000, B00110,
    B00001, B00001, B00000, B00000 };
    byte cinco_5[] = {
    B00000, B00000, B10001, B01110, 
    B00000, B00000, B10001, B01110 };
    byte cinco_6[] = {
    B00001, B00001, B00010, B01100,
    B10000, B10000, B00000, B00000 };

    byte quatro_1[] = {
    B00000, B00000, B00001, B00001,
    B00110, B01000, B10001, B10001 };
    byte quatro_2[] = {
    B01110, B10001, B00000, B00000,
    B00000, B00000, B10001, B10001 };
    byte quatro_3[] = {
    B00000, B00000, B10000, B10000,
    B01100, B00010, B10001, B10001 };
    byte quatro_4[] = {
    B10000, B10000, B01000, B00110,
    B00001, B00001, B00000, B00000 };
    byte quatro_5[] = {
    B00000, B00000, B10001, B01110, 
    B00000, B00000, B10001, B01110 };
    byte quatro_6[] = {
    B00001, B00001, B00010, B01100,
    B10000, B10000, B00000, B00000 };

    byte tres_1[] = {
    B00000, B00000, B00001, B00001,
    B00110, B01000, B10001, B10001 };
    byte tres_2[] = {
    B01110, B10001, B00000, B00000,
    B00000, B00000, B10001, B10001 };
    byte tres_3[] = {
    B00000, B00000, B10000, B10000,
    B01100, B00010, B10001, B10001 };
    byte tres_4[] = {
    B10000, B10000, B01000, B00110,
    B00001, B00001, B00000, B00000 };
    byte tres_5[] = {
    B00000, B00000, B00000, B01110, 
    B00000, B00000, B10001, B01110 };
    byte tres_6[] = {
    B00001, B00001, B00010, B01100,
    B10000, B10000, B00000, B00000 };

    byte dois_1[] = {
    B00000, B00000, B00001, B00001,
    B00110, B01000, B10001, B10001 };
    byte dois_2[] = {
    B01110, B10001, B00000, B00000,
    B00000, B00000, B10001, B10001 };
    byte dois_3[] = {
    B00000, B00000, B10000, B10000,
    B01100, B00010, B10001, B10001 };
    byte dois_4[] = {
    B10000, B10000, B01000, B00110,
    B00001, B00001, B00000, B00000 };
    byte dois_5[] = {
    B00000, B01110, B10001, B00000, 
    B00000, B00000, B10001, B01110 };
    byte dois_6[] = {
    B00001, B00001, B00010, B01100,
    B10000, B10000, B00000, B00000 };

    byte um_1[] = {
    B00000, B00000, B00001, B00001,
    B00110, B01001, B10000, B10001 };
    byte um_2[] = {
    B01110, B10001, B00000, B00000,
    B00000, B01010, B10001, B01010 };
    byte um_3[] = {
    B00000, B00000, B10000, B10000,
    B01100, B10010, B00001, B10001 };
    byte um_4[] = {
    B10000, B10000, B01000, B00110,
    B00001, B00001, B00000, B00000 };
    byte um_5[] = {
    B00000, B00000, B00100, B01010, 
    B00100, B00000, B10001, B01110 };
    byte um_6[] = {
    B00001, B00001, B00010, B01100,
    B10000, B10000, B00000, B00000 };

    lcd -> createChar(0, vaso);
    if (happiness == 0) index = 5;

    switch(index){
        case 1:
            lcd -> createChar(1, um_1);
            lcd -> createChar(2, um_2);
            lcd -> createChar(3, um_3);
            lcd -> createChar(4, um_4);
            lcd -> createChar(5, um_5);
            lcd -> createChar(6, um_6);
            break;
        case 2:
            lcd -> createChar(1, dois_1);
            lcd -> createChar(2, dois_2);
            lcd -> createChar(3, dois_3);
            lcd -> createChar(4, dois_4);
            lcd -> createChar(5, dois_5);
            lcd -> createChar(6, dois_6);
            break;
        case 3:
            lcd -> createChar(1, tres_1);
            lcd -> createChar(2, tres_2);
            lcd -> createChar(3, tres_3);
            lcd -> createChar(4, tres_4);
            lcd -> createChar(5, tres_5);
            lcd -> createChar(6, tres_6);
            break;
        case 4:
            lcd -> createChar(1, quatro_1);
            lcd -> createChar(2, quatro_2);
            lcd -> createChar(3, quatro_3);
            lcd -> createChar(4, quatro_4);
            lcd -> createChar(5, quatro_5);
            lcd -> createChar(6, quatro_6);
            break;
        case 5:
            lcd -> createChar(1, cinco_1);
            lcd -> createChar(2, cinco_2);
            lcd -> createChar(3, cinco_3);
            lcd -> createChar(4, cinco_4);
            lcd -> createChar(5, cinco_5);
            lcd -> createChar(6, cinco_6);
            break;
    }

    lcd -> setCursor(1,0);
    lcd -> print(index);

    lcd -> setCursor(0,1);
    lcd -> write(1);

    lcd -> setCursor(1,1);
    lcd -> write(2);

    lcd -> setCursor(2,1);
    lcd -> write(3);

    lcd -> setCursor(0,2);
    lcd -> write(4);

    lcd -> setCursor(1,2);
    lcd -> write(5);

    lcd -> setCursor(2,2);
    lcd -> write(6);

    lcd -> setCursor(1, 3);
    lcd -> write(0);

    lcd -> setCursor(4,0);
    lcd -> print("Luz: "); lcd -> print(display_luz, 2); lcd -> print(" lm");

    lcd -> setCursor(4,1);
    lcd -> print("CO2: "); lcd -> print(display_co2, 2); lcd -> print(" ppm");

    lcd -> setCursor(4,2);
    lcd -> print("Agua: "); lcd -> print(display_agua); lcd -> print(" %");

    lcd -> setCursor(4,3);
    lcd -> print("Temp: "); lcd -> print(display_temperatura, 2); lcd -> print(" \xDF" "C");
}