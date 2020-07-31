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
    setSize (400, 400);
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

    if (m.isNoteOn())
    {
        messageDescription = { "note", "Note on " + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) };
    }
    else if (m.isNoteOff())
    {
        messageDescription = { "note", "Note off " + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) };
    }
    else if (m.isPitchWheel())
    {
       messageDescription = {"pitchBend", "Pitch bend " + juce::String (m.getPitchWheelValue()) };
    }
    else if (m.isChannelPressure())
    {
        messageDescription = { "channelPressure", "Channel pressure " + juce::String (m.getChannelPressureValue()) };
    }
    else if (m.isAftertouch())
    {
      messageDescription = { "aftertouch", "Aftertouch " + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) +  ": " + juce::String (m.getAfterTouchValue()) };
    }
    else if (m.isController())
    {
        juce::String name (juce::MidiMessage::getControllerName (m.getControllerNumber()));

        if (name.isEmpty())
            name = "[" + juce::String (m.getControllerNumber()) + "]";

        messageDescription = { "controller", "Controller " + name + ": " + juce::String (m.getControllerValue()) };
    }
    else if (m.isProgramChange())
    {
        messageDescription = { "programChange", "Program change " + juce::String (m.getProgramChangeNumber()) };
    }
    else if (m.isAllNotesOff())
    {
        messageDescription = { "allNotesOff", "All notes off" };
    }
    else
    {
        messageDescription = { "unknown", juce::String::toHexString (m.getRawData(), m.getRawDataSize()) };
    }

    return messageDescription;
}