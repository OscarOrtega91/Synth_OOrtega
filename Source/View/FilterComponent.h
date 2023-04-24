/*
  ==============================================================================

    FilterComponent.h
    Created: 11 Oct 2021 2:00:29pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomStyle.h"

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, CustomStyle& style);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::ComboBox _filterSelector;
    using _comboBoxAttachment=juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    using _sliderAttachment=juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<_comboBoxAttachment> _filterAttachment;
    juce::Slider _cutoffFreqSlider;
    juce::Slider _resonanceSlider;
    
    CustomStyle &customLooknFeel;

    std::unique_ptr<_sliderAttachment> _cutoffFreqAttachment;
    std::unique_ptr<_sliderAttachment> _resonanceAttachment;
    
    juce::Label _filterTypeLabel{ "FILTERTYPE","Filter"};
    juce::Label _cutoffFreLabel{ "CUTOFFFREQUENCY","Cut-off Frequency"};
    juce::Label _resonanceLabel{ "RESONANCE","Resonance"};
    
    void setSliderAndLabel(std::unique_ptr<_sliderAttachment>& attachment,juce::Slider& slider,  juce::AudioProcessorValueTreeState& apvts, juce::String idAttachment, juce::Label& label);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
