// NAME: GAL BEN AMI

#include <iostream>
#include <vector>
#include "Algorithms.hpp"
#include <stdexcept>
#include "Graph.hpp"
#include <climits>

using namespace std;
using namespace ariel;

// Determines the weight type of the graph.
int whatWeightType(vector<vector<int>> &matrix)
{
    int type = 0;
    size_t matSize = matrix.size();
    for (size_t i = 0; i < matSize; i++)
    {
        for (size_t j = 0; j < matSize; j++)
        {
            if (matrix[i][j] < 0)
            {
                return -1;
            }
            else if (matrix[i][j] > 0)
            {
                type = 1;
            }
        }
    }
    return type;
}

// Loads a graph from an adjacency matrix. Throws an exception if the matrix is not square, 
// if the diagonal is not zero, or if the matrix is not symmetric for an undirected graph.
void Graph::loadGraph(vector<vector<int>> &matrix)
{
    if (matrix.empty() || matrix[0].size()<2)
    {
        throw invalid_argument("Input matrix is empty");
    }
    this->numVertices = matrix.size();
    this->adjacencyMatrix = matrix;
    size_t matSize = matrix.size();

    for(size_t i = 0; i < matSize; i++){
        if (matrix[i].size() != matSize){
            throw invalid_argument("Input matrix is not a square matrix");
        }
        for (size_t j = 0; j < matSize; j++){
            if (i == j && matrix[i][j] != 0){
                throw invalid_argument("In adjacency matrix, the diagonal elements should be zeros");
            }

            if( matrix[i][j] != matrix[j][i] && !this->isDirected){
                throw invalid_argument("Undirected graph should have symmetric adjacency matrix");
            }
        }
    }
    this->weightType = whatWeightType(matrix);
}

// Prints the graph, stating whether it's directed or undirected,
// and the number of vertices and edges.
void Graph::printGraph()
{
    bool type = getIsDirected();
    int edges = 0;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i){
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j){
            if (i != j && adjacencyMatrix[i][j] != 0){
                ++edges;
            }
        }
    }
    if (!this->isDirected){ 
        edges /= 2;
        cout << "Undirected graph with " << numVertices << " vertices and " << edges << " edges." << endl;
    }
    else{
        cout << "Directed graph with " << numVertices << " vertices and " << edges << " edges." << endl;
    }
}


void Graph::setContainsNegativeCycle(bool flag)
{
    this->containsNegativeCycle = flag;
}

bool Graph::getContainsNegativeCycle()
{
    return this->containsNegativeCycle;
}

// check if the graph is directed or undirected
// by comparing the adjacency matrix with its transpose
void Graph::setIsDirected(bool type)
{
    this->isDirected = type;
}

void Graph::setWeightsType(int type)
{
    this->weightType = type;
}

size_t Graph::getNumVertices()
{
    return numVertices;
}

vector<vector<int>> Graph::getAdjacencyMatrix()
{
    return adjacencyMatrix;
}

bool Graph::getIsDirected()
{
    return this->isDirected;
}

int Graph::getWeightsType()
{
    return this->weightType;
}
