/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "View/ADSRComponent.h"
#include "View/OscComponent.h"
#include "View/FilterComponent.h"
#include "View/CustomStyle.h"

//==============================================================================
/**
*/
class Synth_OOrtegaAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Synth_OOrtegaAudioProcessorEditor (Synth_OOrtegaAudioProcessor&);
    ~Synth_OOrtegaAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Synth_OOrtegaAudioProcessor& audioProcessor;
    CustomStyle customLooknFeel;

    
    ADSRComponent adsrSliders;
    OscComponent oscComboBox;

    FilterComponent filterView;
    ADSRComponent modAdsrSliders;
    
    juce::MidiKeyboardComponent _midiKeyboard;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth_OOrtegaAudioProcessorEditor)
};
