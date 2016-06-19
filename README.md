HDF5Wrapper
=============
This is a C++ wrapper for the HDF5 library which aims to provide a very simple interface for reading and writing contiguous blocks for data 
to HDF5 files. Using the standard C and C++ APIs for reading and writing to HDF5 files can be a complicated process. It requires one to create 
and setup DataSpace and HyperSlab objects aswell as setting myriad offset, stride and count parameters. This interface provides simple functions
for opening files, creating datasets and reading and writing blocks of data. It also supports buffering which allows one to use this interface 
easily from inside loops. 

Requirements
-------------
To use the wrapper requires:
* C++ compiler
* Recent HDF5 libraries 
* CMake 

Installation
-------------
Clone the repository, create a build folder and change to this folder.

`mkdir build; cd build`

Run cmake 

`cmake ../`

Compiler the library and examples

`make`

Install the library and header.

`sudo make install`

The header file gets installed to the `/usr/local/include` folder and the library file to the
`/usr/local/lib` folder.
