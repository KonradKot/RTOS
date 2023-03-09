#include <Arduino_FreeRTOS.h>

#define RED    6
#define BLUE   7
#define YELLOW 8
#define GREEN  9

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler BlueLEDProfiler;
TaskProfiler GreenLEDProfiler;

TaskHandle_t blue_Handle,red_Handle,yellow_Handle,green_Handle; // tworze uchwyt potrzebny wewnątrz funkcji
// tworzę uchwyty dla zmainy priorytów zadań dla każdej z diód
void setup()
{
  xTaskCreate(redLEDController,"Red Led",100,NULL,1,&red_Handle); // to jest mój uchwyt
  xTaskCreate(yellowLEDController,"Yellow Led",100,NULL,1,&yellow_Handle);// uwaga to są wskaźniki!!!
  xTaskCreate(blueLEDController,"Blue Led",100,NULL,1,&blue_Handle);
  xTaskCreate(greenLEDController,"Green Led",100,NULL,1,&green_Handle);
}

void loop() {}

void redLEDController(void *pvParameters)
{
  pinMode(RED, OUTPUT);
  while(1)
  {
    digitalWrite(RED, digitalRead(RED)^1);
    //vTaskPrioritySet(yellow_Handle,2);
    //delay(50);
    //delay(100);
  }
}
void yellowLEDController(void *pvParameters)
{
  pinMode(YELLOW, OUTPUT);
  while(1)
  {
    digitalWrite(YELLOW, digitalRead(YELLOW)^1);
    // ustawiam priorytet wewnątzrz funkji yellow dla diody
    //vTaskPrioritySet(red_Handle,2);
    // czerwonej na priorytet wyższ,2
    //delay(50);
  }
}
void blueLEDController(void *pvParameters)
{
  pinMode(BLUE, OUTPUT);
  while(1)
  {
    digitalWrite(BLUE, digitalRead(BLUE)^1);
    //vTaskPrioritySet(green_Handle,2);
    //delay(50);
  }
}

void greenLEDController(void *pvParameters)
{
  pinMode(GREEN, OUTPUT);
  while(1)
  {
    digitalWrite(GREEN, digitalRead(GREEN)^1);
   // vTaskPrioritySet(red_Handle,2);
   // delay(50);
  }
}
