# Graph's Operators Overloading Project

- In this project we demonstrate functions overloading and more specificly operators overloading in C++. 
- The implementations of the operators are in the `Graph.cpp` class.

### Addition, incremention, and Unary+ operators
- `+`: This operator is used to add two graphs together. It takes two graphs as input and returns a new graph. If the input graphs are not of the same size, an exception is thrown. Usage example: `g1 = g2 + g3`.

- `+=`: This operator is used to assign an addition of a graph to the current graph. It takes a graph as input and modifies the current graph. If the input graph is not of the same size as the current graph, an exception is thrown. Usage example: `g1 += g2`.

- `++`: Ive overloaded the prefix and postfix types of this operator, it increments the current graph by 1 as long as the cell in the matrix is not 0 (meaning no edge). Usage example: `g++` or `++g`.

- `+Graph`: this operator doesnt have any effect really on the graph, returns the graph itself. Usage example: `+g`.

### Subtraction ,decrement and Unary- Operators

- `-`: This operator is used to subtract one graph from another. It takes two graphs as input and returns a new graph. If the input graphs are not of the same size, an exception is thrown. Usage example: `g1 = g2 - g3`

- `-=`: This operator is used to subtract a graph from the current graph. It takes a graph as input and assigns the new value to the current graph. If the input graph is not of the same size as the current graph, an exception is thrown. Usage example: `g1 -= g2`.

- `-Graph`: 

### Multiplication Operators

- `*`: This operator is used to multiply two graphs together. It takes two graphs as input and returns a new graph. The resulting graph's adjacency matrix is the matrix product of the adjacency matrices of the input graphs. If the input graphs are not of compatible sizes for matrix multiplication, an exception is thrown.

- `*=`: This operator is used to multiply the current graph by another graph. It takes a graph as input and modifies the current graph. The adjacency matrix of the current graph is updated to be the matrix product of its own adjacency matrix and the adjacency matrix of the input graph. If the input graph is not of a compatible size for matrix multiplication with the current graph, an exception is thrown.

## Changes made from exe1

### In Graph.cpp , Graph.hpp.
- `getNumVertices()`,`getAdjacencyMatrix()`,`getIsDirected()`,`getWeightsType()`: made const methods.
- `loadGraph()`: if the matrix is assymetric and the graph was set to Undirected, it will be set as directed from now and there wont be exception throwing.
- `getNumEdges()`: added method to help me in the comparison operators.

### In Algorithms.cpp , Algorithms.hpp.
-


## How to Run

The project includes a Makefile for easy compilation and running of the code. Here are some commands you can use:

- `make run`: Compiles the code and runs the demo.
- `make demo`: Compiles the code for the demo.
- `make test`: Compiles the code for the tests.
- `make tidy`: Runs clang-tidy on the source files to check for code quality issues.
- `make valgrind`: Runs valgrind on the demo and test executables to check for memory leaks.
- `make clean`: Removes all compiled files.

## Testing




