#define F_CPU 16000000UL
#include <avr/io.h>
// no more <util/delay.h> — we've retired _delay_ms()

int main(void) {
    // LED pin (PB5) as output — unchanged from blink
    DDRB |= (1 << PB5);

    // --- Timer1 setup ---
    TCCR1A = 0;   // given: no output-pin behavior; the mode is finished in TCCR1B

    //In TCCR1B,VCTC mode (WGM12) AND the /256 prescaler (CS12), together:
	TCCR1B = (1 << WGM12) | (1 << CS12);

    //the 500 ms compare target into OCR1A:
	OCR1A = 31249;

    while (1) {
        //is the OCF1A flag in TIFR1 set?
        if (TIFR1 & (1 << OCF1A) ) {

            //writes a 1 to OCF1A, using =
		TIFR1 = (1 << OCF1A);

            //Toggle the LED (flip PB5):
		PORTB ^= (1 << PB5); 
        }
    }
    return 0;
}