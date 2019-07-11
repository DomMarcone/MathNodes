# MathNodes

MathNodes is a simple C++ math expression parser. It's node structure is designed for quick, repetetive calculations of floating point numbers.

Please refer to [MathNodesTest.cpp](test/MathNodesTest.cpp) as it's designed to be the simplest example on how to add external variables, and functions. It also contains an infinite loop, with an exit funciton added to the MathNodeBuilder object.

To get started with the test toolkit, run
```bash
#clone the repo
git clone https://github.com/DomMarcone/MathNodes

#enter the repo and create a build directory
cd MathNodes
mkdir build

#and, finally, run cmake
cmake ..
```

 *parse* is a trivial program parse a series of expressions. *iparse* is a slighly more robust inline parser, as it has built in help functions and can accept command line arguments.

