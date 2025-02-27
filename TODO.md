- [X] Solve issue: \
    /home/sebastian/Developer/Software/JUCE/juce_cmake_vscode_tutorial/libs/juce/modules/juce_gui_extra/juce_gui_extra.cpp:127:11: schwerwiegender Fehler: gtk/gtk.h: Datei oder Verzeichnis nicht gefunden
    Solved by adding the following to CMakeLists.txt (plugin):

        target_compile_definitions(${PROJECT_NAME}
            PUBLIC
                JUCE_WEB_BROWSER=0
                JUCE_USE_CURL=0
                JUCE_VST3_CAN_REPLACE_VST2=0
        )