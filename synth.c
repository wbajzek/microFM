/* Blinker Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <avr/interrupt.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */
#include "wavetables/SineWaveTable.h"
#include <math.h>

float index_wt = 0.0;
float index_wt_increment = 1.0;
int led = 1;
int table_length = 256;
float sample_rate;
float freq = 440.0;
float freq_ti;

int main(void) {
  sample_rate = F_CPU / 44100;
  freq_ti = (float)table_length / sample_rate;
  // -------- Inits --------- //
  DDRD |= 0b0001110;
  DDRC |= 0b1111111; // DAC outs

  index_wt_increment = freq_ti * freq;
  // ------ Event loop ------ //
  while (1) {
    PORTD |= (1 << PIND3);
    PORTD |= (1 << PIND2);
    PORTD |= (1 << PIND1); //LED
    PORTC = (int)(sineWaveTable[ (int)index_wt ] * 128.0);
    PORTD &= ~(1 << PIND3);
    PORTD &= ~(1 << PIND2);
    PORTD &= ~(1 << PIND1); //LED
    if ((index_wt += index_wt_increment) >= table_length)
      index_wt -= table_length;
    for (int i = 0; i < 220; i++)
      ;
  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}
