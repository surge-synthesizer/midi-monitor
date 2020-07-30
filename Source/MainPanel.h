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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainPanel  : public juce::Component
{
public:
    //==============================================================================
    MainPanel ();
    ~MainPanel() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void logMessage (const juce::String& m);
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> juce__groupComponent;
    std::unique_ptr<juce::TextEditor> midiMessagesBox;
    std::unique_ptr<juce::GroupComponent> filterGroup;
    std::unique_ptr<juce::Label> midiMonitorLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

