/*
  ==============================================================================

    CustomStyle.h
    Created: 23 Apr 2023 8:48:37am
    Author:  Oscar Ortega

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CustomStyle : public juce::LookAndFeel_V4
{
public:
    CustomStyle();
    void drawRotarySlider (juce::Graphics &g , int x, int y, int width, int height,
                           float sliderPos, float rotaryStartAngle,
                           float rotaryEndAngle, juce::Slider &slider) override;
    

};
