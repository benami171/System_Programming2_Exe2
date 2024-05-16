#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

using namespace std;

namespace ariel{
class Graph {
    // we made numVertices as size_t because it will never be negative
    // and also the vector constructor takes size_t as an argument for the size
private:
    vector<vector<int>> adjacencyMatrix;
    bool isDirected; // false for undirected, true for directed
    bool containsNegativeCycle;
    int weightType; // -1 for negative weight, 0 for no weight, 1 for positive weight
    size_t numVertices;

public:

// ADDITION OPERATORS
    Graph operator+(const Graph &g);
    Graph& operator+=(const Graph &g);
    Graph operator+() const;

// INC/DEC OPERATORS
    Graph& operator++(); // prefix incremention
    Graph operator++(int); // postfix incremention
    Graph& operator--(); // prefix decremention
    Graph operator--(int); // postfix decremention

// SUBTRACTION OPERATORS
    Graph operator-(const Graph &g);
    Graph& operator-=(const Graph &g);
    Graph operator-() const;

// MULTIPLICATION OPERATORS
    Graph operator*(const Graph &g);
    Graph& operator*=(const int &scalar);

// DIVISION OPERATORS
    Graph& operator/=(const int &scalar);


// COMPARISON OPERATORS.

    bool operator==(const Graph &g) const;
    bool operator!=(const Graph &g) const;
    bool operator<(const Graph &g) const;
    bool operator>(const Graph &g) const;
    bool operator<=(const Graph &g) const;
    bool operator>=(const Graph &g) const;
    



    Graph(bool directed = false) : isDirected(directed) {}
    // inline Constructor
    
    void setWeightsType(int type);

    friend bool isContained(const Graph& g1, const Graph& g2);
    
    int getWeightsType();

    void printGraph();

    bool getContainsNegativeCycle();

    void loadGraph(vector<vector<int>> &matrix);
    
    bool getIsDirected();

    size_t getNumVertices() const;

    void setContainsNegativeCycle(bool flag);
    
    void setIsDirected(bool type);

    vector<vector<int>> getAdjacencyMatrix() const;

    friend ostream &operator<<(ostream &os, const Graph &g);
};


}
#endif