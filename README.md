# Pop Fizz

## Introduction

Pop-fizz is a basic physics engine written in C++.
We use GLFW and OpenGL for rendering.


## Building:
Clone the repository
```bash
$ git clone https://github.com/MiniFalafel/pop-fizz.git pop-fizz
$ cd pop-fizz
```

#### Build dependencies:
*   `clang`
*   `glfw`

Run the `build` script:
```bash
$ ./build
```

The build script will create a hash of the file contents when run. 
This means that it'll only re-build if the files have changed.

Optionally, you can pass the `-f` parameter to skip this hash check and rebuild anyway:
```bash
$ ./build -f
```
