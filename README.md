# About

Utf8-string is a string manipulation C library for UTF8 encoded data.

It is meant to be lightweight, fast, and to the point.

<i>To the point?</i>

Yes. It does UTF-8 encoding and decoding. No more, no less.

It is unit tested, so most commits are expected to be stable.

It is written using the C89 standard, so is expected to be portable across compilers.

# Building

CMake is used as the build system.

To build any CMake project, do this:

```
mkdir build && cd build
cmake ..
cmake --build . --target all
```

And to install:

```
cmake --build . --target install
```

But if you're using Make, CMake generates a Makefile containing all the standard targets:

```
make clean
make all
make test
make install
```

