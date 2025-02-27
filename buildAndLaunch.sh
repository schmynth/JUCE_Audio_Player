#!/bin/bash

# build project
cmake -S . -B build
cmake --build build


# build juce Audio Plugin Host:
cd libs/juce
cmake -B build
cmake -B build -DJUCE_BUILD_EXTRAS=ON
cmake --build build --target AudioPluginHost

# launch Audio Plugin Host:
./build/extras/AudioPluginHost/AudioPluginHost_artefacts/AudioPluginHost
