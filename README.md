# Graph's Operators Overloading Project

- In this project we demonstrate functions overloading and more specificly operators overloading in C++. 
- The implementations of the operators are in the `Graph.cpp` class.

### Addition, incremention, and Unary+ operators
- `+`: 
This operator is used to add two graphs together. It takes two graphs as input and returns a new graph. If the input graphs are not of the same size, an exception is thrown. Usage example: `g1 = g2 + g3`.

- `+=`: 
This operator is used to assign an addition of a graph to the current graph. It takes a graph as input and modifies the current graph. If the input graph is not of the same size as the current graph, an exception is thrown. Usage example: `g1 += g2`.

- `++`: 
Overloaded the prefix and postfix types of this operator, it increments the current graph by 1 as long as the cell in the matrix is not 0 (meaning no edge). Usage example: `g++` or `++g`.

- `+Graph`: this operator doesnt have any effect really on the graph, returns the graph itself. Usage example: `+g`.

### Subtraction ,decrement and Unary- Operators

- `-`: 
This operator is used to subtract one graph from another. It takes two graphs as input and returns a new graph. If the input graphs are not of the same size, an exception is thrown. Usage example: `g1 = g2 - g3`

- `-=`: 
This operator is used to subtract a graph from the current graph. It takes a graph as input and assigns the new value to the current graph. If the input graph is not of the same size as the current graph, an exception is thrown. Usage example: `g1 -= g2`.

- `-Graph`: 
Unary- ,for each cell in the matrix, in case its not zero, like *(-1) each cell. Usage example: `-g`.

### Multiplication Operators

- `*`: 
This operator is used to multiply two graphs together. It takes two graphs as input and returns a new graph. If the input graphs are not the same size, an exception is thrown.
Usage exampl: `g1 = g2 * g3`

- `*= (for graphs)`: 
This operator is used to multiply the current graph by another graph. It takes a graph as input and modifies the current graph. The adjacency matrix of the current graph is updated to be the matrix product of its own adjacency matrix and the adjacency matrix of the input graph. If the input graph is not the same size as the current graph, an exception is thrown. Usage example: `g1 *= g2`

- `* (scalar)`: 
Overloaded the operator of multiplication to support multiplication with scalar both ways. this operator multiply every cell in the adjecency matrix of a given graph by the given scalar (only if the cell is not 0). Usage example `g1 = g2 * 2`, `g1 = 2 * g2`

- `*= (with scalar)`: 
The same principle as `*=` with graphs in general, multiply each cell in the matrix by the given scalar (if the cell is not zero), and assign the value the the current graph's matrix. Usage example: `g1 *= 2`

### Division operator

- `/=`: 
Given a scalar, divide each cell in the matrix by it (only if the cell is not 0), the new value assigned to the current graph's matrix. Usage example: `g1 /= 2`

### Comparing operators

- `<`: 
    1. If g1 is a submatrix of g2, then g1 < g2. (if they are the same matrix we return false as mentioned in the forum.)
    2. If neither graph is a submatrix of the other, g1 < g2 if the sum of the edges in g1 is less than the sum of edges in g2.
    3. If the sum of edges is equal, g1 < g2 if the number of vertices in g1 is less than the number of vertices in g2.

- `>`:
    Uses the implementation of `<` in reverse placing of the input parameters.


- `==`:

    1. If the number of vertices in both graphs is the same, it compares each element in their adjacency matrices.
    If the adjacency matrices are identical, the graphs are considered equal.

- `<=`:
    Checks if `<` or `==` returns true.

- `>=`:
    Uses `<=` in reverse.

- `!=`: This operator returns true if the two graphs are not equal. It is implemented as the negation of the == operator.


### Printing operator

- `<<`: This operator is overloaded to print the adjacency matrix of the graph. It is declared as a friend function of the Graph class. This is necessary because the << operator needs to access the private data members of the Graph class (the adjacency matrix) which wouldn't be possible without the friend keyword. The operator iterates over each row and column of the matrix, printing each element in a formatted manner. Each row is enclosed in square brackets and elements are separated by commas. Each row of the matrix is printed on a new line.


## Changes made from exe1 In Graph
- `getNumVertices()`,`getAdjacencyMatrix()`,`getIsDirected()`,`getWeightsType()`: made const methods, best practice.
- `loadGraph()`: if the matrix is assymetric and the graph is undirected, it will be set as directed from now and there wont be exception throwing.
- `getNumEdges()`: added method to help me in the comparison operators.

## Changes made from exe1 In Algorithms
- none.

## How to Run

The project includes a Makefile for easy compilation and running of the code. Here are some commands you can use:

- `make `: Compiles the code and runs the demo.
- `make test`: Compiles the code for the tests and run tests.
- `make tidy`: Runs clang-tidy on the source files to check for code quality issues.
- `make valgrind`: Runs valgrind on the demo and test executables to check for memory leaks.
- `make clean`: Removes all compiled files.

## Testing

- In `Test.c` i have added a lot of test to check if the operators works correctly on different matrices scenarios, and added test to see if after the changes made by the operators, the algorithms still works well.



