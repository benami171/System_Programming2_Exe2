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

    size_t Graph::getNumVertices() const
    {
        return numVertices;
    }

    vector<vector<int>> Graph::getAdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }

    bool Graph::getIsDirected() const
    {
        return this->isDirected;
    }

    int Graph::getWeightsType() const
    {
        return this->weightType;
    }

    size_t Graph::getNumEdges() const
    {

        bool type = getIsDirected();
        size_t edges = 0;

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
            return edges /= 2;
        }
        else
        {
            return edges;
        }
    }

    /*
        the following method will check if g1 contains g2.
        first, if the number of vertices in g2 is greater than the number of vertices in g1,
        then g1 can't contain g2.
        then we will check if the adjacency matrix of g2 is a submatrix of the adjacency matrix of g1.
        both of the graphs are represented as adjacency matrices,
        so we know the diagonal should be all zeros, so we dont need to go over
        all the possibilities of the submatrices. we will

        will helps us in operator< overloading.

    */

    // return true if g1 contains g2, otherwise return false.
    bool Graph::isContains(const Graph &g) const
    {
        if (g.adjacencyMatrix.size() > this->adjacencyMatrix.size())
        {
            return false;
        }
        int diff = this->adjacencyMatrix[0].size() - g.adjacencyMatrix[0].size();

        int equalCount = 0;
        // cout << "this: \n" << *this << endl;
        // cout << "g: \n" << g << endl;

        for (size_t t = 0; t < diff; t++)
        {
            for (size_t i = 0; i < g.adjacencyMatrix[0].size(); i++)
            {
                for (size_t j = 0; j < g.adjacencyMatrix[0].size(); j++)
                {
                    // cout << "this[i+t][j+t] = " << this->adjacencyMatrix[i+t][j+t] << " g[i][j] = " << g.adjacencyMatrix[i][j] << endl;
                    if (this->adjacencyMatrix[i + t][j + t] == g.adjacencyMatrix[i][j])
                    {
                        equalCount++;
                    }
                    else
                    {
                        equalCount = 0;
                        break;
                    }
                }
            }
        }

        if (equalCount == g.adjacencyMatrix[0].size() * g.adjacencyMatrix[0].size())
        {
            return true;
        }

        return false;
    }

    /*
            implementing + operator overloading.
    */
    // Overloading the + operator to add two graphs together
    // by adding their adjacency matrices.
    Graph Graph::operator+(const Graph &g)
    {
        Graph resGraph(*this);

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
    Graph &Graph::operator+=(const Graph &g)
    {
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

    // Overloading the Prefix version of the ++ operator to increment all the elements of the graph by 1.
    Graph &Graph::operator++()
    {
        for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < this->adjacencyMatrix[i].size(); j++)
            {
                if (i != j && this->adjacencyMatrix[i][j] != 0)
                {
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
    Graph &Graph::operator--()
    {
        for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < this->adjacencyMatrix[i].size(); j++)
            {
                if (i != j && this->adjacencyMatrix[i][j] != 0)
                {
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
    Graph Graph::operator-(const Graph &g) const
    {
        Graph resGraph(*this);

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

    Graph &Graph::operator-=(const Graph &g)
    {
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
    Graph Graph::operator-() const
    {
        Graph resGraph(*this);
        for (size_t i = 0; i < resGraph.adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < resGraph.adjacencyMatrix[i].size(); j++)
            {
                if (resGraph.adjacencyMatrix[i][j] != 0)
                {
                resGraph.adjacencyMatrix[i][j] = -resGraph.adjacencyMatrix[i][j];
                }
            }
        }

        return resGraph;
    }

    /*
            implementing * operator overloading.
    */

    Graph Graph::operator*(const Graph &g) const
    {
        Graph resGraph(*this);
        vector<vector<int>> resMatrix;
        // check if the matrices have the same dimensions
        if (this->getNumVertices() != g.getNumVertices())
        {

            throw invalid_argument("The size of the matrices is not the same.");
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
            // in my implementation there is no self loops, and the diagonal should be zero.
            // load graph will throw an exception if the diagonal is not zero.
            resMatrix[i][i] = 0;
        }
        resGraph.loadGraph(resMatrix);
        return resGraph;
    }

    Graph Graph::operator*(int scalar) const
    {
        Graph resGraph(*this);
        for (size_t i = 0; i < resGraph.adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < resGraph.adjacencyMatrix[i].size(); j++)
            {
                resGraph.adjacencyMatrix[i][j] *= scalar;
            }
        }
        return resGraph;
    }

    Graph operator*(int scalar, const Graph &g)
    {
        return g * scalar;
    }

    // Overloading the *= operator to multiply the graph by a scalar.
    Graph &Graph::operator*=(const int &scalar)
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
            implementing /= operator overloading.
    */

    Graph &Graph::operator/=(const int &scalar)
    {
        if (scalar == 0)
        {
            throw invalid_argument("Division by zero is not allowed.");
        }
        for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < this->adjacencyMatrix[i].size(); j++)
            {
                if (this->adjacencyMatrix[i][j] != 0)
                {
                    this->adjacencyMatrix[i][j] /= scalar;
                }
            }
        }
        return *this;
    }

    /*
            implementing comparison operators.
    */

    // Overloading the < operator, G1<G2 if G1 matrix is submatrix of G2 matrix.
    // if G1 is not a submatrix of G2 and G2 is not a submatrix of G1,
    // then G1<G2 if the sum of edges in G1 is less than the sum of edges in G2.
    // if the sum of edges is equal

    bool Graph::operator<(const Graph &g) const
    {
        // if g contains this, return true as this<g.
        if (g.isContains(*this))
        {
            return true;
        }

        // if g doesnt contain this, and this contains g, return false as this>g.
        if (this->isContains(g))
        {
            return false;
        }

        // if g and this are not submatrices of each other, then compare the sum of edges.
        size_t thisEdges = this->getNumEdges();
        size_t gEdges = g.getNumEdges();

        if (thisEdges < gEdges)
        {
            return true;
        }
        else if (thisEdges > gEdges)
        {
            return false;
        }
        else // if thisEdges == gEdges
        {
            if (this->numVertices < g.numVertices)
            {
                return true;
            }
            else if (this->numVertices > g.numVertices)
            {
                return false;
            }
            else
            {
                return false;
            }
        }
    }

    bool Graph::operator<=(const Graph &g) const
    {
        return (*this < g) || (*this == g);
    }

    bool Graph::operator>(const Graph &g) const
    {
        return g < *this;
    }

    bool Graph::operator>=(const Graph &g) const
    {
        return g <= *this;
    }

    bool Graph::operator==(const Graph &g) const
    {

        if (this->numVertices == g.numVertices)
        {
            for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
            {
                for (size_t j = 0; j < this->adjacencyMatrix[i].size(); j++)
                {
                    if (this->adjacencyMatrix[i][j] != g.adjacencyMatrix[i][j])
                    {
                        return false;
                    }
                }
            }
            return true;
        } // if not, check if G1 !< G2 and G2 !< G1
        else if (!((*this) < (g)) && !(g < (*this)))
        {
            return true;
        }
        return false;
    }

    bool Graph::operator!=(const Graph &g) const
    {
        return !(*this == g);
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
                    os << ",";
                }
            }
            os << "]\n";
        }
        return os;
    }
}