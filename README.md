CastleTour
==========

This repo is a combination of a few Irrlicht tutorials.

### Compiling
So far I'm using CMake (and only on Debian GNU/Linux). First, compile Irrlicht, move the include and library files to the [include directory](/include) and the [library directory](/libs) (make sure they are named ```libIrrlicht.so``` if you're running Linux and ```libIrrlicht.dll``` if you're running Windows). Then run the following commands from the root directory of the project:
```
$ cmake .
$ make
```
The binary should be in the [binary directory](/bin).

### Contributing
Feel free to add. This is something I'm using to learn Irrlicht, and it would help if I had a better [CMakeLists](/CMakeLists.txt) file that could compile on multiple platforms.

### License
Since this really isn't my code but Irrlicht code I placed it under the [Unlicense](/LICENSE), because kind of like a tutorial.
