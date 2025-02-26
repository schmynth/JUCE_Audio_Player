cmake_minimum_required(VERSION 3.22)

project(AudioPlugin VERSION 0.1.0)

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME schmynth_audio
    IS_SYNTH FALSE
    FORMATS VST3
    PRODUCT_NAME "PluginName"
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    PLUGIN_MANUFACTURER_CODE SCHMNTH # what you want
    PLUGIN_CODE AUPL # what you want
)