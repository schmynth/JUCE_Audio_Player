#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
AudioPlayerPluginProcessorEditor::AudioPlayerPluginProcessorEditor(AudioPlayerPluginProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p) {
    addAndMakeVisible(openButton);
    openButton.setButtonText("Open...");
    openButton.onClick = [&] {
        juce::File initialDir = juce::File::getSpecialLocation(juce::File::userHomeDirectory);
        chooser = std::make_unique<juce::FileChooser>("Select an audio file...", initialDir, "*.wav;*.mp3");
        chooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
                             [this](const juce::FileChooser &fc) {
                                 juce::File file = fc.getResult();
                                 if (file.existsAsFile()) {
                                     processorRef.loadFile(file);
                                     thumbnail.clear();
                                     thumbnail.setSource(new juce::FileInputSource(file));
                                 }
                             });
    };
    addAndMakeVisible(playButton);
    playButton.onClick = [&]() { processorRef.start(); };

    addAndMakeVisible(stopButton);
    stopButton.onClick = [&]() { processorRef.stop(); };

    formatManager.registerBasicFormats();
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    processorRef.onFileLoaded = [this](const juce::File &file) {
        // std::cout << "trying to set thumbnail.." << std::endl;
        thumbnail.setSource(new juce::FileInputSource(file));
    };

    if (processorRef.fileWasRestoredFromState) {
        juce::MessageManager::callAsync([this]() {
            if (processorRef.lastLoadedFile.existsAsFile() && processorRef.onFileLoaded)
                processorRef.onFileLoaded(processorRef.lastLoadedFile);
        });
    }
    setSize(400, 300);
    startTimerHz(30);
}

AudioPlayerPluginProcessorEditor::~AudioPlayerPluginProcessorEditor() {}

//==============================================================================
void AudioPlayerPluginProcessorEditor::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    auto area = getLocalBounds().reduced(10).withTrimmedTop(40).withHeight(100);

    g.setColour(juce::Colours::darkgrey);
    g.fillRect(area);

    if (thumbnail.getTotalLength() > 0.0) {
        g.setColour(juce::Colours::lightblue);
        thumbnail.drawChannels(g, area, 0.0, thumbnail.getTotalLength(), 1.0f);

        // Draw playhead
        double curPos = processorRef.transportSource.getCurrentPosition();
        double total = thumbnail.getTotalLength();
        float relX = (float)(curPos / total) * area.getWidth();

        g.setColour(juce::Colours::red);
        g.drawLine((float)area.getX() + relX, (float)area.getY(), (float)area.getX() + relX, (float)area.getBottom(), 2.0f);
    } else {
        g.setColour(juce::Colours::white);
        g.drawText("No file loaded", area, juce::Justification::centred);
    }
}

void AudioPlayerPluginProcessorEditor::resized() {
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    openButton.setBounds(10, 10, getWidth() - 20, 30);
    playButton.setBounds(10, 150, getWidth() / 2 - 15, 30);
    stopButton.setBounds(getWidth() / 2 + 5, 150, getWidth() / 2 - 15, 30);
}

void AudioPlayerPluginProcessorEditor::timerCallback() {
    repaint(); // just repaint to update playhead
}
