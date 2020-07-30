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
//[/Headers]

#include "MainPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainPanel::MainPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    juce__groupComponent.reset (new juce::GroupComponent ("new group",
                                                          TRANS("Messages")));
    addAndMakeVisible (juce__groupComponent.get());
    juce__groupComponent->setColour (juce::GroupComponent::textColourId, juce::Colour (0xffdddddd));

    juce__groupComponent->setBounds (140, 40, 250, 345);

    midiMessagesBox.reset (new juce::TextEditor ("Messages"));
    addAndMakeVisible (midiMessagesBox.get());
    midiMessagesBox->setMultiLine (true);
    midiMessagesBox->setReturnKeyStartsNewLine (true);
    midiMessagesBox->setReadOnly (true);
    midiMessagesBox->setScrollbarsShown (true);
    midiMessagesBox->setCaretVisible (false);
    midiMessagesBox->setPopupMenuEnabled (true);
    midiMessagesBox->setColour (juce::TextEditor::textColourId, juce::Colours::white);
    midiMessagesBox->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0xff272c40));
    midiMessagesBox->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x00000000));
    midiMessagesBox->setText (juce::String());

    midiMessagesBox->setBounds (152, 60, 225, 315);

    filterGroup.reset (new juce::GroupComponent ("Filters",
                                                 TRANS("Filters")));
    addAndMakeVisible (filterGroup.get());
    filterGroup->setColour (juce::GroupComponent::textColourId, juce::Colour (0xffdddddd));

    filterGroup->setBounds (10, 40, 120, 345);

    midiMonitorLabel.reset (new juce::Label ("Midi Monitor",
                                             TRANS("MIDI Monitor")));
    addAndMakeVisible (midiMonitorLabel.get());
    midiMonitorLabel->setFont (juce::Font (20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    midiMonitorLabel->setJustificationType (juce::Justification::centred);
    midiMonitorLabel->setEditable (false, false, false);
    midiMonitorLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    midiMonitorLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    midiMonitorLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    midiMonitorLabel->setBounds (10, 10, 380, 25);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainPanel::~MainPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    juce__groupComponent = nullptr;
    midiMessagesBox = nullptr;
    filterGroup = nullptr;
    midiMonitorLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainPanel::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff272c40));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    auto area = getLocalBounds();
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    // midiMessagesBox.setBounds (area.reduced (8));
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainPanel::logMessage (const juce::String& m)
{
    midiMessagesBox->moveCaretToEnd();
    midiMessagesBox->insertTextAtCaret (m + juce::newLine);
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
                 fixedSize="0" initialWidth="400" initialHeight="400">
  <BACKGROUND backgroundColour="ff272c40"/>
  <GROUPCOMPONENT name="new group" id="582abaaf115d3790" memberName="juce__groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="140 40 250 345" textcol="ffdddddd"
                  title="Messages"/>
  <TEXTEDITOR name="Messages" id="bdc400430d70b1c1" memberName="midiMessagesBox"
              virtualName="" explicitFocusOrder="0" pos="152 60 225 315" textcol="ffffffff"
              bkgcol="ff272c40" outlinecol="0" initialText="" multiline="1"
              retKeyStartsLine="1" readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <GROUPCOMPONENT name="Filters" id="4514dcc6ef929e34" memberName="filterGroup"
                  virtualName="" explicitFocusOrder="0" pos="10 40 120 345" textcol="ffdddddd"
                  title="Filters"/>
  <LABEL name="Midi Monitor" id="78f962969b487daf" memberName="midiMonitorLabel"
         virtualName="" explicitFocusOrder="0" pos="10 10 380 25" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="MIDI Monitor" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="20.0" kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

