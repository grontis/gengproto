# CMake 

issues with cmake on windows solved by renaming cmake file https://stackoverflow.com/questions/71199549/cmake-in-vsc-doesnt-find-generator

# Dependencies
## Linux
```sudo apt-get install libsdl2-dev```

## Windows
had some issues with vcpkg installing SDL2 with a windows x64 MSVC version, which was incompatible with building this project with GCC.

Instead downloaded the SDL release zip
https://github.com/libsdl-org/SDL/releases
unzip
then run from a MSYS2 terminal
```./configure && make && make install ```
(as seen in INSTALL.txt)