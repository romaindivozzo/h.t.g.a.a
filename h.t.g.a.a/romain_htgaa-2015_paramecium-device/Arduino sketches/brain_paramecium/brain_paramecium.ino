// Simple paramecium brain control code using a Neurosky sensor (e.g. from a MindFlex Duel)
// Requires the Arduino brain library (https://github.com/kitschpatrol/Arduino-Brain-Library)

#include <Brain.h>

// Concentration threshold: play around with this to find a level that works well for you
#define THRESHOLD 60

// Change this if necessary to match the pins for your up, down, left and right electrodes
#define UP    4
#define DOWN  5
#define LEFT  6
#define RIGHT 7

// #define TRISTATE

Brain brain(Serial);

void setup() {
#ifdef TRISTATE
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
#else
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
#endif
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);
  digitalWrite(UP, LOW);
  digitalWrite(DOWN, LOW);
  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, LOW);
  Serial.begin(9600);
}

int attn = 0;
int signal;

void loop() {
  if (brain.update()) {
    signal = brain.readSignalQuality();
    if(signal==0)  {
      attn = brain.readAttention();
    }
    // enable this if you want debug information about signal strength and concentration level
    // printed to the serial console
    /*
    Serial.print("S: ");
    Serial.print(signal);
    Serial.print(" A: ");
    Serial.println(attn);
    */
    if(attn>=THRESHOLD) {
#ifdef TRISTATE
      pinMode(UP, OUTPUT);
      pinMode(DOWN, OUTPUT);
#endif
      digitalWrite(DOWN, HIGH);
    } else {
#ifdef  TRISTATE
      pinMode(UP, INPUT);
      pinMode(DOWN, INPUT);
#endif
      digitalWrite(DOWN, LOW);
    }
  }
}



