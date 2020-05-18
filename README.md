## Kl1p-test

A test/evaluation program for a portable c++ compressed sensing library: [kl1p-0.4.2](http://kl1p.sourceforge.net/home.html) 

## About

This is a Project for Obersiminar of [Chair Communication Networks TU-Dresden](https://cn.ifn.et.tu-dresden.de/)

In this evaluation program, the library kl1p is used for testing three common compressed sensing algorithms(OMP, CoSaMP, AMP). 

## Installation

### Required packages and libraries
* [cmake](https://cmake.org/): build static libraries of kl1p
* [armadillo](http://arma.sourceforge.net/): c++ linear algebra library used in kl1p
* compiler: g++ or clang++(default in this makefile)

### Steps for building

1. build the armadillo libraries, details see the README.txt of armadillo

2. build kl1p static libraries(.a files), details is in README.txt in ./kl1p_0.4.2

3. use make to build the program
    * put static libraries in the root directory of program(default in makefile)
    * edit makefile: choose compiler, edit libname(like -lKLab for x86 platforms)
    * use `make BUILD=Debug` for debug or `make` for release version

**Notice**: some codes is added or modified in the source code of kl1p, so i put ./kl1p_0.4.2 dir in the repository(for rebuilding static libs). So if you want
to use original library or the latest version, you should get library from its [homepage](http://kl1p.sourceforge.net/home.html)

## Contributors

* Zuo Xiang : xianglinks@gmail.com

## License

This program use the same license as the kl1p library: 
> This library is free software; You can redistribute it and/or modify it under the terms of the GNU Lesser General Public License (LGPL) as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
