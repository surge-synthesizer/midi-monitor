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
    setSize (600, 400);

    addAndMakeVisible (&midiMessagesBox);
    midiMessagesBox.setMultiLine (true);
    midiMessagesBox.setReturnKeyStartsNewLine (true);
    midiMessagesBox.setReadOnly (true);
    midiMessagesBox.setScrollbarsShown (true);
    midiMessagesBox.setCaretVisible (false);
    midiMessagesBox.setPopupMenuEnabled (true);
    midiMessagesBox.setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x32ffffff));
    midiMessagesBox.setColour (juce::TextEditor::outlineColourId, juce::Colour (0x1c000000));
    midiMessagesBox.setColour (juce::TextEditor::shadowColourId, juce::Colour (0x16000000));

    // Start polling processor for Midi Messages
    startTimer(10);
}

MidiMonitorAudioProcessorEditor::~MidiMonitorAudioProcessorEditor()
{
}

//==============================================================================
void MidiMonitorAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void MidiMonitorAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();

    midiMessagesBox.setBounds (area.reduced (8));
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

    if (shownMessages.find(messageDescription.type)->second) {
        juce::String midiMessageString (messageDescription.description);
        logMessage (midiMessageString);
    }
}


void MidiMonitorAudioProcessorEditor::logMessage (const juce::String& m)
{
    midiMessagesBox.moveCaretToEnd();
    midiMessagesBox.insertTextAtCaret (m + juce::newLine);
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
       messageDescription = {"pitchWheel", "Pitch wheel " + juce::String (m.getPitchWheelValue()) };
    }
    else if (m.isChannelPressure())
    {
        messageDescription = { "channelPressure", "Channel pressure " + juce::String (m.getChannelPressureValue()) };
    }
    else if (m.isAftertouch())
    {
      messageDescription = { "aftertouch", "After touch " + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) +  ": " + juce::String (m.getAfterTouchValue()) };
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

// juce::String MidiMonitorAudioProcessorEditor::getMidiMessageDescription (const juce::MidiMessage& m)
// {
//     if (m.isNoteOn())           return "Note on "          + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
//     if (m.isNoteOff())          return "Note off "         + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
//     if (m.isProgramChange())    return "Program change "   + juce::String (m.getProgramChangeNumber());
//     if (m.isPitchWheel())       return "Pitch wheel "      + juce::String (m.getPitchWheelValue());
//     if (m.isAftertouch())       return "After touch "      + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) +  ": " + juce::String (m.getAfterTouchValue());
//     if (m.isChannelPressure())  return "Channel pressure " + juce::String (m.getChannelPressureValue());
//     if (m.isAllNotesOff())      return "All notes off";
//     if (m.isAllSoundOff())      return "All sound off";
//     if (m.isMetaEvent())        return "Meta event";

//     if (m.isController())
//     {
//         juce::String name (juce::MidiMessage::getControllerName (m.getControllerNumber()));

//         if (name.isEmpty())
//             name = "[" + juce::String (m.getControllerNumber()) + "]";

//         return "Controller " + name + ": " + juce::String (m.getControllerValue());
//     }

//     return juce::String::toHexString (m.getRawData(), m.getRawDataSize());
// }