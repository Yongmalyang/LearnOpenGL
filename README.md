# learnopengl.com code repository
Contains code samples for all tutorials of [http://learnopengl.com](http://learnopengl.com). 

The CMakeLists.txt is not yet finished for Linux/OS X; for more info see http://learnopengl.com/#!Code-repository

## Windows building
All relevant libraries are found in /libs and all DLLs found in /dlls (pre-)compiled for Windows. 
The CMake script knows where to find the libraries so just run CMake script and generate project of choice.
Note that you still have to manually copy the required .DLL files from the /dlls folder to your binary folder for the binaries to run.

## Linux building
First get the required packages:
Use root (sudo) and type `apt-get install libsoil-dev libglm-dev libassimp-dev libglew-dev libglfw-dev`