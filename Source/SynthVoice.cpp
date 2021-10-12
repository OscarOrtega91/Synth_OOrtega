/*
  ==============================================================================

    SynthVoice.cpp
    Created: 6 Oct 2021 7:07:55pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound ){
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
     
}
void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition){

    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
    modADSR.noteOn();
    
}
void SynthVoice::stopNote (float velocity, bool allowTailOff) {

    adsr.noteOff();
    modADSR.noteOff();
    if(! allowTailOff || !adsr.isActive())
        clearCurrentNote();
}
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue) {

}
void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels){
    adsr.setSampleRate(sampleRate);
    
    //Initialize DSP Variables for Oscillator
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize=samplesPerBlock;
    spec.sampleRate=sampleRate;
    spec.numChannels= outputChannels;
    
    osc.prepareToPlay(spec);
    adsr.setSampleRate(sampleRate);

    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    modADSR.setSampleRate(sampleRate);
    
    gain.prepare(spec);
    
    gain.setGainLinear(0.5f);
    isPrepared= true;
}



void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) {
    
    jassert(isPrepared);// Review the status of is Prepared that only change in prepareToPlay method
    
    if(! isVoiceActive())
        return;
    _synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples,false,false,true);
    modADSR.applyEnvelopeToBuffer(_synthBuffer, 0, numSamples);
    _synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock {_synthBuffer};
    
    osc.getNextAudioBlock(audioBlock);
    adsr.applyEnvelopeToBuffer(_synthBuffer, 0, _synthBuffer.getNumSamples());

    filter.process(_synthBuffer);

    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
    
    for(int i=0;i<outputBuffer.getNumChannels();i++){
        outputBuffer.addFrom(i, startSample, _synthBuffer, i, 0, numSamples);
        if(!adsr.isActive()){
            clearCurrentNote();
        }
    }

}

void SynthVoice::updateADSR(const float attack, const float decay, const float release, const float sustain){
    adsr.updateADSR(attack,decay,release,sustain);
}
void SynthVoice::updateModADSR(const float attack, const float decay, const float release, const float sustain){
    modADSR.updateADSR(attack, decay, release, sustain);
    
}

void SynthVoice::updateFilter(const int filterType, const float frequency, const float resonance){
    
    float modulator = modADSR.getNextSample();
    filter.updateParameters(filterType, frequency, resonance,modulator);
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue){
    
}


void SynthVoice::setWaveType(const int waveType){
    osc.setWaveType(waveType);
}

void SynthVoice::setFMParams(const float fmDepth, const float frequency){
    osc.setFMParams(fmDepth,  frequency);
}
