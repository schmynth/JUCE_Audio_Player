#pragma once

#include "PluginProcessor.h"
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

//==============================================================================
class AudioPlayerPluginProcessorEditor final : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    explicit AudioPlayerPluginProcessorEditor (AudioPlayerPluginProcessor&);
    ~AudioPlayerPluginProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:

    juce::AudioThumbnailCache thumbnailCache { 5 };
    juce::AudioThumbnail thumbnail { 512, processorRef.formatManager, thumbnailCache};
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    std::unique_ptr<juce::FileChooser> chooser;
    juce::AudioTransportSource transportSource;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPlayerPluginProcessor& processorRef;
    juce::TextButton openButton { "open" };
    juce::TextButton playButton { "play" };
    juce::TextButton stopButton { "stop" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayerPluginProcessorEditor)
};
