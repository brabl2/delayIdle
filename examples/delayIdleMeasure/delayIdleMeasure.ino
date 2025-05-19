/*
  This sketch allows to measure and compare power consumption
  during the original Arduino delay() and delayIdle() functions

  Using the delayIdle() function most common AVR chips consume approx. 1/2 of the power when compared to the original Arduino delay() function.
  ATmega328p@8MHz@5V   : delay() =13.5mA   delayIdle() = 8mA
  ATmega328p@8MHz@3.3V : delay() = 3.7mA   delayIdle() = 1.4mA
  ATmega328p@1MHz@3.3V : delay() = 1.2mA   delayIdle() = 0.5mA
  ATtiny85  @1MHz@5V   : delay() = 3.2mA   delayIdle() = 2.5mA
  Putting the CPU to SLEEP_MODE_IDLE causes some inaccuracy in the time when the CPU returns from the delayIdle() function, however in most cases the small inaccuracy is acceptable.
  The inaccuracy depends mostly on TIMER0 overflow, which depends on CPU frequency : 1ms @ 16MHz, 2ms @ 8MHz, 16ms @ 1MHz
*/

#include <delayIdle.h>

#define LED 13 // LED pin number

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED as an output.
  pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // blink once
  digitalWrite(LED, HIGH);   // turn the LED on
  delay(100);
  digitalWrite(LED, LOW);    // turn the LED off
  // perform the original Arduino delay()
  // the power consumption might be measured by the ampermeter
  delay(6000);

  // blink twice
  digitalWrite(LED, HIGH);   // turn the LED on
  delayIdle(100);
  digitalWrite(LED, LOW);    // turn the LED off
  delayIdle(200);
  digitalWrite(LED, HIGH);   // turn the LED on
  delayIdle(100);
  digitalWrite(LED, LOW);    // turn the LED off
  // perform the delayIdle()
  // the power consumption might be measured by the ampermeter
  delayIdle(6000);

} 