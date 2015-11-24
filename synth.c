#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "wavetables/SineWaveTable.h"
#include <math.h>

float index_wt = 0.0;
float index_wt_increment = 1.0;
int table_length = 256;
int clock_divider = 400;
float sample_rate;
float freq_ti;

void set_note(float frequency) {
  index_wt_increment = freq_ti * frequency;
}

void init_pins() {
  DDRD |= 0b0001110;
  DDRC |= 0b1111111; // DAC outs
  PORTD &= ~(1 << PIND2); // select DAC A
}

void init_sample_timer() {
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS12);
  TIMSK |= (1 << OCIE1A);
  OCR1A = clock_divider - 1;
}

void init_synth() {
  float sample_rate = F_CPU / clock_divider;
  freq_ti = table_length / sample_rate;
  set_note(440.0);
}

int calculate_sample() {
  if ((index_wt += index_wt_increment) >= table_length)
    index_wt -= table_length;

  return (1.0 + sineWaveTable[ (int)index_wt ]) * 63;
}

void update_dac(int sample) {
  PORTD |= (1 << PIND3); // set DAC write pin high for writing
  PORTC = sample;
  PORTD &= ~(1 << PIND3); // set DAC write pin low to trigger output
}

ISR(TIMER1_COMPA_vect) {
  update_dac(calculate_sample());
}

int main(void) {
  init_synth();
  init_pins();
  init_sample_timer();
  sei();

  while (1) {}
  return (0);
}
