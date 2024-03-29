#include <delayIdle.h>
#include <avr/sleep.h>
#include <Arduino.h>

// Using this function most common AVR chips consume approx. 1/2 of the power when compared to the original Arduino delay() function
// ATmega328p@8MHz@5V   : delay()=13.5mA   delayIdle()=8mA
// ATmega328p@8MHz@3.3V : delay()=3.72mA   delayIdle()=1.35mA
// ATmega328p@1MHz@3.3V : delay()=1.17mA   delayIdle()=0.53mA
// Putting the CPU to SLEEP_MODE_IDLE causes some inaccuracy in the time when the CPU returns from the delayIdle() function, however in most cases the small inaccuracy is acceptable.
// The inaccuracy depends mostly on TIMER0 overflow, which depends on CPU frequency : 1ms @ 16MHz, 2ms @ 8MHz, 16ms @ 1MHz
void delayIdle(unsigned long ms) {
  unsigned long start = millis();
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable(); // enables the sleep bit (SE) in the mcucr register
  do {
    //sleep_mode(); // Put the device into sleep mode, taking care of setting the SE bit before, and clearing it afterwards.
    sleep_cpu(); // Put the device into sleep mode. The SE bit must be set beforehand, and it is recommended to clear it afterwards.
  } while((millis() - start) < ms);
  sleep_disable(); // disables the sleep bit (SE) in the mcucr register
}
