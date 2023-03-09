#include <Arduino_FreeRTOS.h>

#define RED    6
#define BLUE   7
#define YELLOW 8

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler BlueLEDProfiler;
// 1. to sa moje pvParameters - wskazniki do funkcji to na co pokazują
const uint16_t *blueLed = (uint16_t *) BLUE;// wskaznik stały typu unsigned int 16 bitowy 2bajtowy
// do pokazywania na pin BLUE(7)
// nie moze zmieniac to na co pokazuje cast - formatowanie
// stały wskaznik do pokazywania na port BLUE, mozna go przesuwać ale nie moża zmieniać tego na co pokazuje
const uint16_t *redLed = (uint16_t *) RED;
const uint16_t *yellowLed =(uint16_t *)YELLOW;
void setup()
{
  xTaskCreate(LedControllerTask,"RED LED Task",100,(void *)redLed,1,NULL);  // trzecia pozycja od konca to pv parameters
  // castuje bo to bedzie funkcja, chodzi nam o to ze to bedzie parametr zwracany z funkcji w postaci wskaznika
  xTaskCreate(LedControllerTask,"YELLOW LED TASK",100,(void *)yellowLed,1,NULL);
  // jak bym podał samo redLED to bym podał adres w pamięci a ja musz podac wskaznik
  xTaskCreate(LedControllerTask,"BLUE LED TASK",100,(void *)blueLed,1,NULL);
}

void LedControllerTask(void *pvParameters)
{
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  while(1)
  {
    // 3. w zależności co będzie argumentem to się zapali dioda od wykonanego aktualnego zadania
    //digitalWrite(RED,HIGH); // tak jest prosto alee..
    digitalWrite(pvParameters,digitalRead(pvParameters)^1); // negacja co bedzie na porcie w zaleznosci od wskaznika to bedzie zanegowane i pusczone na port
  }
}
void loop(){}
