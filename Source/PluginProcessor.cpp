/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiMonitorAudioProcessor::MidiMonitorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

MidiMonitorAudioProcessor::~MidiMonitorAudioProcessor()
{
}

//==============================================================================
const juce::String MidiMonitorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiMonitorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiMonitorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiMonitorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidiMonitorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiMonitorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidiMonitorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiMonitorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MidiMonitorAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidiMonitorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MidiMonitorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MidiMonitorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiMonitorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
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

bool MidiMonitorAudioProcessor::midiMessageQueueEmpty() {
    return messageQueue.empty();
}

juce::MidiMessage MidiMonitorAudioProcessor::getMidiMessage() {
    juce::MidiMessage message = messageQueue.front();
    messageQueue.pop();
    return message;
}

void MidiMonitorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();

    juce::MidiMessage message;
    for (const auto meta: midiMessages)
    {
        message = meta.getMessage();
        messageQueue.push(message);
    }
}

//==============================================================================
bool MidiMonitorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MidiMonitorAudioProcessor::createEditor()
{
    return new MidiMonitorAudioProcessorEditor (*this);
}

//==============================================================================
void MidiMonitorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidiMonitorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiMonitorAudioProcessor();
}
