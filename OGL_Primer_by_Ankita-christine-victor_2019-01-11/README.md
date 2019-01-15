# OpenGL Primer
This is a starter OpenGL shader application written in C++. It uses GLFW for window creation.

## Requirements
- OpenGL 3.3 and above
- GLEW
- GLFW
- GLM

## Installation
For Ubuntu 
```
./requirements.sh
```
to install necessary libraries

For Mac OS X visit https://www.youtube.com/watch?v=Tz0dq2krCW8&t=48s for OpenGL, GLFW and GLEW, and http://macappstore.org/glm/ for GLM.

Ensure your OpenGL Core Profile is at least 3.3 by running 
```
glxinfo | grep 'version'
```

## Program Usage
To compile and execute code with OpenGL 3.3 run
```
make run3
```

To compile and execute code witj OpenGL 1.1 run
```
make run1
```

Use the arrow keys to move up, down, left and right. Use + to increase size and - to decrease.
