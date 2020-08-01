# Midi Monitor

MIDI Monitor is a small utility plugin for monitoring MIDI. It logs a limited set of MIDI messages that are useful when debugging controller output.

MIDI messages can be filtered by type. For example, note events and pitch bend could be shown, but channel pressure and aftertouch left out.

This plugin is currently in early alpha. Our plan is to add more features and polish and learn JUCE along the way!

We distribute a built version of the codebase for mac, windows, and linux [here](https://github.com/surge-synthesizer/midi-monitor/releases/tag/Nightly).

If you find a bug or want to make a change, please open a github issue or join our slack.

## How to Build 

The build uses `cmake` and is the same on all platforms.

```
git clone https://github.com/surge-synthesizer/midi-monitor  # or your fork obviously
cd midi-monitor 
git submodule update --init --recursive
cmake -Bbuild     # macos users may want cmake -Bbuild -GXcode if they want an xcode file
cmake --build build --config Release 
```

That's it!

Of course cmake will create IDE assets in a normal way if you want them. They will all appear in the build directory.
