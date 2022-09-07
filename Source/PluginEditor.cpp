/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiMonitorAudioProcessorEditor::MidiMonitorAudioProcessorEditor (MidiMonitorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    startTime (juce::Time::getMillisecondCounterHiRes() * 0.001)
{
    setSize (480, 400);
    addAndMakeVisible(mainPanel);

    // Start polling processor for Midi Messages
    startTimer(10);
}

MidiMonitorAudioProcessorEditor::~MidiMonitorAudioProcessorEditor()
{
}

//==============================================================================
void MidiMonitorAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void MidiMonitorAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    mainPanel.setBounds(area);
}

void MidiMonitorAudioProcessorEditor::timerCallback() 
{
    if (!audioProcessor.midiMessageQueueEmpty()) {
        juce::MidiMessage message = audioProcessor.getMidiMessage();
        postMessageToList(message);
    }
}

void MidiMonitorAudioProcessorEditor::postMessageToList (const juce::MidiMessage& message)
{
    (new IncomingMessageCallback (this, message))->post();
}

void MidiMonitorAudioProcessorEditor::addMessageToList (const juce::MidiMessage& message)
{
    auto messageDescription = getMidiMessageDescription (message);

    if (mainPanel.messageTypeSelected(messageDescription)) {
        mainPanel.logMessage (messageDescription.description);
    }
}

MidiMessageDescription MidiMonitorAudioProcessorEditor::getMidiMessageDescription (const juce::MidiMessage& m)
{
    MidiMessageDescription messageDescription;
    String midiChannelText = " [CH " + juce::String(m.getChannel()) + "]";

    if (m.isNoteOn())
    {
        messageDescription = { "note", "Note on " + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) + 
                midiChannelText};
    }
    else if (m.isNoteOff())
    {
        messageDescription = { "note", "Note off " + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) + 
                midiChannelText};
    }
    else if (m.isPitchWheel())
    {
       messageDescription = {"pitchBend", "Pitch bend " + juce::String (m.getPitchWheelValue()) + 
                midiChannelText};
    }
    else if (m.isChannelPressure())
    {
        messageDescription = { "channelPressure", "Channel pressure " + juce::String (m.getChannelPressureValue()) + 
                midiChannelText};
    }
    else if (m.isAftertouch())
    {
      messageDescription = { "aftertouch", "Aftertouch " + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) +  ": " + juce::String (m.getAfterTouchValue()) + 
                midiChannelText};
    }
    else if (m.isController())
    {
        juce::String name (juce::MidiMessage::getControllerName (m.getControllerNumber()));

        if (name.isEmpty())
            name = "[" + juce::String (m.getControllerNumber()) + "]";

        messageDescription = { "controller", "Controller " + name + ": " + juce::String (m.getControllerValue()) + 
                midiChannelText};
    }
    else if (m.isProgramChange())
    {
        messageDescription = { "programChange", "Program change " + juce::String (m.getProgramChangeNumber()) + 
                midiChannelText};
    }
    else if (m.isAllNotesOff())
    {
        messageDescription = { "allNotesOff", "All notes off" + midiChannelText};
    }
    else
    {
        messageDescription = { "unknown", juce::String::toHexString (m.getRawData(), m.getRawDataSize()) + 
                midiChannelText};
    }

    return messageDescription;
}