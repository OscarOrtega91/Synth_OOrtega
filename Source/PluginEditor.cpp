/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth_OOrtegaAudioProcessorEditor::Synth_OOrtegaAudioProcessorEditor (Synth_OOrtegaAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsrSliders(audioProcessor.apvts,"ATTACK", "DECAY", "RELEASE", "SUSTAIN" ), oscComboBox(audioProcessor.apvts,customLooknFeel), filterView(audioProcessor.apvts,customLooknFeel),
        modAdsrSliders(audioProcessor.apvts,"MODATTACK", "MODDECAY", "MODRELEASE" ,"MODSUSTAIN"),
        _midiKeyboard(audioProcessor.getKeyboardState(), juce::MidiKeyboardComponent::horizontalKeyboard)
{

    addAndMakeVisible(adsrSliders);
    addAndMakeVisible(oscComboBox);
    addAndMakeVisible(filterView);
    addAndMakeVisible(modAdsrSliders);
    addAndMakeVisible(_midiKeyboard);
    
    
    // Add Elements to Midi Map Elements
    // Paint New Elements from New Class
    // Clean git files to dont push the builds
    
    
    setSize (900, 600);
}

Synth_OOrtegaAudioProcessorEditor::~Synth_OOrtegaAudioProcessorEditor()
{
}

//==============================================================================
void Synth_OOrtegaAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    const auto fillColour = juce::Colour::fromRGB(255,248,5);

    g.setColour (fillColour);
    
    auto border = 3.0f;
    //To Draw Dashed Line
    //juce::Point<float> _begin{ 0.0f , 0.0f};
    //juce::Point<float> _begin2{ static_cast<float>(getWidth()), 0.0f};
    //juce::Line<float> line {_begin,_begin2};
    //float dashPattern[] {4,5,6,8};
    //g.drawDashedLine(line, dashPattern, 4, 3.0f);
    //g.drawLine(<#float startX#>, <#float startY#>, <#float endX#>, <#float endY#>)
    g.drawLine(border, border, static_cast<float>(getWidth()/2 -border), border);
    g.drawLine(border, border, border, static_cast<float>(getHeight()/2 -border));
    
    g.drawLine(border, static_cast<float>(getHeight()/2-border),static_cast<float>(getWidth()/2 - border), static_cast<float>(getHeight()/2 -border) );
    
    g.drawLine(static_cast<float>(getWidth()/2 - border), border , static_cast<float>(getWidth()/2 - border), static_cast<float>(getHeight()/2 -border) );
    
    
    
    //Draw Rectangle in the bottom
    
    g.drawLine(static_cast<float>(getWidth()/2 + border), border ,static_cast<float>(getWidth() - border), border);
    
    g.drawLine(static_cast<float>(getWidth() - border), border, static_cast<float>(getWidth() - border),static_cast<float>(getHeight()/2 -border));
    
    g.drawLine(static_cast<float>(getWidth()/2 + border), border, static_cast<float>(getWidth()/2 + border),static_cast<float>(getHeight()/2 - border));
               
    g.drawLine(static_cast<float>(getWidth()/2 + border), static_cast<float>(getHeight()/2 - border), static_cast<float>(getWidth() - border),static_cast<float>(getHeight()/2 - border));
    

    
    //juce::Path path;
    //juce::Rectangle<float> area (0,0, getWidth(), getHeight()/2 );
    //path.addRectangle (area);
    
    //g.fillPath(path);
    
}

void Synth_OOrtegaAudioProcessorEditor::resized()
{


    auto border = 10;
   

    
    oscComboBox.setBounds(border, border, getWidth()/4 - border, getHeight()/2 - border);
    adsrSliders.setBounds( (getWidth()/4) + border, border , getWidth()/4 - border, getHeight()/2 - border);
    
    filterView.setBounds( (getWidth()/4) * 2 + border   , border ,  getWidth()/4 - border, getHeight()/2 - border);
    
    modAdsrSliders.setBounds((getWidth()/4) * 3 + border ,  border , getWidth()/4 - border, getHeight()/2 - border);
    
    _midiKeyboard.setBounds(border , getHeight()/2 + border*4, getWidth() - border * 2, getHeight()/3.5 - border);
    
    
}


