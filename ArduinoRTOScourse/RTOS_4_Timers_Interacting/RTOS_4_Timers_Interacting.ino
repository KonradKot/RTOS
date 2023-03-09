#include <Arduino_FreeRTOS.h>
#include "timers.h"

#define RED  6
#define Yellow 7
#define Blue 8

#define BLUE_TIMER_PERIOD (pd_MS_TO_TICKS(120)) // tworze konwertery z ms to pic 
#define RED_TIMER_PERIOD (pdMS_TO_TICKS(300)) // tak to bedzie działać za szybko
// okresy są stałe
TimerHandle_t xBlueTimer, xRedTimer;
void setup()
{
  Serial.begin(9600);
  BaseType_t xBlueTimerStarted, xRedTimerStarted;

  xBlueTimer=xTimerCreate("Blue Timer",BLUE_TIMER_PERIOD,pdTRUE,0,prvTimerCallback);
  xRedTimer= xTimerCreate("Red Timer",RED_TIMER_PERIOD,pdTRUE,0);
}

void loop() {}
