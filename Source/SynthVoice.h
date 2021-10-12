/*
  ==============================================================================

    SynthVoice.h
    Created: 6 Oct 2021 7:07:55pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Controller/ADSRController.h"
#include "Controller/OscController.h"
#include "Controller/FilterController.h"

class SynthVoice: public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay  (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void pitchWheelMoved (int newPitchWheelValue) override;
    void updateADSR(const float attack, const float decay, const float release, const float sustain);
    void setWaveType(const int waveType);
    void setFMParams(const float fmDepth, const float frequency);
    void updateFilter(const int filterType, const float frequency, const float resonance);
    void updateModADSR(const float attack, const float decay, const float release, const float sustain);
    
private:
    juce::AudioBuffer<float> _synthBuffer;

    OscController osc;
    ADSRController adsr;
    FilterController filter;
    ADSRController modADSR;
    juce::dsp::Gain<float> gain;
    bool isPrepared {false};

    
};
