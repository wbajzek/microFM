/*
  ==============================================================================

    WaveTables.h
    Created: 6 Dec 2014 3:02:24pm
    Author:  William Bajzek

  ==============================================================================
*/

#ifndef WAVETABLES_H_INCLUDED
#define WAVETABLES_H_INCLUDED

const unsigned int waveTableLength = 256;
const unsigned long i32waveTableLength = waveTableLength << 16;

enum WaveTables {
  SINE_WAVE_TABLE = 0,
  TRIANGLE_WAVE_TABLE,
  SAW_WAVE_TABLE,
  RAMP_WAVE_TABLE,
  WHITE_NOISE_WAVE_TABLE,
  NUMBER_OF_WAVE_TABLES
};

#include "SineWaveTable.h"
#include "TriangleWaveTable.h"
#include "SawWaveTable.h"
#include "RampWaveTable.h"
#include "WhiteNoiseWaveTable.h"

#endif  // WAVETABLES_H_INCLUDED
