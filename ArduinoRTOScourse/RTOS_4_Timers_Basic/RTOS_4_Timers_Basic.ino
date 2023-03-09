#include<Arduino_FreeRTOS.h>
#include"timers.h"

#define ONE_SHOT_TIMER_PERIOD (pdMS_TO_TICKS(500))// zamieniam tiki na ms 0,5 s
#define AUTO_RELOAD_TIMER_PERIOD (pdMS_TO_TICKS(300)) //0,3s nie trzeba kalkulwać zegara
// one shot jeden cykl zadania
/// auto shot wiele cykli zadania

TimerHandle_t xZegar1,xZegar2;
BaseType_t xZegar1Started, xZegar2Started;


void setup()
{
  Serial.begin(9600);
  xZegar1=xTimerCreate("jeden strzal",ONE_SHOT_TIMER_PERIOD,
                       pdFALSE,// nie powtarzaj zadania - jednorazowy
                       0,
                       prvOneShotTimerCallback
                       ); // tak defniuje swój pierwszytimer
  xZegar2=xTimerCreate("Auto-Reload",
                       AUTO_RELOAD_TIMER_PERIOD,
                       pdTRUE,//wykonuj cyklicznie
                       0,
                       prvAutoTimerCallback     // deklaracja funkcii callback              
  );
  if((xZegar1 != NULL)&&(xZegar2 != NULL)) // jesli timery są aktywne
  {
    xZegar1Started=xTimerStart(xZegar1,0);// jaki zegar, po jakim czasie wystartuj
    xZegar2Started=xTimerStart(xZegar2,0);// zwraca 1 działa 0 niedziała
  }

  while((xZegar1Started != pdPASS)&& (xZegar2Started != pdPASS))// dopuki obydwa timery działaja
  {
 
  }
}

void prvOneShotTimerCallback(TimerHandle_t xTimer)// argument funkcji jest uchwytem
{ // jest to funkcja typu callback
  TickType_t xTimeNow; // type tick
  xTimeNow = xTaskGetTickCount();
  Serial.print("One-shot timer callback sxecution: ");
  Serial.println(xTimeNow);
}
void prvAutoTimerCallback(TimerHandle_t xTimer)
{
  static TickType_t xTimeNow; // typstatyczny
  xTimeNow = xTaskGetTickCount();
  Serial.print("Auto-reload timer callback execution: ");
  Serial.println(xTimeNow);
}
void loop(){}
