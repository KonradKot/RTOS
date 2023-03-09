#include <Arduino_FreeRTOS.h>

#define RED 6
#define YELLOW 7
#define BLUE 8

typedef int TaskProfiler; // redefiniuje int do zmiennej globalnej

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler BlueLEDProfiler;

TaskHandle_t blue_Handle, red_Handle, yellow_Handle; //tworze uchwyty do moich zadań 
uint32_t suspend_monitor; // licznik od kiedy ma nastąpić przerwanie, liczba 32 bitowa

void setup() {
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask,"RED LED Task",128,NULL,1,&red_Handle);
  xTaskCreate(blueLedControllerTask,"BLUE LED Task",128,NULL,1,&blue_Handle);
  xTaskCreate(yellowLedControllerTask,"YELLOW LED Task",128,NULL,1,&yellow_Handle);
  // zadanie, co robi,stos/pamiec,ktora chcemy przydzieli,priorytet zadania
// każde zadanie to jak petla trwa do nieskączonosci
// pvParameters to były zwyczajne wskaźniki do funkcji np. numery pinów które działają

}

void redLedControllerTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);  // ustawiam pin dopiero jak jest potrzebny
  while(1)
  {
    digitalWrite(RED,digitalRead(RED)^1);
    suspend_monitor++;
    RedLEDProfiler++; //ile razy wykonane zadanie
    Serial.print("Red Run Time: ");
    Serial.println(RedLEDProfiler);
    vTaskDelay(100);
    if(suspend_monitor>=12)
    {
      vTaskSuspend(blue_Handle); // kiedy licznik bedzie większy od 71200 do dioda zgaśnie zadanie jest przerwanie, wykonywanie calego zadania
      digitalWrite(BLUE,LOW); // dodatkowo musze miec pewnosc ze dioda zgaśnie bo jak przerwę zadanie to może dioda pozostać zapalona
    }
    if(suspend_monitor>=15)
    {
      digitalWrite(RED,LOW);
      vTaskSuspend(NULL); // domyślnie bedzie to red bo w tym jest zadaniu
    }
  }
}

void blueLedControllerTask(void *pvParameters)
{
  pinMode(BLUE,OUTPUT);
  while(1)
  {
    digitalWrite(BLUE,digitalRead(BLUE)^1);
    BlueLEDProfiler++;
    Serial.print("Blue Run Time ");
    Serial.println(BlueLEDProfiler);
    vTaskDelay(100);
    if(suspend_monitor>=10)
    {
      vTaskSuspend(yellow_Handle);
      digitalWrite(YELLOW,LOW);
    }
  }
}

void yellowLedControllerTask(void *pvParameters)
{
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    YellowLEDProfiler++;
    Serial.print("Yellow Run Time ");
    Serial.println(YellowLEDProfiler);
    vTaskDelay(100);
  }
}
void loop(){}
