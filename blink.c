#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>   // NEW: gives us ISR() and sei()

int main(void) {
    DDRB |= (1 << PB5);              // LED pin as output

    // --- Timer1 setup---
    TCCR1A = 0;
    TCCR1B |= (1 << WGM12) | (1 << CS12);   // CTC + /256 prescaler
    OCR1A = 31249;                          // 500 ms target

    //Enable the Timer1 compare-match-A interrupt:
	TIMSK1 |= (1 << OCIE1A);

    sei();   //flip the global interrupt master switch on

    while (1) {
        // This emptiness IS the milestone.
    }
    return 0;
}

// The ISR — runs automatically every time Timer1 hits OCR1A.
ISR(TIMER1_COMPA_vect) {
    //Toggle the LED:
	PORTB ^= (1 << PB5);
}