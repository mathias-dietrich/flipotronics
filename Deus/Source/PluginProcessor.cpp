/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Model.h"

//==============================================================================
DeusAudioProcessor::DeusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                     #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), false)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    instance = this;
    Model::of()->init();
    
    // load default Preset
 
    ImageFactory::of().init();
}

DeusAudioProcessor::~DeusAudioProcessor()
{
    ImageFactory::of().close();
}


//==============================================================================
const String DeusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DeusAudioProcessor::acceptsMidi() const
{
    return true;
}

bool DeusAudioProcessor::producesMidi() const
{
    return false;
}

bool DeusAudioProcessor::isMidiEffect() const
{
    return false;
}

double DeusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DeusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DeusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DeusAudioProcessor::setCurrentProgram (int index)
{
}

const String DeusAudioProcessor::getProgramName (int index)
{
    return {};
}

void DeusAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DeusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    core.init(sampleRate,samplesPerBlock );
    core.configure(Model::of()->preset);
}

void DeusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DeusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void DeusAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    int totalNumInputChannels  = getTotalNumInputChannels();
    int totalNumOutputChannels = getTotalNumOutputChannels();
    core.processBlock(buffer, midiMessages, totalNumInputChannels, totalNumOutputChannels);
}

//==============================================================================
bool DeusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DeusAudioProcessor::createEditor()
{
    return new DeusAudioProcessorEditor (*this);
}

//==============================================================================
void DeusAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DeusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DeusAudioProcessor();
}

DeusAudioProcessor * DeusAudioProcessor::instance = 0;
