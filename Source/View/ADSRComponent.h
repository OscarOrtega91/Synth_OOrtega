/*
  ==============================================================================

    ADSRComponent.h
    Created: 8 Oct 2021 7:48:38pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ADSRComponent  : public juce::Component
{
public:
    ADSRComponent(juce::AudioProcessorValueTreeState& apvts, juce::String idAttack , juce::String idDecay, juce::String idRelease, juce::String idSustain);
    ~ADSRComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider _attackSlider;
    juce::Slider _decaySlider;
    juce::Slider _releaseSlider;
    juce::Slider _sustainSlider;
    
    using _sliderAttachment=juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<_sliderAttachment> _attackAttachment;
    std::unique_ptr<_sliderAttachment> _decayAttachment;
    std::unique_ptr<_sliderAttachment> _releaseAttachment;
    std::unique_ptr<_sliderAttachment> _sustainAttachment;
    juce::Label _attackLabel{ "A","A"};
    juce::Label _decayLabel{ "D","D"};
    juce::Label _sustainLabel{ "S","S"};
    juce::Label _releaseLabel{ "R","R"};

    void setSliderAndLabel(std::unique_ptr<_sliderAttachment>& attachment,juce::Slider& slider,  juce::AudioProcessorValueTreeState& apvts, juce::String idAttachment, juce::Label& label );
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComponent)
};
