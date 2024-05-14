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
    Graph(bool directed = false) : isDirected(directed) {}
    // inline Constructor
    
    void setWeightsType(int type);
    
    int getWeightsType();

    void printGraph();

    bool getContainsNegativeCycle();

    void loadGraph(vector<vector<int>> &matrix);
    
    bool getIsDirected();

    size_t getNumVertices();

    void setContainsNegativeCycle(bool flag);
    
    void setIsDirected(bool type);

    vector<vector<int>> getAdjacencyMatrix();

};
}
#endif