/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct MidiMessageDescription {
    juce::String type;
    juce::String description;
};

//==============================================================================
/**
*/
class MidiMonitorAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                         public juce::Timer
{
public:
    MidiMonitorAudioProcessorEditor (MidiMonitorAudioProcessor&);
    ~MidiMonitorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void addMessageToList (const juce::MidiMessage& message, const juce::String& source);

private:
    void timerCallback() override;
    void postMessageToList (const juce::MidiMessage& message, const juce::String& source);
    void logMessage (const juce::String& m);
    static MidiMessageDescription getMidiMessageDescription (const juce::MidiMessage& m);
    // static juce::String getMidiMessageDescription (const juce::MidiMessage& m);

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiMonitorAudioProcessor& audioProcessor;

    juce::TextEditor midiMessagesBox;
    double startTime;

    std::map<juce::String,bool> shownMessages = {
      { "note", true },
      { "pitchWheel", false },
      { "channelPressure", false },
      { "aftertouch", false },
      { "programChange", false },
      { "allNotesOn", false },
      { "allNotesOff", false },
      { "metaEvent", false },
      { "controller", false },
      { "unknown", false }
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiMonitorAudioProcessorEditor)
};


// This is used to dispach an incoming message to the message thread
class IncomingMessageCallback   : public juce::CallbackMessage
{
public:
    IncomingMessageCallback (MidiMonitorAudioProcessorEditor* o, const juce::MidiMessage& m, const juce::String& s)
        : owner (o), message (m), source (s)
    {}

    void messageCallback() override
    {
        if (owner != nullptr)
            owner->addMessageToList (message, source);
    }

    MidiMonitorAudioProcessorEditor::SafePointer<MidiMonitorAudioProcessorEditor> owner;
    juce::MidiMessage message;
    juce::String source;
};
