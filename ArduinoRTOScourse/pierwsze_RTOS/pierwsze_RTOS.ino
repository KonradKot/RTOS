#include <Arduino_FreeRTOS.h>
#define RED 6
#define YELLOW 7
#define BLUE 8

void setup() {

  xTaskCreate(redLedControllerTask,"RED LED Task",128,NULL,1,NULL);
  xTaskCreate(blueLedControllerTask,"BLUE LED Task",128,NULL,1,NULL);
  xTaskCreate(yellowLedControllerTask,"YELLOW LED Task",128,NULL,1,NULL);
  // zadanie, co robi,stos/pamiec,ktora chcemy przydzieli,priorytet zadania
// każde zadanie to jak petla trwa do nieskączonosci
}

void redLedControllerTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);  // ustawiam pin dopiero jak jest potrzebny
  while(1)
  {
    digitalWrite(RED,digitalRead(RED)^1);
    delay(50);
  }
}

void blueLedControllerTask(void *pvParameters)
{
  pinMode(BLUE,OUTPUT);
  while(1)
  {
      digitalWrite(BLUE,digitalRead(BLUE)^1);
      delay(50);
  }
}

void yellowLedControllerTask(void *pvParameters)
{
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);// odczyt z pinu jest zanegowany to co jest zanegowane jest na wyjsciu
    delay(50);
  }
}
void loop() {

}
