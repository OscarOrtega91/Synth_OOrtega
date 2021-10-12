/*
  ==============================================================================

    OscComponent.h
    Created: 8 Oct 2021 9:19:15pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox _oscSelector;
    using _comboBoxAttachment=juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    using _sliderAttachment=juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<_comboBoxAttachment> _oscAttachment;
    juce::Slider _fmDepthSlider;
    juce::Slider _fmFreqSlider;
    

    std::unique_ptr<_sliderAttachment> _fmDepthAttachment;
    std::unique_ptr<_sliderAttachment> _fmFreqAttachment;
    
    juce::Label _fmFreqLabel{ "FMFREQ","FM Frequency"};
    juce::Label _fmDepthLabel{ "FMDEPTH","FM Depth"};
    juce::Label _oscLabel{ "OSC","Oscillator"};
    juce::Label _waveTypeLabel{ "WAVETYP","Wave Type"};

    void setSliderAndLabel(std::unique_ptr<_sliderAttachment>& attachment,juce::Slider& slider,  juce::AudioProcessorValueTreeState& apvts, juce::String idAttachment, juce::Label& label);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
