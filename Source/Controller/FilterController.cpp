/*
  ==============================================================================

    FilterController.cpp
    Created: 11 Oct 2021 1:13:32pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#include "FilterController.h"

void FilterController::prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels){
    filter.reset();
    juce::dsp::ProcessSpec spec;
    
    spec.maximumBlockSize=samplesPerBlock;
    spec.sampleRate=sampleRate;
    spec.numChannels=numChannels;
    
    filter.prepare(spec);
    
    isPrepared=true;
    
}
void FilterController::process(juce::AudioBuffer<float>& buffer){
    jassert(isPrepared);// Review the status of is Prepared that only change in prepareToPlay method
    
    juce::dsp::AudioBlock<float> audioBlock {buffer};
    filter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
}

void FilterController::updateParameters(const int filterType, const float frequency, const float resonance, const float modulator){
    
    switch (filterType) {
        case 0:
            filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
        case 1:
            filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
        case 2:
            filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
            break;
        default:
            //Invalid Value pause the execution if failed
            jassertfalse;
            break;
    }

    auto modFreq = frequency * modulator;
    //Returns the maxmimum value between modFreq or 20.0
    // To avoid values less than 20 Hz
    modFreq=std::fmax(modFreq, 20.0f);
    
    // To avoid values more than 20 kHz
    modFreq=std::fminf(modFreq, 20000.0f);
    
    
    filter.setCutoffFrequency(modFreq);
    filter.setResonance(resonance);
    
}

void FilterController::reset(){
    filter.reset();
}
