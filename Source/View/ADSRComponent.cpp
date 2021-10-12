/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 8 Oct 2021 7:48:38pm
    Author:  Oscar Ortega

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState& apvts, juce::String idAttack , juce::String idDecay, juce::String idRelease, juce::String idSustain)
{
    //& to only pass the reference and not make a copy of the element
    // Initialize ADSRComponent in the constructor of PluginEditor
    // with apvts reference

    setSliderAndLabel(_attackAttachment, _attackSlider, apvts, idAttack, _attackLabel);
    setSliderAndLabel(_decayAttachment, _decaySlider, apvts, idDecay, _decayLabel);
    setSliderAndLabel(_releaseAttachment, _releaseSlider, apvts, idRelease, _releaseLabel);
    setSliderAndLabel(_sustainAttachment, _sustainSlider, apvts, idSustain, _sustainLabel);

}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colours::black);
}

void ADSRComponent::resized()
{
    const auto bound= getLocalBounds().reduced(10);
    
    const auto padding= 10;
    const auto labelSpace=30;
    
    const auto sliderHeight= (bound.getHeight()/4)-padding;
    const auto sliderWidth= (bound.getWidth())-padding -labelSpace;
    
    const auto sliderStartX=bound.getWidth()/2 -(sliderWidth/2);
    const auto sliderStartY=0;

    _attackSlider.setBounds(sliderStartX+labelSpace, sliderStartY, sliderWidth-padding, sliderHeight);
    _attackLabel.setBounds(sliderStartX, sliderStartY + (sliderHeight/2), labelSpace, 15);
    
    
    
    _decaySlider.setBounds(sliderStartX+labelSpace, _attackSlider.getBottom()+padding, sliderWidth-padding, sliderHeight);
    _decayLabel.setBounds(sliderStartX, _attackSlider.getBottom()+ (sliderHeight/2), labelSpace, 15);
    
    _sustainSlider.setBounds(sliderStartX+labelSpace, _decaySlider.getBottom()+padding, sliderWidth-padding, sliderHeight);
    _sustainLabel.setBounds(sliderStartX, _decaySlider.getBottom()+ (sliderHeight/2), labelSpace, 15);
    
    _releaseSlider.setBounds(sliderStartX+labelSpace,  _sustainSlider.getBottom()+padding, sliderWidth-padding, sliderHeight);
    _releaseLabel.setBounds(sliderStartX, _sustainSlider.getBottom()+ (sliderHeight/2), labelSpace, 15);
}



void ADSRComponent::setSliderAndLabel(std::unique_ptr<_sliderAttachment>& attachment,juce::Slider& slider,  juce::AudioProcessorValueTreeState& apvts, juce::String idAttachment, juce::Label& label ){
    
    attachment = std::make_unique<_sliderAttachment>(apvts, idAttachment, slider);
    
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50,  20);
    addAndMakeVisible(slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(15.0f);
    addAndMakeVisible(label);

}
