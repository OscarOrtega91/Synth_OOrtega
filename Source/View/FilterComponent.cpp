/*
  ==============================================================================

    FilterComponent.cpp
    Created: 11 Oct 2021 2:00:29pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts)
{
    juce::StringArray choices {"Low Pass", "Band Pass", "High Pass"};
    
    _filterAttachment = std::make_unique<_comboBoxAttachment>( apvts, "FILTERTYPE", _filterSelector);
    _filterSelector.addItemList(choices, 1);
    _filterSelector.setSelectedItemIndex(0);
    
    addAndMakeVisible(_filterSelector);
    
    _filterTypeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    _filterTypeLabel.setJustificationType(juce::Justification::centred);
    _filterTypeLabel.setFont(15.0f);
    addAndMakeVisible(_filterTypeLabel);
    
    setSliderAndLabel(_cutoffFreqAttachment, _cutoffFreqSlider, apvts, "FILTERCUTOFFFREQ", _cutoffFreLabel);
   
    setSliderAndLabel(_resonanceAttachment, _resonanceSlider, apvts, "FILTERRES", _resonanceLabel);

}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colours::black);
}

void FilterComponent::resized()
{
    auto border=5;
    
    _filterTypeLabel.setBounds(0, 0, getWidth()-border, 15);
    _filterSelector.setBounds(0, 20, getWidth()-border, 30);
    
    _cutoffFreqSlider.setBounds(0, getHeight()/2 -10, 100 , 100);
    _cutoffFreLabel.setBounds(_cutoffFreqSlider.getX(), _cutoffFreqSlider.getY()-20, _cutoffFreqSlider.getWidth(), 15);
    
    _resonanceSlider.setBounds(110, getHeight()/2 -10, 100 , 100);
    _resonanceLabel.setBounds(_resonanceSlider.getX(), _resonanceSlider.getY()-20, _resonanceSlider.getWidth(), 15);

}

void FilterComponent::setSliderAndLabel(std::unique_ptr<_sliderAttachment>& attachment,juce::Slider& slider,  juce::AudioProcessorValueTreeState& apvts, juce::String idAttachment, juce::Label& label ){
    
    attachment = std::make_unique<_sliderAttachment>(apvts, idAttachment, slider);
    
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50,  25);
    addAndMakeVisible(slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centredTop);
    label.setFont(15.0f);
    addAndMakeVisible(label);

}
