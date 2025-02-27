# how to set this up

This is a combination of the following sources of info:

1. [Wolf Sound Tutorial](https://www.youtube.com/watch?v=Uq7Hwt18s3s&t=1145s&ab_channel=WolfSound)
    for basic toolchain Setup and google testing (follow this one first)
2. [trirpi](https://trirpi.github.io/posts/developing-audio-plugins-with-juce-and-visual-studio-code/)
    for setting up Audio Plugin Host 
3. [melatonin dev blog](https://melatonin.dev/blog/how-to-use-cmake-with-juce/)
    general info on cmake


## set up cpm

CPM is kind of the "*C*Make *P*ackage *M*anager"

Run the following in project root dir:

    mkdir -p cmake
    wget -O cmake/CPM.cmake https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake

Replace ${DOWNLOAD_LOCATION} with ${LIB_DIR}, otherwise you get "unknown cmake command CPMAddPackage" error.

## install JUCE

add the following to top level CMakeLists.txt:

    CPMAddPackage(
        NAME JUCE
        GITHUB_REPOSITORY juce-framework/JUCE
        GIT_TAG 8.0.6
        VERSION 8.0.6    
        SOURCE_DIR ${LIB_DIR}/juce
    )

# configure

Configuration in CMake means that cmake prepares the whole build infrastructure so that the whole project can be compiled using one single command.
The Configuration is invoked by the following command in the project root directory:

    cmake -S . -B build

where "build" is the directory in which CMake will put all the necessary config files for building the project.

# link and compile

To compile the project, invoke:

    cmake --build build

where "--build" is an option for cmake and "build" is the directory, where CMake will put the object files and binaries.

# link, compile and launch with script

You can simply launch the script ```buildAndLaunch.sh``` in order to link and compile the Plugin and launch the plugin host. If you want to recreate all the build files you can launch it with the option like this:

    ./buildAndLaunch.sh --remove-build


# add modules (f.e. juce_dsp)

To add juce modules, do not use `juce_add_module()`. Instead, add the module (juce_dsp) to `target_link_libraries()` in `CMakeLists.txt` (plugin) like so:

    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            juce::juce_audio_utils
            juce::juce_dsp
        PUBLIC
            juce::juce_recommended_config_flags
            juce::juce_recommended_lto_flags
            juce::juce_recommended_warning_flags
    )