/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth_OOrtegaAudioProcessorEditor::Synth_OOrtegaAudioProcessorEditor (Synth_OOrtegaAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsrSliders(audioProcessor.apvts,"ATTACK", "DECAY", "RELEASE", "SUSTAIN" ), oscComboBox(audioProcessor.apvts), filterView(audioProcessor.apvts),
        modAdsrSliders(audioProcessor.apvts,"MODATTACK", "MODDECAY", "MODRELEASE" ,"MODSUSTAIN")
{

    addAndMakeVisible(adsrSliders);
    addAndMakeVisible(oscComboBox);
    addAndMakeVisible(filterView);
    addAndMakeVisible(modAdsrSliders);

    setSize (600, 500);
}

Synth_OOrtegaAudioProcessorEditor::~Synth_OOrtegaAudioProcessorEditor()
{
}

//==============================================================================
void Synth_OOrtegaAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour (juce::Colours::orange);
    auto border = 3.0f;
    //To Draw Dashed Line
    //juce::Point<float> _begin{ 0.0f , 0.0f};
    //juce::Point<float> _begin2{ static_cast<float>(getWidth()), 0.0f};
    //juce::Line<float> line {_begin,_begin2};
    //float dashPattern[] {4,5,6,8};
    //g.drawDashedLine(line, dashPattern, 4, 3.0f);
    
    g.drawLine(border, border, static_cast<float>(getWidth()-border), border);
    g.drawLine(border, border, border, static_cast<float>(getHeight()/2 -border));
    
    g.drawLine(border, static_cast<float>(getHeight()/2-border),static_cast<float>(getWidth()-border), static_cast<float>(getHeight()/2 -border) );
    
    g.drawLine(static_cast<float>(getWidth()-border), border,static_cast<float>(getWidth()-border), static_cast<float>(getHeight()/2 -border) );
    
    
    
    //Draw Rectangle in the bottom
    
    g.drawLine(border, static_cast<float>(getHeight()/2+border),static_cast<float>(getWidth()-border), static_cast<float>(getHeight()/2+border));
    
    g.drawLine(border, static_cast<float>(getHeight()/2 +border), border,static_cast<float>(getHeight()-border));
    
    g.drawLine(static_cast<float>(getWidth()-border), static_cast<float>(getHeight()/2+border), static_cast<float>(getWidth()-border),static_cast<float>(getHeight()-border));
               


    g.drawLine(border,static_cast<float>(getHeight()-border), static_cast<float>(getWidth()-border),static_cast<float>(getHeight()-border));
    

    
    //juce::Path path;
    //juce::Rectangle<float> area (0,0, getWidth(), getHeight()/2 );
    //path.addRectangle (area);
    
    //g.fillPath(path);
    
}

void Synth_OOrtegaAudioProcessorEditor::resized()
{


    auto border = 10;
   

    
    oscComboBox.setBounds(border, border, getWidth()/2 - border, getHeight()/2 - border);
    adsrSliders.setBounds( (getWidth()/2) + border, border , getWidth()/2 - border, getHeight()/2 - border);
    
    filterView.setBounds(border,(getHeight()/2) + border,  getWidth()/2 - border, getHeight()/2 - border);
    
    modAdsrSliders.setBounds((getWidth()/2) + border, (getHeight()/2) + border, getWidth()/2 - border, getHeight()/2 - border);
    
    
}


