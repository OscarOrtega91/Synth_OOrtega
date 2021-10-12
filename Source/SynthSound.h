/*
  ==============================================================================

    SynthSound.h
    Created: 6 Oct 2021 7:08:08pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override;
    bool appliesToChannel (int midiChannel) override;
private:
    
};
