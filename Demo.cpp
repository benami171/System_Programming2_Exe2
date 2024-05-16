/*
 * Demo program for Exercise 3.
 * Author: Benjamin Saldman.
 */

#include "Graph.hpp"
#include "Algorithms.hpp"
using ariel::Algorithms;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

int main()
{
    ariel::Graph g1;
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph); // Load the graph to the object.

    cout << g1 << endl; // Should print the matrix of the graph: [0, 1, 0], [1, 0, 1], [0, 1, 0]

    // 3x3 matrix that represents a weighted connected graph.
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    ariel::Graph g2;
    g2.loadGraph(weightedGraph); // Load the graph to the object.

    ariel::Graph g10 = g1 * g2;
    cout<<"g10 = g1 * g2: " << endl << g10 << endl; // Should print the multiplication of the matrices of g1 and g2: [0, 0, 2], [1, 0, 1], [1, 0, 0]
    ariel::Graph g11 = g1 * 2;
    cout<<"g11 = g1 * 2:" << endl << g11 << endl; // Should print the multiplication of the matrix of g1 by 2: [0, 2, 0], [2, 0, 2], [0, 2, 0]
    ariel::Graph g12 = 2 * g1;
    cout<< "g12 = 2 * g1:" << endl << g12 << endl; // Should print the multiplication of the matrix of g1 by 2: [0, 2, 0], [2, 0, 2], [0, 2, 0]



  
    
    ariel::Graph g3 = g1 + g2; // Add the two graphs together.
    cout<<"g3 = g1 + g2:" << endl << g3 << endl;           // Should print the matrix of the graph: [0, 2, 1], [2, 0, 3], [1, 3, 0]

    g1 *= -2;        // Multiply the graph by -2.
    cout << "g1 *= -2:" << endl << g1 << endl; // Should print the matrix of the graph: [0, -2, 0], [-2, 0, -2], [0, -2, 0]

    g1 /= -2;
    ariel::Graph g4 = g1 * g2; // Multiply the two graphs together.
    cout<< "divided g1 by 2, g4 = g1 * g2 :" << endl << g4 << endl ;           // Should print the multiplication of the matrices of g1 and g2: [0, 0, 2], [1, 0, 1], [1, 0, 0]

    // 5x5 matrix that represents a connected graph.
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    ariel::Graph g5;
    g5.loadGraph(graph2); // Load the graph to the object.
    cout << "trying g5 * g1:" << endl;
    try
    {
        ariel::Graph g6 = g5 * g1; // Multiply the two graphs together.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print "The size of the matrices is not the same."
    }

    vector<vector<int>> weightedGraph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};

    ariel::Graph g7;
    g7.loadGraph(weightedGraph2); // Load the graph to the object.

    g7 = g7 * g1;
    cout<< "g7 = g7 * g1:" << endl << g7 << endl; // Should print the multiplication of the matrices of g7 and g1: [0, 0, 2], [1, 0, 1], [1, 0, 0]

    vector<vector<int>> graph3 = {
        {0, 2, 5, 0, 5},
        {4, 0, 2, 5, 5},
        {0, 3, 0, 4, 4},
        {6, 6, 2, 0, 1},
        {7, 0, 2, 6, 0}};

    g1.loadGraph(graph3); // Load the graph to the object.

    vector<vector<int>> graph4 = {
        {0, 2, 5},
        {3, 0, 4},
        {6, 2, 0}};

    g2.loadGraph(graph4); // Load the graph to the object.

    cout << "is g1 Contains g2 ? " << g1.isContains(g2) << endl; // Should print "1"

    vector<vector<int>> graph5 = {
        {0, 2, 2},
        {3, 0, 4},
        {6, 2, 0}};
    g1.loadGraph(graph5); // Load the graph to the object.

    cout << "is g1 == g2 ? " << (g1 == g2) << endl; // Should print "0" 
    cout << "is g1 < g2 ? " << (g1 < g2) << endl;   // Should print "0" 
    cout << "is g1 > g2 ? " << (g1 > g2) << endl;   // Should print "0" 
}
