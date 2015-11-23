#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "wavetables/SineWaveTable.h"
#include <math.h>

float index_wt = 0.0;
float index_wt_increment = 1.0;
int table_length = 256;
int clock_divider = 36;
float sample_rate;
float freq = 440.0;
float freq_ti;

int main(void) {
  sample_rate = F_CPU / clock_divider / 16; // why divide by 16?
  freq_ti = table_length / sample_rate;
  index_wt_increment = freq_ti * freq;

  DDRD |= 0b0001110;
  DDRC |= 0b1111111; // DAC outs

  // setup timer
  TCCR0 |= (1 << CS00);
  TCCR0 &= ~(1 << CS01);
  TCCR0 &= ~(1 << CS02);
  TCNT0 = 0;

  while (1) {
    if (TCNT0 >= clock_divider) {
      TCNT0 = 0;

      PORTD |= (1 << PIND3); // set DAC write pin high for writing
      PORTD &= ~(1 << PIND2); // select DAC A
      // why do I have to scale this down to avoid clipping?
      PORTC = (sineWaveTable[ (int)index_wt ]) * 0.49;
      PORTD &= ~(1 << PIND3); // set DAC write pin low to trigger output
      PORTD |= (1 << PIND3); // set it high again because that's what the micro does?

      if ((index_wt += index_wt_increment) >= table_length)
        index_wt -= table_length;
    }
  }
  return (0);
}
