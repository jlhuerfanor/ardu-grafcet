#include <Wire.h>

//
// Example of grafcet implementation using arduino-based PLC.
// 
// 2017-08-07  Jerson Huerfano <huerfano.jerson@gmail.com>
//

#include "Grafcet.h"
#include "DataStream.h"

// This is the set of functions each stage calls
// once when is activated.
void q0_onActivated();
void q1_onActivated();
void q2_onActivated();
void q3_onActivated();
void q4_onActivated();
void q5_onActivated();

// This is the set of functions each stage calls
// once when is deactivated.
void q0_onShutdown();
void q1_onShutdown();
void q2_onShutdown();
void q3_onShutdown();
void q4_onShutdown();
void q5_onShutdown();

// this is a dumy function the timers uses when interrupts. You can set to NULL
// or implement independent functions for each timer.
void onActivating(ulong milis);

// This is the function that encapsulates all transition conditions.
// id is the index of the transtion in the array that is being analyzed.
bool thePredicates(int id);


void sendState();
// Stage list. Index is important for transition definitions.
Stage q[6] = {
    Stage(NULL, q0_onActivated, q0_onShutdown),
    Stage(NULL, q1_onActivated, q1_onShutdown),
    Stage(NULL, q2_onActivated, q2_onShutdown),
    Stage(NULL, q3_onActivated, q3_onShutdown),
    Stage(NULL, q4_onActivated, q4_onShutdown),
    Stage(NULL, q5_onActivated, q5_onShutdown) };

// Transition list. Order of transition is irelevant.
Transition t[6] = {
    Transition((int[] ) { 0, 1, 2 },  1, 2),
    Transition((int[] ) { 2, 3 },     1, 1),
    Transition((int[] ) { 2, 4 },     1, 1),
    Transition((int[] ) { 3, 5 },     1, 1),
    Transition((int[] ) { 4, 5 },     1, 1),
    Transition((int[] ) { 1, 5, 0 },  2, 1)};

// Timer list. Timer can be configured as continous or single-shot timer.
Timer tim[6] = {
    Timer(onActivating, 2000),
    Timer(onActivating, 2000),
    Timer(onActivating, 2000),
    Timer(onActivating, 2000),
    Timer(onActivating, 2000),
    Timer(onActivating, 2000)};

// Grafcet timer. You can attatch a continous timer to this clock 
// if you wanted to implement a temperature PID controller.
byte buffer[50];
Clock theClock = Clock(tim, 6);
Grafcet grafcet = Grafcet(t, 6, q, 6, thePredicates);
DataStream stream = DataStream(buffer, 50);
int Nloops = 0;

void setup() {
  pinMode(4, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  // you must set grafcet clock after setup.
  grafcet.setClock(&theClock);
  grafcet.setup();
  Serial.begin(9600);
}

void loop() {
  // Grafcet loop.
  grafcet.loop();
}

// This function encapsulates all the transition conditions
//
bool thePredicates(int id) {
  bool result = false;

  switch (id) {
  case 0:
    result = tim[0].isInterrupted();
    break;
  case 1:
    result = tim[1].isInterrupted() && (digitalRead(4)) == LOW;
    break;
  case 2:
    result = tim[2].isInterrupted() && (digitalRead(4)) == HIGH;
    break;
  case 3:
    result = tim[3].isInterrupted();
    break;
  case 4:
    result = tim[4].isInterrupted();
    break;
  case 5:
    result = tim[5].isInterrupted();
    break;
  default:
    break;
  }
  return result;
}

// This functions will be called once when stage is activated

void q0_onActivated() { 
  digitalWrite(5, HIGH); 
  tim[0].enable();
  stream.wseek(0);
  stream.encode(Nloops);
  Nloops++;
  sendState();
}
void q1_onActivated() { digitalWrite(6, HIGH); tim[1].enable(); }
void q2_onActivated() { digitalWrite(7, HIGH); tim[2].enable(); }
void q3_onActivated() { digitalWrite(8, HIGH); tim[3].enable(); }
void q4_onActivated() { digitalWrite(9, HIGH); tim[4].enable(); }
void q5_onActivated() { digitalWrite(10, HIGH); tim[5].enable(); }

// This functions will be called once when stage is deactivated
void q0_onShutdown() { digitalWrite(5, LOW); tim[0].reset(); }
void q1_onShutdown() { digitalWrite(6, LOW); tim[1].reset(); }
void q2_onShutdown() { digitalWrite(7, LOW); tim[2].reset(); }
void q3_onShutdown() { digitalWrite(8, LOW); tim[3].reset(); }
void q4_onShutdown() { digitalWrite(9, LOW); tim[4].reset(); }
void q5_onShutdown() { digitalWrite(10, LOW); tim[5].reset(); }

void sendState()
{
  int n = 0;
  stream.rseek(0);
  stream.decode(n);
  Serial.print("Ciclo ");
  Serial.println(n);
}
// This functions will be called when timers are interrupted
void onActivating(ulong delta)
{
  return;
}
