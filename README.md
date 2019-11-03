## About

This project was an first attempt to design a entity-component based
graphics engine. I want to create a well designed engine with the
purpose of being used for creating 64k intros. Writing a well desined
engine for that purpose is hard and I instead wanted to start by
writing a first iteration using modern-ish C++. One problem is that
the engine uses quite a lot of virtual classes which I will have to
design away to make it sutable for such a purpose.

## Building on Linux
### Dependencies
    * GLFW3
    * GLEW
    * GLM
    
### Building
    * mkdir build
    * cd build
    * cmake ..
    * make

## Building on Windows

   It should be possible to just import the project as a cmake project
   in visual studio.
