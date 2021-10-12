/*
  ==============================================================================

    OscController.h
    Created: 8 Oct 2021 8:54:56pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscController : public juce::dsp::Oscillator<float>
{
    
public:
    void setWaveType(const int waveType);
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block );
    void setWaveFrequency (const int midiNoteNumber);
    void setFMParams(const float fmDepth, const float frequency);
private:
    //For FM Frequency Modulation
    juce::dsp::Oscillator<float> _internalOsc {[](float x){return std::sin(x);}};
    float _fmModulation =0.0f;
    float _fmDepth=0.0f;
    int _lastMidiNote=0;
};
