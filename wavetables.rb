wavetable_length = 256;
File.open('wavetables/SineWaveTable.h','w') do |f|
  f.write <<HEADER
/*
  ==============================================================================

    SineWavetable.h
    Author:  William Bajzek

  ==============================================================================
*/

#ifndef SINEWAVETABLE_H_INCLUDED
#define SINEWAVETABLE_H_INCLUDED
HEADER


  f.write "const float sineWaveTable[] = {\n"
  phase = 0.0
  phase_increment = 2.0 * Math::PI / wavetable_length
  wavetable_length.to_i.times do
    f.write "#{ (1.0 + Math::sin(phase)) * 128.0 },\n"
    phase += phase_increment
  end
  f.write "};\n"

  f.write "#endif  // SINEWAVETABLE_H_INCLUDED\n"
end
