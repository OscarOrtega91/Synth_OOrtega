/*
  ==============================================================================

    FilterController.h
    Created: 11 Oct 2021 1:13:32pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterController{
public:
    void prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    
    void updateParameters(const int filterType, const float frequency, const float resonance, const float modulator=1.0f);
    void reset();
    
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared {false};

};
