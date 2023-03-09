int leds[] = {6, 7, 8,9};
//określamy wielkość tablicy jako stałą
#define SIZE 10
int i;

void setup()
{
  Serial.begin(57600);

  //ustawiamy piny jako wyjścia
  for (i = 0; i < SIZE; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{

  //biegnący punkt świetlny
  for (i = 0; i < SIZE; i++) {
    digitalWrite(leds[i], HIGH);
    delay(200);
    digitalWrite(leds[i], LOW);
  }

  //Bar graph
  for (i = 0; i < SIZE; i++) {
    digitalWrite(leds[i], HIGH);
    delay(200);
  }
  for (i = 0; i < SIZE; i++) {
    digitalWrite(leds[i], LOW);
    delay(200);

  }
}
