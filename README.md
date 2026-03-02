# Pop Fizz

## Introduction

Pop-fizz is a basic game engine written in C++.
We use GLFW and OpenGL for rendering.


## Building:
Clone the repository
```bash
$ git clone git@github.com:maeday-modus/pop-fizz.git pop-fizz
$ cd pop-fizz
```

#### Dependencies:
*   `clang++`
*   `glfw`
    > NOTE: if `glfw` isn't installed under `/usr/lib` and `/usr/include`, you can change where clang searches for it at the top of the `build` script file. This applies to all external library includes.

#### BUILD
From the project root directory, run the `build` script:
```bash
$ ./build
```
OR
```bash
$ bash ./build
```

The build script will try and detect whether changes have been made since the last build. 

Optionally, you can pass the `-f` parameter to skip this hash check and rebuild anyway:
```bash
$ ./build -f
```
