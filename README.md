# TinyWeb
Tiny web is a *very* small WSGI inspired framework to build web applications in C++. Why should you use this project? You probably shouldn't as this is mostly just a toy project to get more familliar with C++. If you think it is awesome and you want to use it, go ahead. Contributions are also very welcome, just make a pull request and I will take a look, even feedback is more than welcome.

## Installation
Tiny web depends on Boost and is build using CMake. I recommend running
```
cd build
cmake ..
```
to build the project, but ultimately it's up to you. If you decide to go with this you can find the executable files `example` and `tests` in the `bin/` folder and `libtinyweb.a` in `lib/`. The first provides an example server, the second runs a nice array of tests and the latter is the library that you can include to start creating your web server.