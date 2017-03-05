Pandemonium
========================

Pandemonium is an action platformer game made for a 72-hour game jam in IIIT Jabalpur.


Team members
-------------------------


* Amish Naidu
* Anurag Bisht
* Ayaskant Panigrahi
* Shivam Garg


Download
-----------------------

32-bit Windows executable: https://www.dropbox.com/s/xvroaat97ehmiqa/Pandemonium.zip?dl=0 

For Linux/macOS, see Compiling

Compiling
----------------------

Install SFML 2.0+ and a C++11 compliant compiler, then run CMake on this directory to get appropriate build files.

On Ubuntu/Debian-based distros (assuming you have a compiler installed), e.g.

```sh
$ sudo apt install libsfml-dev cmake
```

Then, download and extract the [source](https://github.com/amhndu/Pandemonium/archive/master.zip) if you haven't already followed by:

```
$ cd Pandemonium
$ mkdir build/ && cd build/
$ cmake ..
$ make -j2
```

This will create an executable 'gamejam' in the build directory.

Similar steps for other distributions/macOS, while Windows' users will find the cmake gui useful which generates Visual C++ projects as well as MinGW makefiles.


Contact
--------------------------
amhndu --at-- gmail


