/*
  ==============================================================================

    CustomStyle.cpp
    Created: 23 Apr 2023 8:48:37am
    Author:  Oscar Ortega

  ==============================================================================
*/

#include "CustomStyle.h"

CustomStyle::CustomStyle(){
    
}

void CustomStyle::drawRotarySlider (juce::Graphics &g , int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider){
    
    //Define Colours
    const auto outlineColour = juce::Colour::fromRGB(88, 88, 88);
    const auto fillColour = juce::Colour::fromRGB(255,248,5);
    const auto mainColour = juce::Colour::fromRGB(104,104,104);
    const auto brigthColour = juce::Colour::fromRGB(128,128,128);
    
    
    auto rect = juce::Rectangle<int>(x,y,width,height).toFloat();
    auto centre = rect.getCentre();
    auto radio = juce::jmin ( rect.getWidth() / 1.9f , rect.getHeight() / 1.9f);
    
    radio -= 10.0f;
    
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    

    auto lineThickness = juce::jmin( width * 0.035f , radio * 0.5f);
    
    auto arcRad = radio - lineThickness * 1.1f;
    
    //Draw Background Arc
    juce::Path backgroundArc;
    //move the current position to starting point
    backgroundArc.startNewSubPath(centre.getX() + lineThickness * -3.7f, centre.getY() + lineThickness * 5.1f);
    //Add Arc
    backgroundArc.addCentredArc(rect.getCentreX(), rect.getCentreY(), arcRad, arcRad, 0.0f, rotaryStartAngle, rotaryEndAngle);
    
    g.setColour(outlineColour);
    //Draw Arc
    g.strokePath(backgroundArc, juce::PathStrokeType(lineThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
    auto dialRad = juce::jmax( radio - 3.0f * lineThickness, 10.0f);
    {
        juce::Graphics::ScopedSaveState saved(g);
        if(slider.isEnabled())
        {
            juce::ColourGradient fillGrad (brigthColour,
                                           centre.getX() + lineThickness * -5.0f,
                                           centre.getY() - lineThickness * 5.0f,
                                           mainColour,
                                           centre.getX() + dialRad,
                                           centre.getY() + dialRad,
                                           true);
            g.setGradientFill(fillGrad);
        }
    
    //Add Ellipse in the centre
    g.fillEllipse(centre.getX() - dialRad , centre.getY() - dialRad , dialRad * 2.0f , dialRad *2.0f);
    }
    
    dialRad = juce::jmax(dialRad - 4.0f, 10.0f);
    
    g.setColour(outlineColour.withAlpha(0.0f));
    
    g.drawEllipse(centre.getX() - dialRad, centre.getY()-dialRad , dialRad*2.0f, dialRad*2.0f, 4.0f);
    
    juce::Path dialValTrck;
    dialValTrck.addCentredArc(rect.getCentreX(), rect.getCentreY(), arcRad, arcRad, 0.0f, rotaryStartAngle, angle, true);
    
    g.setColour(fillColour);
    g.strokePath(dialValTrck, juce::PathStrokeType(lineThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
    g.setColour(fillColour);
    juce::Path dialTck;
    
    dialTck.startNewSubPath(centre.getPointOnCircumference(dialRad - lineThickness * 0.3f , angle));
    dialTck.lineTo(centre.getPointOnCircumference((dialRad - lineThickness) * 0.2f, angle));

    g.strokePath(dialTck, juce::PathStrokeType(lineThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
    
    
}

 
 
