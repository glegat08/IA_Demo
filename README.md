Hello,

To start the project, please follow those steps :

-> Clone the repository
-> In the folder, start Bootstrap.bat and wait for it to finish
-> Go into build folder, and launch the .sln file
-> Set "mainFile" as startup project
-> And go to Properties, Linker, Input and make sure you have those lines (for Debug Config) or it won't work :
    "sfml-graphics-d.lib
     sfml-window-d.lib
     sfml-system-d.lib
     sfml-audio-d.lib"
-> Enjoy !