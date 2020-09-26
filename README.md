## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)


## About The Project
CodeRepair is the a tool for the reapir of simple integer based C program written in addition to the dissertation submitted to the University of Bristol in accordance with the requirements of the degree of MSc in the Faculty of Engineering.


### Built With
* [C++](https://isocpp.org/)
* [Boost](https://www.boost.org/)

## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

The project requires C++11 to build,
including compiler and standard and boost library support.

The following minimum versions are required to build the library:

* GCC 4.8
* Clang 3.4
* Visual Studio 14 2015

Boost library can be installed using following the instructions here: [Boost library Installation](https://www.boost.org/doc/libs/1_66_0/more/getting_started/unix-variants.html)

<!-- USAGE EXAMPLES -->
## Usage

In order to build the project:

```sh
make -f Makefile
```

To run the program where path is the exact file path of the buggy program (e.g: benchmarks/test1.c):

```sh
./repairTool <path>
```

New benchamrks or IO examples can be placed into the benchmarks directory or IO directory respectively or any other path that is valid.
