# how to set this up

## set up cpm

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