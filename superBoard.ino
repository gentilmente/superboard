#include <IRremote.h>

const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
int speakerPin = 7;
int r = 10;
int g = 11;
int b = 9;

bool on = false;
int mode = -1;
const int flasho = 1;
const int offo = 0;
bool ledState = LOW;

bool ledBlinkState = HIGH;
int ledDelay = 1000;
long ledTimer;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  //irrecv.blink13(true);
  pinMode(speakerPin, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.println(results.value);
    switch (results.value)
    {
    case 4188645185:
      Serial.println("1");
      digitalWrite(g, !digitalRead(g));
      break;
    case 2013339561:
      Serial.println("2");
      digitalWrite(r, !digitalRead(r));
      break;
    case 3182446403:
      Serial.println("3");
      digitalWrite(b, !digitalRead(b));
      break;
    case 1182328499:
      Serial.println("4");
      cumple();
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
    delay(80);
    irrecv.resume();
  }

  switch (mode)
  {
  case flasho:
    determineState();
    display();
    cumple();
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
  }
}

void determineState()
{
  checkBlinkTimer();
  determineLedState();
}

void checkBlinkTimer()
{
  if (millis() - ledTimer > ledDelay)
  {
    ledTimer = millis();
    ledBlinkState = !ledBlinkState;
  }
}

void determineLedState()
{
  if (ledBlinkState)
  {
    ledState = HIGH;
  }
  else
  {
    ledState = LOW;
  }
}

void display()
{
  digitalWrite(ledPin, ledState);
}

void offAll()
{
  Serial.println("-jkj");
  digitalWrite(r, LOW);
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
}

// **************************
// *      cumple            *
// **************************

void cumple()
{
  int length = 28; // the number of notes
  char notes[] = "GGAGcB GGAGdc GGgecBA yyecdc";
  int beats[] = {2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8, 8, 8, 16, 1, 2, 2, 8, 8, 8, 16};
  int tempo = 150;

  for (int i = 0; i < length; i++)
  {
    if (notes[i] == ' ')
    {
      delay(beats[i] * tempo); // rest
    }
    else
    {
      playNote(notes[i], beats[i] * tempo);
    }
    // pause between notes
    delay(tempo);
  }
}

void playNote(char note, int duration)
{
  char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',
                  'c', 'd', 'e', 'f', 'g', 'a', 'b',
                  'x', 'y'};
  int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014,
                 956, 834, 765, 593, 468, 346, 246,
                 655, 715};
  int SPEE = 5;
  // play the tone corresponding to the note name
  for (int i = 0; i < 17; i++)
  {
    if (names[i] == note)
    {
      int newduration = duration / SPEE;
      playTone(tones[i], newduration);
    }
  }
}

void playTone(int tone, int duration)
{
  for (long i = 0; i < duration * 1000L; i += tone * 2)
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
