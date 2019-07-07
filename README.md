# MathNodes

MathNodes is a simple C++ math expression parser. It's node structure is designed for quick, repetetive calculations of floating point numbers.

Please refer to [MathNodesTest.cpp](test/MathNodesTest.cpp) as it's designed to be the simplest example on how to add external variables, and functions. It also contains an infinite loop, with an exit funciton added to the MathNodeBuilder object.

If, after cloning, you run ```make``` in the main directory of the repo, it will build a small collection of simple tools. *parse* is a trivial program parse a series of expressions. *iparse* is a slighly more robust inline parser, as it has built in help functions and can accept command line arguments.
