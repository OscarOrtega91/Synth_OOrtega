/*
  ==============================================================================

    OscComponent.cpp
    Created: 8 Oct 2021 9:19:15pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts,CustomStyle& style):
customLooknFeel(style)
{
    juce::StringArray choices {"Sine", "Saw", "Square"};
    
    _oscAttachment = std::make_unique<_comboBoxAttachment>( apvts, "OSC", _oscSelector);
    _oscSelector.addItemList(choices, 1);
    _oscSelector.setSelectedItemIndex(0);
    
    addAndMakeVisible(_oscSelector);
    
    setSliderAndLabel(_fmFreqAttachment, _fmFreqSlider, apvts, "FMFREQ", _fmFreqLabel);
   
    setSliderAndLabel(_fmDepthAttachment, _fmDepthSlider, apvts, "FMDEPTH", _fmDepthLabel);
    
    _oscLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    _oscLabel.setJustificationType(juce::Justification::left);
    _oscLabel.setFont(18.0f);
    
    _waveTypeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    _waveTypeLabel.setJustificationType(juce::Justification::centred);
    _waveTypeLabel.setFont(15.0f);
    
    addAndMakeVisible(_oscLabel);
    addAndMakeVisible(_waveTypeLabel);

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    auto border=10;
    
    _oscLabel.setBounds(0, border, getWidth(), 15);
    _waveTypeLabel.setBounds(0, border*3, getWidth(), 15);
    _oscSelector.setBounds(0, border*5, getWidth(), 30);
    
    _fmFreqSlider.setBounds(0, getHeight()/2 -10, 100 , 90);
    _fmFreqLabel.setBounds(_fmFreqSlider.getX(), _fmFreqSlider.getY()-20, _fmFreqSlider.getWidth(), 15);
    
    _fmDepthSlider.setBounds(110, getHeight()/2 -10, 100 , 90);
    _fmDepthLabel.setBounds(_fmDepthSlider.getX(), _fmDepthSlider.getY()-20, _fmDepthSlider.getWidth(), 15);
    
    

}

void OscComponent::setSliderAndLabel(std::unique_ptr<_sliderAttachment>& attachment,juce::Slider& slider,  juce::AudioProcessorValueTreeState& apvts, juce::String idAttachment, juce::Label& label ){
    
    attachment = std::make_unique<_sliderAttachment>(apvts, idAttachment, slider);
    
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50,  25);
    slider.setLookAndFeel(&customLooknFeel);
    slider.setMouseDragSensitivity(50);
    addAndMakeVisible(slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centredTop);
    label.setFont(15.0f);
    addAndMakeVisible(label);

}
