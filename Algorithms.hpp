// NAME: GAL BEN AMI

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include "Graph.hpp"

using namespace std;
namespace ariel{

class Algorithms
{
    public:
        static bool isConnected(Graph& graph); // if can reach all vertices from any vertex
        static string shortestPath(Graph& graph, int start, int end); // using BFS, Dijkstra or Bellman-Ford.
        static string isContainsCycle(Graph& graph); // using DFS implementation.
        static string findCycle(Graph& graph); // a helper function
        static string isBipartite(Graph& graph); 
        static string negativeCycle(Graph& graph); // using Bellman-Ford.
};

}

#endif