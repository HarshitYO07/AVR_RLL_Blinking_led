#include <avr/io.h>
#include <util/delay.h>

void setup() {
  DDRB |= (1 << PB5);     // Set PB5 as output    #  define PB5 PORTB5
  PORTB &= ~(1 << PB5);   // Start with LED OFF (LOW)
  _delay_ms(1000);
}

void loop() {
  PORTB |= (1 << PB5);    // Turn LED ON
  _delay_ms(100);
  PORTB &= ~(1 << PB5);   // Turn LED OFF
  _delay_ms(100);
}

int main(void) {
  setup();
  while (1) {
    loop();
  }
}
