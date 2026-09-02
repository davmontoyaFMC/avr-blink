#define F_CPU 16000000UL   // the UNO's clock runs at 16 MHz; delay needs to know this
#include <avr/io.h>        // defines the register names (DDRB, PORTB…) for this chip
#include <util/delay.h>    // provides _delay_ms()

int main(void) {
    // 1. Make PB5 an output:
    // >>> your line here
	DDRB |= (1 << 5); //sets ddrb as output

    while (1) {
        // 2. Turn the LED on:
        // >>> your line here
	PORTB |= (1 << 5); //turns on the led
        _delay_ms(500);

        // 3. Turn the LED off:
        // >>> your line here
	PORTB &= ~(1 << 5); //turns off the led
        _delay_ms(500);
    }

    return 0;   // never reached
}