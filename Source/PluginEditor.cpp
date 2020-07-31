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
        postMessageToList(message, "Host");
    }
}

void MidiMonitorAudioProcessorEditor::postMessageToList (const juce::MidiMessage& message, const juce::String& source)
{
    (new IncomingMessageCallback (this, message, source))->post();
}

void MidiMonitorAudioProcessorEditor::addMessageToList (const juce::MidiMessage& message, const juce::String& source)
{
    auto time = message.getTimeStamp() - startTime;

    auto hours   = ((int) (time / 3600.0)) % 24;
    auto minutes = ((int) (time / 60.0)) % 60;
    auto seconds = ((int) time) % 60;
    auto millis  = ((int) (time * 1000.0)) % 1000;

    auto timecode = juce::String::formatted ("%02d:%02d:%02d.%03d",
                                              hours,
                                              minutes,
                                              seconds,
                                              millis);

    auto messageDescription = getMidiMessageDescription (message);

    if (mainPanel.messageTypeSelected(messageDescription)) {
        juce::String midiMessageString (messageDescription.description);
        mainPanel.logMessage (midiMessageString);
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
    else if (m.isProgramChange())
    {
        messageDescription = { "programChange", "Program change " + juce::String (m.getProgramChangeNumber()) };
    }
    else if (m.isAllNotesOff())
    {
        messageDescription = { "allNotesOn", "All notes off" };
    }
    else if (m.isAllSoundOff())
    {
        messageDescription = { "allNotesOff",  "All sound off" };
    }
    else if (m.isMetaEvent()) {
        messageDescription = { "metaEvent", "Meta event" };
    }
    else if (m.isController())
    {
        juce::String name (juce::MidiMessage::getControllerName (m.getControllerNumber()));

        if (name.isEmpty())
            name = "[" + juce::String (m.getControllerNumber()) + "]";

        messageDescription = { "controller", "Controller " + name + ": " + juce::String (m.getControllerValue()) };
    }
    else
    {
        messageDescription = { "unknown", juce::String::toHexString (m.getRawData(), m.getRawDataSize()) };
    }

    return messageDescription;
}