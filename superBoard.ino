#include <IRremote.h>

const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
int r = 13;
int g = 11;
int b = 12;
bool on = false;
int mode = -1;
const int flasho = 1;
const int offo = 0;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  //irrecv.blink13(true);

  pinMode(r, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(g, OUTPUT);
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.println(results.value);
    switch (results.value)
    {
    case 4197062193:
      Serial.println("1");
      digitalWrite(r, HIGH);
      break;
    case 2021756569:
      Serial.println("2");
      digitalWrite(g, HIGH);
      break;
    case 3057459025:
      Serial.println("3");
      digitalWrite(b, HIGH);
      break;
    case 2354352215:
      Serial.println("-");
      mode = offo;
      break;
    case 3730122487:
      Serial.println("+");
      mode = flasho;
      break;
    default:
      mode = -1;
      break;
    }
    irrecv.resume();
  }

  switch (mode)
  {
  case flasho:
    flash();
    break;
  case offo:
    offAll();
    break;
  default:
    break;
  }
}

void flash()
{
  for (int i = 11; i <= 13; i++)
  {
    digitalWrite(i, HIGH);
    delay(100);
    digitalWrite(i, LOW);
    delay(100);
  }
}

void offAll()
{
  digitalWrite(r, LOW);
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
}
