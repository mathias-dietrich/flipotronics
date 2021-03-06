/*
  ==============================================================================

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "img.h"

Synth1AudioProcessor::Synth1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                      )
#endif
{
    core = new Core();
    
     //setWantsKeyboardFocus(true);
}

Synth1AudioProcessor::~Synth1AudioProcessor(){
    delete core;
}

//==============================================================================
const String Synth1AudioProcessor::getName() const{
    return JucePlugin_Name;
}

bool Synth1AudioProcessor::acceptsMidi() const{
    return true;
}

bool Synth1AudioProcessor::producesMidi() const{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Synth1AudioProcessor::isMidiEffect() const{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Synth1AudioProcessor::getTailLengthSeconds() const{
    return 0.0;
}

int Synth1AudioProcessor::getNumPrograms(){
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Synth1AudioProcessor::getCurrentProgram(){
    return 0;
}

void Synth1AudioProcessor::setCurrentProgram (int index){
}

const String Synth1AudioProcessor::getProgramName (int index){
    return {};
}

void Synth1AudioProcessor::changeProgramName (int index, const String& newName){
    
}

//==============================================================================
void Synth1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock){
    maxTimeMsec = 1000 * samplesPerBlock / sampleRate;
    setArp(false);
    isArpOn = false;
    
    BankLoader::of().load();
    loadPatch(0);
    core->init( sampleRate,  samplesPerBlock);
    waveComponent.init(sampleRate, samplesPerBlock);
    adsrComponent.init(sampleRate, samplesPerBlock);
    lfoComponent.init(sampleRate, samplesPerBlock);
    outputComponent.init(sampleRate, samplesPerBlock);
    spectrum.init(sampleRate, samplesPerBlock);
    curveComponent.init(sampleRate, samplesPerBlock);
    showTableComponent.init(sampleRate, samplesPerBlock);
}

void Synth1AudioProcessor::releaseResources(){
    core->close();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Synth1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const{
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

void Synth1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages){
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    core->handle(buffer, midiMessages, totalNumInputChannels, totalNumOutputChannels);
    spectrum.getNextAudioBlock();
    outputComponent.getNextAudioBlock();
}

//==============================================================================
bool Synth1AudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Synth1AudioProcessor::createEditor() {
    return new Synth1AudioProcessorEditor (*this);
}

//==============================================================================
void Synth1AudioProcessor::getStateInformation (MemoryBlock& destData){
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Synth1AudioProcessor::setStateInformation (const void* data, int sizeInBytes){
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter(){
    return new Synth1AudioProcessor();
}
