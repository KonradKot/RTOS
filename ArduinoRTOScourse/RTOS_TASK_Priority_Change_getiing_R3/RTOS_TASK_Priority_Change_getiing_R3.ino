#include <Arduino_FreeRTOS.h>

#define RED    6
#define YELLOW   7
#define BLUE 8
#define GREEN  9

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler BlueLEDProfiler;
TaskProfiler GreenLEDProfiler;

TaskHandle_t blue_Handle,red_Handle,yellow_Handle,green_Handle;

void setup()
{
  Serial.begin(9600);
  xTaskCreate(yellowLEDController,"Yellow Led",100,NULL,1,&yellow_Handle);// uwaga to są wskaźniki!!!
  // uwaga zadanie z najwyższym priorytetem jest na samej górze, bo program się gubi przez to
  xTaskCreate(redLEDController,"Red Led",100,NULL,1,&red_Handle); // to jest mój uchwyt
  xTaskCreate(blueLEDController,"Blue Led",100,NULL,1,&blue_Handle);
  xTaskCreate(greenLEDController,"Green Led",100,NULL,1,&green_Handle);
}

void loop(){}

void redLEDController(void *pvParameters)
{
  pinMode(RED, OUTPUT);
  while(1)
  {
    RedLEDProfiler++; // za każdym razem gdy to zadanie działa to ten profil jest zwiększany
    Serial.print("Red task is running: ");
    Serial.println(RedLEDProfiler);
    digitalWrite(RED, digitalRead(RED)^1);
    //vTaskPrioritySet(red_Handle,1);
    delay(500);
  }
}
void yellowLEDController(void *pvParameters)
{
  pinMode(YELLOW, OUTPUT);
  while(1)
  {
    YellowLEDProfiler++; // pokazuje nam ile razy dane zadanie było wykonane
    Serial.print("Yellow task is running: ");
    Serial.println(YellowLEDProfiler);
    digitalWrite(YELLOW, digitalRead(YELLOW)^1);
    //vTaskPrioritySet(yellow_Handle,2);
    //vTaskPrioritySet(NULL,2);
    delay(500);
  }
}
void blueLEDController(void *pvParameters)
{
  pinMode(BLUE, OUTPUT);
  while(1)
  {
    BlueLEDProfiler++;
    Serial.print("Blue task is running: ");
    Serial.println(BlueLEDProfiler);
    digitalWrite(BLUE, digitalRead(BLUE)^1);
    delay(500);
  }
}

void greenLEDController(void *pvParameters)
{
  pinMode(GREEN, OUTPUT);
  while(1)
  {
    GreenLEDProfiler++;
    Serial.print("Green task is running: ");
    Serial.println(GreenLEDProfiler);
    digitalWrite(GREEN, digitalRead(GREEN)^1);
    delay(500);
  }
}
