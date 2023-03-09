#include <Arduino_FreeRTOS.h>

#define RED 6
#define YELLOW 7
#define BLUE 8

typedef int TaskProfiler; // redefiniuje int do zmiennej globalnej

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler BlueLEDProfiler;


void setup() {
  Serial.begin(9600);
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
    RedLEDProfiler++;
    Serial.print("REDLEDProfiler: ");
    Serial.println(RedLEDProfiler);
    delay(500);
    //digitalWrite(RED,digitalRead(RED)^1);
  }
}

void blueLedControllerTask(void *pvParameters)
{
  pinMode(BLUE,OUTPUT);
  while(1)
  {
    BlueLEDProfiler++;
    Serial.print("BLUELEDProfiler: ");
    Serial.println(BlueLEDProfiler++);
    delay(500);
    //digitalWrite(BLUE,digitalRead(BLUE)^1);
  }
}

void yellowLedControllerTask(void *pvParameters)
{
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
    YellowLEDProfiler++;
    Serial.print("YELLOWLEDProfiler");
    Serial.println(YellowLEDProfiler);
    delay(500);
    //digitalWrite(YELLOW,digitalRead(YELLOW)^1);// odczyt z pinu jest zanegowany to co jest zanegowane jest na wyjsciu
  }
}
void loop(){}


/*podstawy RTOS
 * 
 * 
 * nazwy makra:
 * taskXYZ   :task.h    określa zadania
 * pdXYZ :FreeRTOSConfig.h  określa anomalie
 * configXYZ   :projdefs.h  określa błędy
 * 
 * pdTrue   1
 * pdFALSE  0
 * pdPASS   1
 * pdFAIL   0
 * 
 * 
 * 
 **/a */
