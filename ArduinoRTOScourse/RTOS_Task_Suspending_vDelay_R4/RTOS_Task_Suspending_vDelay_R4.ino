#include <Arduino_FreeRTOS.h>

#define RED 6
#define YELLOW 7
#define BLUE 8
#define GREEN 9

typedef int TaskProfiler; // redefiniuje int do zmiennej globalnej

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler BlueLEDProfiler;
TaskProfiler GreenLEDProfiler;

const TickType_t _500ms = pdMS_TO_TICKS(500); // gotowa funkcja
// to co zwróci ta funkcja dla argumentu 500 bedzie przypisamne do _500ms typu TickType jako stała
uint32_t resume_cou=0;
uint32_t suspend_cou=0; 
uint32_t i=0;
bool flag_A=false;
bool flag_B=false;

TaskHandle_t red_Handle,blue_Handle,yellow_Handle,green_Handle;

void setup() {
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask,"RED LED Task",128,NULL,1,&red_Handle);
  xTaskCreate(blueLedControllerTask,"BLUE LED Task",128,NULL,1,&blue_Handle);
  xTaskCreate(yellowLedControllerTask,"YELLOW LED Task",128,NULL,1,&yellow_Handle);
  xTaskCreate(greenLedControllerTask,"green LED Task",128,NULL,1,&green_Handle);
  // zadanie, co robi,stos/pamiec,ktora chcemy przydzieli,priorytet zadania
// każde zadanie to jak petla trwa do nieskączonosci
// pvParameters to były zwyczajne wskaźniki do funkcji np. numery pinów które działają
// vTaskDelay(); przez ten czas można wykonać inne zadanie a znie zatrzymywać cały program jak w DElay
// TERAZ ZAJMNIEJMY SIE CONVWRTEM NA MS
}

void redLedControllerTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);  // ustawiam pin dopiero jak jest potrzebny
  while(1)
  {
    digitalWrite(RED,digitalRead(RED)^1);
    vTaskDelay(10);
    i++;
    //i=i>=3?0:i++;
    if(flag_B==false)
    {
    if(i>=3)
    {
      flag_B=true;
      i=0;
      vTaskResume(green_Handle);
      vTaskSuspend(NULL);
    }
    // zapalenie i dzialanie w sume trwa 1s
  }
  }
}

void blueLedControllerTask(void *pvParameters)
{
  pinMode(BLUE,OUTPUT);
  while(1)
  {
    digitalWrite(BLUE,HIGH);
    vTaskDelay(1*_500ms); // wywołuje tą funkcję
    digitalWrite(BLUE,LOW);
    vTaskDelay(1*_500ms); 
    BlueLEDProfiler++;
    if(flag_A==false)
    {
    suspend_cou++;
    if(suspend_cou==3)
    {
      flag_A=true;
      suspend_cou=0;
      vTaskResume(yellow_Handle);
      vTaskSuspend(NULL);
    }
    }
  }
}

void yellowLedControllerTask(void *pvParameters)
{
  pinMode(YELLOW,OUTPUT);
  
  while(1)
  {
    digitalWrite(YELLOW,HIGH);
    vTaskDelay(1*_500ms); // wywołuje tą funkcję
    digitalWrite(YELLOW,LOW);
    vTaskDelay(1*_500ms); 
    if(flag_A==true)
    {
      resume_cou++;
      if(resume_cou==3)
      {
        flag_A=false;
        resume_cou=0;
        vTaskResume(blue_Handle);
        vTaskSuspend(NULL);
      }
    }
  }
}
void greenLedControllerTask(void *pvParameters)
{
  pinMode(GREEN,OUTPUT);
  while(1)
  {
    digitalWrite(GREEN,digitalRead(GREEN)^1);
    vTaskDelay(10);
    i++;
    if(flag_B==true)
    {
    //i=i>=3?0:i++;
    if(i>=3)
    {
      flag_B=false;
      i=0;
      vTaskResume(red_Handle);
      vTaskSuspend(NULL);
    }
    // zapalenie i dzialanie w sume trwa 1s
  }
  }
}
void loop(){}
