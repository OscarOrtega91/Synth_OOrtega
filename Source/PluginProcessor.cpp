/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
Synth_OOrtegaAudioProcessor::Synth_OOrtegaAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

Synth_OOrtegaAudioProcessor::~Synth_OOrtegaAudioProcessor()
{
}

//==============================================================================
const juce::String Synth_OOrtegaAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Synth_OOrtegaAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Synth_OOrtegaAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Synth_OOrtegaAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Synth_OOrtegaAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Synth_OOrtegaAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Synth_OOrtegaAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Synth_OOrtegaAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Synth_OOrtegaAudioProcessor::getProgramName (int index)
{
    return {};
}

void Synth_OOrtegaAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Synth_OOrtegaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i=0;i< synth.getNumVoices();i++){
        //Cast to the class create it
        // To get access to the new method
        if(auto voice= dynamic_cast<SynthVoice*>(synth.getVoice(i))){
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels() );
        }
    }
    
}

void Synth_OOrtegaAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Synth_OOrtegaAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Synth_OOrtegaAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int i=0; i< synth.getNumVoices();i++)
    {
        //Cast all voices
        if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
           //OSC Controls
            
            auto& waveType= *apvts.getRawParameterValue("OSC");
            auto& fmDepth=*apvts.getRawParameterValue("FMDEPTH");
            auto& frequency=*apvts.getRawParameterValue("FMFREQ");
            
            auto& attack= *apvts.getRawParameterValue("ATTACK");
            auto& decay= *apvts.getRawParameterValue("DECAY");
            auto& release= *apvts.getRawParameterValue("RELEASE");
            auto& sustain= *apvts.getRawParameterValue("SUSTAIN");

            //Filter Processing
            auto& filterType= *apvts.getRawParameterValue("FILTERTYPE");
            auto& frequencyFilter= *apvts.getRawParameterValue("FILTERCUTOFFFREQ");
            auto& filterResonance= *apvts.getRawParameterValue("FILTERRES");
            
            //MOD Controls
             auto& mod_attack= *apvts.getRawParameterValue("MODATTACK");
             auto& mod_decay= *apvts.getRawParameterValue("MODDECAY");
             auto& mod_release= *apvts.getRawParameterValue("MODRELEASE");
             auto& mod_sustain= *apvts.getRawParameterValue("MODSUSTAIN");
            
            voice->setWaveType(waveType.load());
            voice->setFMParams(fmDepth.load(), frequency.load());
            voice->updateADSR( attack.load() , decay.load() , release.load(), sustain.load());
            voice->updateFilter(filterType.load(), frequencyFilter.load(), filterResonance.load());
            voice->updateModADSR(mod_attack.load(), mod_decay.load(), mod_release.load(), mod_sustain.load());
            
            
            
        }
    }


    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    

    
}

//==============================================================================
bool Synth_OOrtegaAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Synth_OOrtegaAudioProcessor::createEditor()
{
    return new Synth_OOrtegaAudioProcessorEditor (*this);
}

//==============================================================================
void Synth_OOrtegaAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Synth_OOrtegaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Synth_OOrtegaAudioProcessor();
}


juce::AudioProcessorValueTreeState::ParameterLayout Synth_OOrtegaAudioProcessor::createParameterLayout(){
    
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    //Oscillator Selector
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator", juce::StringArray{"Sine","Saw","Square"}, 0));
    //Modulation
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMFREQ","FM Frequency", juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01, 0.4f }, 10.0f));
    //Values in Hertz
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMDEPTH","FM Depth", juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01, 0.4f}, 600.0f));
    
    //ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK","Attack", juce::NormalisableRange<float> {0.1f, 1.0f, 0.001, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY","Decay", juce::NormalisableRange<float> {0.1f, 1.0f, 0.001, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN","Sustain", juce::NormalisableRange<float> {0.1f, 1.0f, 0.001, 1.0f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE","Release", juce::NormalisableRange<float> {0.1f, 3.0f, 0.001, 1.0f}, 0.5f));
    
    
    // Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray{"Low Pass","Band Pass ","High Pass"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFFFREQ","Cut off Frequency", juce::NormalisableRange<float> {20.0f, 20000.0f, 1, 0.6f}, 200.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES"," Filter Resonance", juce::NormalisableRange<float> {1.0f, 10.0f, 0.1f,}, 2.0f));
    
    
    //FILTER ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODATTACK","Mod Attack", juce::NormalisableRange<float> {0.1f, 1.0f, 0.001, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODDECAY","Mod Decay", juce::NormalisableRange<float> {0.1f, 1.0f, 0.001, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODSUSTAIN","Mod Sustain", juce::NormalisableRange<float> {0.1f, 1.0f, 0.001, 1.0f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODRELEASE","Mod Release", juce::NormalisableRange<float> {0.1f, 3.0f, 0.001, 1.0f}, 0.5f));
    
    
    return {params.begin(),params.end()};
    
}
