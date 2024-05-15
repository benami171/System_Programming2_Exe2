// NAME: GAL BEN AMI

#include <iostream>
#include <vector>
#include "Algorithms.hpp"
#include <stdexcept>
#include "Graph.hpp"
#include <climits>
#include <iomanip>

using namespace std;

namespace ariel
{

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
        if (matrix.empty() || matrix[0].size() < 2)
        {
            throw invalid_argument("Input matrix is empty");
        }
        this->numVertices = matrix.size();
        this->adjacencyMatrix = matrix;
        size_t matSize = matrix.size();

        for (size_t i = 0; i < matSize; i++)
        {
            if (matrix[i].size() != matSize)
            {
                throw invalid_argument("Input matrix is not a square matrix");
            }
            for (size_t j = 0; j < matSize; j++)
            {
                if (i == j && matrix[i][j] != 0)
                {
                    throw invalid_argument("In adjacency matrix, the diagonal elements should be zeros");
                }

                if (matrix[i][j] != matrix[j][i] && !this->isDirected)
                {
                    this->isDirected = true;
                  //  throw invalid_argument("Undirected graph should have symmetric adjacency matrix");
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
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                if (i != j && adjacencyMatrix[i][j] != 0)
                {
                    ++edges;
                }
            }
        }
        if (!this->isDirected)
        {
            edges /= 2;
            cout << "Undirected graph with " << numVertices << " vertices and " << edges << " edges." << endl;
        }
        else
        {
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

    vector<vector<int>> Graph::getAdjacencyMatrix() const
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

    

    /*
            implementing + operator overloading.
    */
    // Overloading the + operator to add two graphs together
    // by adding their adjacency matrices.
    Graph Graph::operator+(const Graph &g){
        Graph resGraph;

        // check if the matrices have the same dimensions
        if (this->adjacencyMatrix.size() != g.adjacencyMatrix.size() ||
            this->adjacencyMatrix[0].size() != g.adjacencyMatrix[0].size())
        {
            throw invalid_argument("The matrices should have the same dimensions.");  
        }

        vector<vector<int>> resMatrix;
        // iterating over each row of the matrix.
        for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            // creating an empty row to store the sum of the two matrices.
            vector<int> row; 
            for (size_t j = 0; j < this->adjacencyMatrix[i].size(); j++)
            {
                // adding the corresponding elements of the two matrices.
                // and storing the sum in the row.
                row.push_back(this->adjacencyMatrix[i][j] + g.adjacencyMatrix[i][j]);
            }
            // adding the row to the result matrix.
            resMatrix.push_back(row);
        }

        resGraph.loadGraph(resMatrix);
        return resGraph;

    }

    /*
            implementing += operator overloading.
    */
    // Overloading the += operator to add two graphs together
    // by adding their adjacency matrices.
    Graph& Graph::operator+=(const Graph &g){
        // check if the matrices have the same dimensions
        if (this->adjacencyMatrix.size() != g.adjacencyMatrix.size() ||
            this->adjacencyMatrix[0].size() != g.adjacencyMatrix[0].size())
        {
            throw invalid_argument("The matrices should have the same dimensions.");  
        }

        // iterating over each row of the matrix.
        for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < this->adjacencyMatrix[i].size(); j++)
            {
                // adding the corresponding elements of the two matrices.
                this->adjacencyMatrix[i][j] += g.adjacencyMatrix[i][j];
            }
        }

        return *this;
    }

    // Unary plus operator overloading, returns the graph itself.
    // made it const to avoid changing the graph, and because it doesn't need to change it.
    Graph Graph::operator+() const
    {
        return *this;
    }

    Graph& Graph::operator++()
    {
        for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < this->adjacencyMatrix[i].size(); j++)
            {
                if (i!=j){
                this->adjacencyMatrix[i][j]++;
                }
            }
        }
        return *this;
    }

    // Overloading the Postfix version of the ++ operator
    // the int argument is a flag to differentiate between the prefix and postfix versions.
    Graph Graph::operator++(int)
    {
        // calling copy constructor to copy the graph.
        Graph temp(*this);
        ++*this;
        return temp;
    }

    // Overloading the Prefix -- operator to decrement all the elements of the graph by 1.
    Graph& Graph::operator--()
    {
        for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < this->adjacencyMatrix[i].size(); j++)
            {
                if (i!=j){
                this->adjacencyMatrix[i][j]--;
                }
            }
        }
        return *this;
    }


    // Overloading the Postfix -- operator to decrement all the elements of the graph by 1.
    Graph Graph::operator--(int)
    {
        Graph temp(*this);
        --*this;
        return temp;
    }


    /*
            implementing - operator overloading.
    */
  
    // Overloading the - operator to subtract two graphs together
    // by subtracting their adjacency matrices.
    Graph Graph::operator-(const Graph &g){
        Graph resGraph;

        // check if the matrices have the same dimensions
        if (this->adjacencyMatrix.size() != g.adjacencyMatrix.size() ||
            this->adjacencyMatrix[0].size() != g.adjacencyMatrix[0].size())
        {
            throw invalid_argument("The matrices should have the same dimensions.");  
        }

        vector<vector<int>> resMatrix;
        // iterating over each row of the matrix.
        for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            // creating an empty row to store the subtraction of the two matrices.
            vector<int> row; 
            for (size_t j = 0; j < this->adjacencyMatrix[i].size(); j++)
            {
                // subtracting the corresponding elements of the two matrices.
                row.push_back(this->adjacencyMatrix[i][j] - g.adjacencyMatrix[i][j]);
            }
            // adding the row to the result matrix.
            resMatrix.push_back(row);
        }

        resGraph.loadGraph(resMatrix);
        return resGraph;

    }

    Graph& Graph::operator-=(const Graph &g){
        // check if the matrices have the same dimensions
        if (this->adjacencyMatrix.size() != g.adjacencyMatrix.size() ||
            this->adjacencyMatrix[0].size() != g.adjacencyMatrix[0].size())
        {
            throw invalid_argument("The matrices should have the same dimensions.");  
        }

        // iterating over each row of the matrix.
        for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < this->adjacencyMatrix[i].size(); j++)
            {
                // subtracting the corresponding elements of the two matrices.
                this->adjacencyMatrix[i][j] -= g.adjacencyMatrix[i][j];
            }
        }

        return *this;
    }


    // Unary minus operator overloading, returns the graph with all its elements negated.
    Graph Graph::operator-() const{
        Graph resGraph(*this);
        for (size_t i = 0; i < resGraph.adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < resGraph.adjacencyMatrix[i].size(); j++)
            {
                resGraph.adjacencyMatrix[i][j] = -resGraph.adjacencyMatrix[i][j];
            }
        }

        return resGraph;
    }

    /*
            implementing * operator overloading.
    */

    Graph Graph:: operator*(const Graph &g)
    {
        Graph resGraph;
        vector<vector<int>> resMatrix;
        // check if the matrices have the same dimensions
        if (this->adjacencyMatrix[0].size() != g.adjacencyMatrix.size())
        {
            throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        // iterating over each row of the first matrix.
        for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            // creating an empty row to store the multiplication of the two matrices.
            vector<int> row;
            for (size_t j = 0; j < g.adjacencyMatrix[0].size(); j++)
            {
                int sum = 0;
                // iterating over each column of the second matrix.
                for (size_t k = 0; k < g.adjacencyMatrix.size(); k++)
                {
                    // multiplying the corresponding elements of the two matrices.
                    // and adding the result to the sum.
                    sum += this->adjacencyMatrix[i][k] * g.adjacencyMatrix[k][j];
                }
                // adding the sum to the row.
                row.push_back(sum);
            }
            // adding the row to the result matrix.
            resMatrix.push_back(row);
        }
        // resetting the result matrix diagonal to zeroes.
        for (size_t i = 0; i < resMatrix.size(); i++)
        {
            resMatrix[i][i] = 0;
        }
        resGraph.loadGraph(resMatrix);
        return resGraph;
    }

    // Overloading the *= operator to multiply the graph by a scalar.
    Graph& Graph::operator*=(const int &scalar)
    {
        for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < this->adjacencyMatrix[i].size(); j++)
            {
                this->adjacencyMatrix[i][j] *= scalar;
            }
        }
        return *this;
    }

    /*
            implementing / operator overloading.
    */  

    Graph& Graph::operator/=(const int &scalar)
    {
        for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < this->adjacencyMatrix[i].size(); j++)
            {
                this->adjacencyMatrix[i][j] /= scalar;
            }
        }
        return *this;
    }


    // Overloading the << operator to print the adjacency matrix of the graph.
    std::ostream &operator<<(std::ostream &os, const Graph &g)
    {
        for (size_t i = 0; i < g.getAdjacencyMatrix().size(); i++)
        {
            os << "[";
            for (size_t j = 0; j < g.getAdjacencyMatrix()[i].size(); j++)
            {

                os << std::setw(2) << g.getAdjacencyMatrix()[i][j];
                if (j != g.getAdjacencyMatrix()[i].size() - 1)
                {
                    os << ", ";
                }
            }
            os << "]\n";
        }
        return os;
    }
}