#include <Arduino_FreeRTOS.h>

#define RED    6
#define BLUE   7
#define YELLOW 8

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler BlueLEDProfiler;

// uwaga na delay - delay usuwa priorytety
// wyższe priorytety mają pierszeństwo
// mając najwyższy priorytet dioda nie miga i się świeci jako jedyna
// mając dwie takie same priorytety diody  migają na zmianę
void setup()
{
  xTaskCreate(redLEDController,"Red Led",100,NULL,3,NULL);
  xTaskCreate(yellowLEDController,"Yellow Led",100,NULL,3,NULL);
  xTaskCreate(blueLEDController,"Blue Led",100,NULL,1,NULL);
}

void loop() {}

void redLEDController(void *pvParameters)
{
  pinMode(RED, OUTPUT);
  while(1)
  {
    digitalWrite(RED, digitalRead(RED)^1);
    //delay(100);
  }
}
void yellowLEDController(void *pvParameters)
{
  pinMode(YELLOW, OUTPUT);
  while(1)
  {
    digitalWrite(YELLOW, digitalRead(YELLOW)^1);
    //delay(100);
  }
}
void blueLEDController(void *pvParameters)
{
  pinMode(BLUE, OUTPUT);
  while(1)
  {
    digitalWrite(BLUE, digitalRead(BLUE)^1);
    //delay(100);
  }
}
