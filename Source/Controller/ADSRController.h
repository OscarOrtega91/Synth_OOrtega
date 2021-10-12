/*
  ==============================================================================

    ADSRController.h
    Created: 8 Oct 2021 7:49:14pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ADSRController: public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float release, const float sustain);
private:
    juce::ADSR::Parameters params;
};
