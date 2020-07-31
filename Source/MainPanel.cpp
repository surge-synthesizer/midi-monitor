/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "version.h"
//[/Headers]

#include "MainPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainPanel::MainPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    messagesGroup.reset (new juce::GroupComponent ("Messages Group",
                                                   TRANS("Messages")));
    addAndMakeVisible (messagesGroup.get());
    messagesGroup->setColour (juce::GroupComponent::textColourId, juce::Colour (0xffdddddd));

    messagesGroup->setBounds (170, 40, 300, 345);

    midiMessagesBox.reset (new juce::TextEditor ("Messages"));
    addAndMakeVisible (midiMessagesBox.get());
    midiMessagesBox->setMultiLine (true);
    midiMessagesBox->setReturnKeyStartsNewLine (true);
    midiMessagesBox->setReadOnly (true);
    midiMessagesBox->setScrollbarsShown (true);
    midiMessagesBox->setCaretVisible (false);
    midiMessagesBox->setPopupMenuEnabled (true);
    midiMessagesBox->setColour (juce::TextEditor::textColourId, juce::Colours::white);
    midiMessagesBox->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0xff001122));
    midiMessagesBox->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x00000000));
    midiMessagesBox->setText (juce::String());

    midiMessagesBox->setBounds (182, 60, 275, 315);

    filterGroup.reset (new juce::GroupComponent ("Filters",
                                                 TRANS("Filters")));
    addAndMakeVisible (filterGroup.get());
    filterGroup->setColour (juce::GroupComponent::textColourId, juce::Colour (0xffdddddd));

    filterGroup->setBounds (10, 40, 150, 345);

    midiMonitorLabel.reset (new juce::Label ("Midi Monitor",
                                             TRANS("MIDI Monitor")));
    addAndMakeVisible (midiMonitorLabel.get());
    midiMonitorLabel->setFont (juce::Font ("Lato", 30.00f, juce::Font::plain).withTypefaceStyle ("Regular").withExtraKerningFactor (0.018f));
    midiMonitorLabel->setJustificationType (juce::Justification::centred);
    midiMonitorLabel->setEditable (false, false, false);
    midiMonitorLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    midiMonitorLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    midiMonitorLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    midiMonitorLabel->setBounds (10, 10, 460, 25);

    noteButton.reset (new juce::TextButton ("Note Button"));
    addAndMakeVisible (noteButton.get());
    noteButton->setButtonText (TRANS("Note"));
    noteButton->addListener (this);
    noteButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff001122));
    noteButton->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff072f4f));
    noteButton->setColour (juce::TextButton::textColourOffId, juce::Colours::white);

    noteButton->setBounds (20, 60, 130, 25);

    pitchBendButton.reset (new juce::TextButton ("Pitch Bend Button"));
    addAndMakeVisible (pitchBendButton.get());
    pitchBendButton->setButtonText (TRANS("Pitch Bend"));
    pitchBendButton->addListener (this);
    pitchBendButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff001122));
    pitchBendButton->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff072f4f));
    pitchBendButton->setColour (juce::TextButton::textColourOffId, juce::Colours::white);

    pitchBendButton->setBounds (20, 95, 130, 25);

    channelPressureButton.reset (new juce::TextButton ("Channel Pressure Button"));
    addAndMakeVisible (channelPressureButton.get());
    channelPressureButton->setButtonText (TRANS("Channel Pressure"));
    channelPressureButton->addListener (this);
    channelPressureButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff001122));
    channelPressureButton->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff072f4f));
    channelPressureButton->setColour (juce::TextButton::textColourOffId, juce::Colours::white);

    channelPressureButton->setBounds (20, 130, 130, 25);

    aftertouchButton.reset (new juce::TextButton ("Aftertouch Button"));
    addAndMakeVisible (aftertouchButton.get());
    aftertouchButton->setButtonText (TRANS("Aftertouch"));
    aftertouchButton->addListener (this);
    aftertouchButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff001122));
    aftertouchButton->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff072f4f));
    aftertouchButton->setColour (juce::TextButton::textColourOffId, juce::Colours::white);

    aftertouchButton->setBounds (20, 165, 130, 25);

    controllerButton.reset (new juce::TextButton ("CC Button"));
    addAndMakeVisible (controllerButton.get());
    controllerButton->setButtonText (TRANS("CC"));
    controllerButton->addListener (this);
    controllerButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff001122));
    controllerButton->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff072f4f));
    controllerButton->setColour (juce::TextButton::textColourOffId, juce::Colours::white);

    controllerButton->setBounds (20, 200, 130, 25);

    programChangeButton.reset (new juce::TextButton ("Program Change Button"));
    addAndMakeVisible (programChangeButton.get());
    programChangeButton->setButtonText (TRANS("Program Change"));
    programChangeButton->addListener (this);
    programChangeButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff001122));
    programChangeButton->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff072f4f));
    programChangeButton->setColour (juce::TextButton::textColourOffId, juce::Colours::white);

    programChangeButton->setBounds (20, 235, 130, 25);

    allNotesOffButton.reset (new juce::TextButton ("All Notes Off Button"));
    addAndMakeVisible (allNotesOffButton.get());
    allNotesOffButton->setButtonText (TRANS("All Notes Off"));
    allNotesOffButton->addListener (this);
    allNotesOffButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff001122));
    allNotesOffButton->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff072f4f));
    allNotesOffButton->setColour (juce::TextButton::textColourOffId, juce::Colours::white);

    allNotesOffButton->setBounds (20, 270, 130, 25);


    //[UserPreSize]
    noteButton->setClickingTogglesState(true);
    pitchBendButton->setClickingTogglesState(true);
    channelPressureButton->setClickingTogglesState(true);
    aftertouchButton->setClickingTogglesState(true);
    controllerButton->setClickingTogglesState(true);
    programChangeButton->setClickingTogglesState(true);
    allNotesOffButton->setClickingTogglesState(true);

    noteButton->setToggleState(true, juce::NotificationType::dontSendNotification);
    //[/UserPreSize]

    setSize (480, 400);


    //[Constructor] You can add your own custom stuff here..
    std::string vl =  Build::git_commit_hash + " / " + Build::build_date;
    versionLabel.reset (new juce::Label ("Version",
                                         TRANS(vl.c_str())));
    addAndMakeVisible (versionLabel.get());
    versionLabel->setFont (juce::Font ("Lato", 10.00f, juce::Font::plain).withTypefaceStyle ("Regular").withExtraKerningFactor (0.018f));
    versionLabel->setJustificationType (juce::Justification::centred);
    versionLabel->setEditable (false, false, false);
    versionLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    versionLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    versionLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    versionLabel->setBounds (10, 385, 460, 12);

    //[/Constructor]
}

MainPanel::~MainPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    messagesGroup = nullptr;
    midiMessagesBox = nullptr;
    filterGroup = nullptr;
    midiMonitorLabel = nullptr;
    noteButton = nullptr;
    pitchBendButton = nullptr;
    channelPressureButton = nullptr;
    aftertouchButton = nullptr;
    controllerButton = nullptr;
    programChangeButton = nullptr;
    allNotesOffButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainPanel::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff001122));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    // auto area = getLocalBounds();
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    // midiMessagesBox.setBounds (area.reduced (8));
    //[/UserResized]
}

void MainPanel::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == noteButton.get())
    {
        //[UserButtonCode_noteButton] -- add your button handler code here..
        selectedMessages["note"] = !( selectedMessages.find("note")->second );
        //[/UserButtonCode_noteButton]
    }
    else if (buttonThatWasClicked == pitchBendButton.get())
    {
        //[UserButtonCode_pitchBendButton] -- add your button handler code here..
        selectedMessages["pitchBend"] = !( selectedMessages.find("pitchBend")->second );
        //[/UserButtonCode_pitchBendButton]
    }
    else if (buttonThatWasClicked == channelPressureButton.get())
    {
        //[UserButtonCode_channelPressureButton] -- add your button handler code here..
        selectedMessages["channelPressure"] = !( selectedMessages.find("channelPressure")->second );
        //[/UserButtonCode_channelPressureButton]
    }
    else if (buttonThatWasClicked == aftertouchButton.get())
    {
        //[UserButtonCode_aftertouchButton] -- add your button handler code here..
        //[/UserButtonCode_aftertouchButton]
    }
    else if (buttonThatWasClicked == controllerButton.get())
    {
        //[UserButtonCode_controllerButton] -- add your button handler code here..
        selectedMessages["controller"] = !( selectedMessages.find("controller")->second );
        //[/UserButtonCode_controllerButton]
    }
    else if (buttonThatWasClicked == programChangeButton.get())
    {
        //[UserButtonCode_programChangeButton] -- add your button handler code here..
        selectedMessages["programChange"] = !( selectedMessages.find("programChange")->second );
        //[/UserButtonCode_programChangeButton]
    }
    else if (buttonThatWasClicked == allNotesOffButton.get())
    {
        //[UserButtonCode_allNotesOffButton] -- add your button handler code here..
        selectedMessages["allNotesOff"] = !( selectedMessages.find("allNotesOff")->second );
        //[/UserButtonCode_allNotesOffButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainPanel::logMessage (const juce::String& m)
{
    midiMessagesBox->moveCaretToEnd();
    midiMessagesBox->insertTextAtCaret (m + juce::newLine);
}


bool MainPanel::messageTypeSelected (const MidiMessageDescription messageDescription) {
    return selectedMessages.find(messageDescription.type)->second;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainPanel" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="480" initialHeight="400">
  <BACKGROUND backgroundColour="ff001122"/>
  <GROUPCOMPONENT name="Messages Group" id="582abaaf115d3790" memberName="messagesGroup"
                  virtualName="" explicitFocusOrder="0" pos="170 40 300 345" textcol="ffdddddd"
                  title="Messages"/>
  <TEXTEDITOR name="Messages" id="bdc400430d70b1c1" memberName="midiMessagesBox"
              virtualName="" explicitFocusOrder="0" pos="182 60 275 315" textcol="ffffffff"
              bkgcol="ff001122" outlinecol="0" initialText="" multiline="1"
              retKeyStartsLine="1" readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <GROUPCOMPONENT name="Filters" id="4514dcc6ef929e34" memberName="filterGroup"
                  virtualName="" explicitFocusOrder="0" pos="10 40 150 345" textcol="ffdddddd"
                  title="Filters"/>
  <LABEL name="Midi Monitor" id="78f962969b487daf" memberName="midiMonitorLabel"
         virtualName="" explicitFocusOrder="0" pos="10 10 460 25" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="MIDI Monitor" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Lato"
         fontsize="30.0" kerning="0.018" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="Note Button" id="c7894df8d392efd7" memberName="noteButton"
              virtualName="" explicitFocusOrder="0" pos="20 60 130 25" bgColOff="ff001122"
              bgColOn="ff072f4f" textCol="ffffffff" buttonText="Note" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Pitch Bend Button" id="ff1dc9d942ab5b19" memberName="pitchBendButton"
              virtualName="" explicitFocusOrder="0" pos="20 95 130 25" bgColOff="ff001122"
              bgColOn="ff072f4f" textCol="ffffffff" buttonText="Pitch Bend"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Channel Pressure Button" id="c1ee44c5a8af9727" memberName="channelPressureButton"
              virtualName="" explicitFocusOrder="0" pos="20 130 130 25" bgColOff="ff001122"
              bgColOn="ff072f4f" textCol="ffffffff" buttonText="Channel Pressure"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Aftertouch Button" id="5936a87208eb6749" memberName="aftertouchButton"
              virtualName="" explicitFocusOrder="0" pos="20 165 130 25" bgColOff="ff001122"
              bgColOn="ff072f4f" textCol="ffffffff" buttonText="Aftertouch"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="CC Button" id="6ba6a7bd7b0ff30" memberName="controllerButton"
              virtualName="" explicitFocusOrder="0" pos="20 200 130 25" bgColOff="ff001122"
              bgColOn="ff072f4f" textCol="ffffffff" buttonText="CC" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Program Change Button" id="b439ad557214f7af" memberName="programChangeButton"
              virtualName="" explicitFocusOrder="0" pos="20 235 130 25" bgColOff="ff001122"
              bgColOn="ff072f4f" textCol="ffffffff" buttonText="Program Change"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="All Notes Off Button" id="4e2e00f3057e6615" memberName="allNotesOffButton"
              virtualName="" explicitFocusOrder="0" pos="20 270 130 25" bgColOff="ff001122"
              bgColOn="ff072f4f" textCol="ffffffff" buttonText="All Notes Off"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

