/*
  ==============================================================================

    OscController.cpp
    Created: 8 Oct 2021 8:54:56pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#include "OscController.h"

void OscController::prepareToPlay(juce::dsp::ProcessSpec& spec){
    prepare(spec);
    _internalOsc.prepare(spec);
}


void OscController::setWaveType(const int waveType){
    
    /*
     
     Different equations
     Sin
     osc{ [](float x){return std::sin(x);}};
     
     Saw
     osc{ [](float x) { return x / juce::MathConstants<float>::pi; }};
     
     Square Wave
     osc{ [](float x){return x<0.0f ? -1.0f : 1.0f; }};
     
     */
    
    switch (waveType) {
        case 0:
            //Sin Wave
            initialise( [](float x){return std::sin(x);});
            break;
        case 1:
            //Saw Wave
            initialise( [](float x){return x / juce::MathConstants<float>::pi;});

            break;
        case 2:
            //Square Wave
            initialise( [](float x){return x<0.0f ? -1.0f : 1.0f;});
            break;
            
        default:
            //Invalid Value pause the execution if failed
            jassertfalse;
            break;
    }
}

void OscController::getNextAudioBlock (juce::dsp::AudioBlock<float>& block ){
    //FM modulation
    for(auto channel=0;channel<block.getNumChannels();channel++){
        for (auto sample=0;sample<block.getNumSamples();sample++){
            _fmModulation=_internalOsc.processSample(block.getSample(channel, sample) )* _fmDepth;
        }
    }
    
    //Reference as input to change the original element
    process(juce::dsp::ProcessContextReplacing<float>(block));
    
    
}

void OscController::setWaveFrequency (const int midiNoteNumber){
    
    //Add the value of the second oscillator for modulation
    auto currentFreq=juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + _fmModulation;
    setFrequency(currentFreq >=0 ?currentFreq : currentFreq*-1.0f);
    _lastMidiNote=midiNoteNumber;
}

void OscController::setFMParams(const float fmDepth, const float frequency){
    _internalOsc.setFrequency(frequency);
    _fmDepth=fmDepth;
    //ADD values before the Set Frequency
    // a validate if there is a negative value make it positive
    
    auto currentFreq=juce::MidiMessage::getMidiNoteInHertz(_lastMidiNote) + _fmModulation;
    setFrequency(currentFreq >=0 ?currentFreq : currentFreq*-1.0f);
}
