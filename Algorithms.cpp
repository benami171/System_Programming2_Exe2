// NAME: GAL BEN AMI

#include <climits>
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <queue>
#include <limits>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
using namespace ariel;

// Enum to represent the color of a vertex in the graph
// used in the cycle detection algorithm
enum Color
{
    WHITE,
    GRAY,
    BLACK
};

// Helper function to construct the path from the parent array
string constructPath(const vector<int> &parent, int start, int end)
{
    if (parent[(size_t)end] == -1)
    {
        return "No path found";
    }

    string path = to_string(end);
    while (end != start)
    {
        end = parent[(size_t)end];
        path = to_string(end) + "->" + path;
    }
    return path;
}

// Helper function to construct the cycle path
// The cycle path is constructed from the cyclePath vector
string cycleConstructor(vector<int> &cyclePath, int startingVertex)
{
    string cycle;
    size_t start = 0;
    for (start = 0; start < cyclePath.size(); start++)
    {
        if (cyclePath[start] == startingVertex)
        {
            break;
        }
    }
    for (size_t j = start; j < cyclePath.size(); j++)
    {
        cycle = cycle + to_string(cyclePath[j]) + "->";
    }
    cycle = cycle + to_string(startingVertex);
    return cycle;
}

// BFS function
string BFS(Graph &graph, int start, int end)
{
    vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix();
    size_t numVertices = graph.getNumVertices();
    vector<int> parentVertx(numVertices, -1);
    vector<bool> visited(numVertices, false);
    queue<int> queue;
    // Mark the start vertex as visited
    visited[(size_t)start] = true;
    // Set the parentVertxious node of the start vertex as itself
    // parentVertx[start] = start;
    // Add the start vertex to the queue
    queue.push(start);

    // While the queue is not empty
    while (!queue.empty())
    {
        // Get the front vertex of the queue
        int current = queue.front();
        // Remove the front vertex from the queue
        queue.pop();

        // If the current vertex is the end vertex, break the loop
        if (current == end)
        {
            break;
        }

        // For each vertex in the graph
        for (size_t i = 0; i < numVertices; ++i)
        {
            // If the current vertex is connected to the i-th vertex and the i-th vertex is not visited
            if (adjMatrix[(size_t)current][i] != 0 && !visited[i])
            {
                // Add the i-th vertex to the queue
                queue.push((int)i);
                // Mark the i-th vertex as visited
                visited[i] = true;
                // Set the parentVertxious node of the i-th vertex as the current vertex
                parentVertx[i] = current;
            }
        }
    }

    return constructPath(parentVertx, start, end);
}

// Dijkstra function
string Dijkstra(Graph &graph, int start, int end)
{
    size_t numVertices = graph.getNumVertices();
    vector<bool> visited(numVertices, false);
    vector<int> distance(numVertices, INT_MAX);
    vector<int> parentVertx(numVertices, -1);

    // Initialize the priority queue for Dijkstra's algorithm
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Initialize the distance of the start vertex as 0
    distance[(size_t)start] = 0;
    // Add the start vertex to the priority queue
    pq.push({0, start});

    // While the priority queue is not empty
    while (!pq.empty())
    {
        // Get the vertex with the smallest distance
        int u = pq.top().second;
        // Remove the vertex from the priority queue
        pq.pop();

        // If the vertex has been visited, skip it
        if (visited[(size_t)u])
        {
            continue;
        }
        // Mark the vertex as visited
        visited[(size_t)u] = true;

        // For each vertex in the graph
        for (size_t v = 0; v < numVertices; ++v)
        {
            // If the u-th vertex is connected to the v-th vertex and the v-th vertex is not visited
            if (graph.getAdjacencyMatrix()[(size_t)u][v] != 0 && !visited[v])
            {
                // Calculate the new distance to the v-th vertex
                int newdistance = distance[(size_t)u] + graph.getAdjacencyMatrix()[(size_t)u][v];
                // If the new distance is smaller than the current distanceance
                if (newdistance < distance[v])
                {
                    // Update the distance to the v-th vertex
                    distance[v] = newdistance;
                    // Set the parentVertxious node of the v-th vertex as the u-th vertex
                    parentVertx[v] = u;
                    // Add the v-th vertex to the priority queue
                    pq.push({distance[v], v});
                }
            }
        }
    }
    // at this stage, parentVertx contains the shortest path from start to end
    return constructPath(parentVertx, start, end);
}

string bellmanford(Graph &graph, int start, int end)
{
    size_t numVertices = graph.getNumVertices();
    vector<int> distance(numVertices, INT_MAX);
    vector<int> parentVertx(numVertices, -1);
    vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix();

    // This is the main part of the Bellman-Ford algorithm.
    // It relaxes all the edges 'numVertices - 1' times.
    // For each vertex, it tries to update the shortest distance value of all its adjacent vertices.
    // If the sum of the shortest distance value of the current vertex (d[u]) and the weight of the edge connecting
    // the current vertex and its adjacent vertex (adjMatrix[u][v]) is less than the shortest distance value of the adjacent vertex (d[v]),
    // then update d[v] and set the current vertex as the parent of the adjacent vertex.
    distance[(size_t)start] = 0;
    for (size_t i = 0; i < numVertices - 1; ++i)
    {
        for (size_t u = 0; u < numVertices; ++u)
        {
            for (size_t v = 0; v < numVertices; ++v)
            {
                if (adjMatrix[u][v] != 0 && distance[u] != INT_MAX && distance[u] + adjMatrix[u][v] < distance[v])
                {
                    distance[v] = distance[u] + adjMatrix[u][v];
                    parentVertx[v] = u;
                }
            }
        }
    }

    // This loop checks for negative weight cycles in the graph.
    // It tries to relax all edges one more time.
    // If it can still update a shortest distance value, then there is a negative weight cycle.
    // Because we can always get a shorter path by including one more cycle in the path.
    vector<bool> inNegativeCycle(numVertices, false);
    for (size_t u = 0; u < numVertices; ++u)
    {
        for (size_t v = 0; v < numVertices; ++v)
        {
            if (adjMatrix[u][v] != 0 && distance[u] != INT_MAX && distance[u] + adjMatrix[u][v] < distance[v])
            {
                return "Negative cycle detected";
            }
        }
    }

    if (distance[(size_t)end] == INT_MAX)
    {
        return "No path found";
    }

    return constructPath(parentVertx, start, end);
}

bool Algorithms::isConnected(Graph &graph)
{
    size_t numVertices = graph.getNumVertices();
    vector<bool> visited(numVertices, false);
    queue<int> q;

    if (numVertices == 0)
    {
        return true; // An empty graph is considered connected
    }

    vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix(); // Fetch the adjacency matrix once

    // For each vertex in the graph
    for (size_t startVertex = 0; startVertex < numVertices; ++startVertex)
    {
        // Reset the visited vector
        fill(visited.begin(), visited.end(), false);

        // Start a BFS from the current vertex
        q.push(startVertex);
        visited[startVertex] = true;

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            for (size_t i = 0; i < numVertices; ++i)
            {
                if (adjacencyMatrix[(size_t)current][i] != 0 && !visited[i])
                {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }

        // After performing BFS from the current vertex, check if all vertices were visited
        for (bool v : visited)
        {
            if (!v)
            {
                return false;
            }
        }
    }

    return true;
}

string Algorithms::shortestPath(Graph &graph, int start, int end)
{

    if (start < 0 || end < 0 || start >= graph.getNumVertices() || end >= graph.getNumVertices())
    {
        return "Invalid start or end vertex.";
    }

    if (graph.getWeightsType() == 0)
    {
        return BFS(graph, start, end);
    }

    else if (graph.getWeightsType() == 1)
    {
        return Dijkstra(graph, start, end);
    }

    return bellmanford(graph, start, end);
}

// This function is a helper function used to detect a cycle in a graph.
// It uses Depth-First Search (DFS) to traverse the graph.
// It marks each visited node as 'GRAY' and unvisited nodes as 'WHITE'.
// If it visits a node that is already marked as 'GRAY', it means that a cycle is detected.
// If a node is completely visited, it is marked as 'BLACK' and removed from the path.
string containsCycleUtil(Graph &graph, size_t u, vector<Color> *color, vector<int> *parent, vector<int> *cyclePath)
{
    // Marking the vertex as visited and
    // adding the starting vertex to the path.
    (*color)[u] = GRAY;
    cyclePath->push_back(u);

    vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix();
    for (size_t v = 0; v < graph.getAdjacencyMatrix().size(); v++)
    {
        if (adjMatrix[u][v] != 0)
        {
            if ((*color)[v] == WHITE)
            {
                (*parent)[v] = (int)u;
                string cycle = containsCycleUtil(graph, v, color, parent, cyclePath);
                if (!cycle.empty())
                {
                    return cycle; // cycle detected
                }
            }
            else if ((*color)[v] == GRAY)
            {
                if (!graph.getIsDirected() && (*parent)[u] == (int)v)
                {
                    continue;
                }
                return cycleConstructor(*cyclePath, v);
            }
        }
    }

    // as we finished with the vertex, we mark it as black
    // and remove it from the path
    (*color)[u] = BLACK;
    cyclePath->pop_back();

    return ""; // no cycle detected
}

// This function is used to find a cycle in a graph.
// It initializes all nodes as 'WHITE' (unvisited) and starts DFS from each unvisited node.
// If a cycle is detected during the DFS, it returns a message indicating that a cycle is detected.
// If no cycle is detected after visiting all nodes, it returns a message indicating that no cycle is detected.
string Algorithms::findCycle(Graph &graph)
{
    size_t numVertices = graph.getNumVertices();
    vector<Color> color(numVertices, WHITE);
    vector<int> parentVertx(numVertices, -1);
    vector<int> cyclePath;

    for (size_t u = 0; u < numVertices; u++)
    {
        if (color[u] == WHITE)
        {
            string cycle = containsCycleUtil(graph, u, &color, &parentVertx, &cyclePath);
            if (!cycle.empty())
            {
                return "Graph contains a cycle: " + cycle; // cycle detected
            }
        }
    }

    return "0"; // no cycle detected
}

string Algorithms::isContainsCycle(Graph &graph)
{
    if (graph.getNumVertices() < 2){
        return "0";
    }

    return findCycle(graph);
}

// this function creates a copy of the original adjMatrix and converts it to an undirected graph
// it helps us in the isBipartite function.
vector<vector<int>> convertToUndirected(Graph &graph)
{
    vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix(); // Original adjacency matrix
    vector<vector<int>> newAdjMatrix = adjMatrix;               // Copy of the adjacency matrix
    size_t numVertices = graph.getNumVertices();

    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = i + 1; j < numVertices; j++)
        {
            if (newAdjMatrix[i][j] != 0 && newAdjMatrix[j][i] != 0)
            {
                // If there are edges in both directions, take the average of the two weights
                newAdjMatrix[i][j] = newAdjMatrix[j][i] = (newAdjMatrix[i][j] + newAdjMatrix[j][i]) / 2;
            }
            else if (newAdjMatrix[i][j] != 0)
            {
                // If there's only an edge from i to j, use its weight for the edge from j to i
                newAdjMatrix[j][i] = newAdjMatrix[i][j];
            }
            else if (newAdjMatrix[j][i] != 0)
            {
                // If there's only an edge from j to i, use its weight for the edge from i to j
                newAdjMatrix[i][j] = newAdjMatrix[j][i];
            }
        }
    }

    return newAdjMatrix;
}

string Algorithms::isBipartite(Graph &graph)
{
    vector<vector<int>> groups(2);
    vector<vector<int>> adjMatrix;

    // Check if the graph is directed
    if (graph.getIsDirected())
    {
        // If the graph is directed, get a convert adjMatrix vertion of the graph to undirected.
        adjMatrix = convertToUndirected(graph);
    }
    else
    {
        // If the graph is undirected, use its adjacency matrix as is
        adjMatrix = graph.getAdjacencyMatrix();
    }

    size_t numVertices = graph.getNumVertices();
    vector<int> colorArr(numVertices, -1);

    // Iterate over all vertices in the graph
    for (size_t i = 0; i < numVertices; i++)
    {
        // If the vertex hasn't been colored yet
        if (colorArr[i] == -1)
        {
            // Create a queue for BFS and enqueue the current vertex
            queue<int> q;
            q.push(i);

            // Color the first vertex with color 0 if group 0 is empty, else color it with 1
            colorArr[i] = groups[0].empty() ? 0 : 1;

            // Push the colored vertex to the corresponding group
            groups[(size_t)colorArr[i]].push_back(i);

            // While there are vertices in the queue
            while (!q.empty())
            {
                // Dequeue a vertex
                int node = q.front();
                q.pop();

                // Iterate over all vertices
                for (size_t v = 0; v < numVertices; v++)
                {
                    // If there is an edge from the dequeued vertex to v and v is not colored
                    if (adjMatrix[(size_t)node][v] != 0 && colorArr[v] == -1)
                    {
                        // Color the vertex with the opposite color of its neighbor
                        colorArr[v] = 1 - colorArr[(size_t)node];
                        // Push the colored vertex to the corresponding group
                        groups[(size_t)colorArr[v]].push_back(v);
                        // Enqueue the vertex for further BFS
                        q.push(v);
                    }
                    // If there is an edge from the dequeued vertex to v and they have the same color
                    else if (adjMatrix[(size_t)node][v] != 0 && colorArr[v] == colorArr[(size_t)node])
                    {
                        return "Graph is not Bipartite";
                    }
                }
            }
        }
    }

    // If we reach here, then all vertices can be colored with alternate color
    // So, we return the two sets of vertices
    string result = "Graph is Bipartite and those are the two sets: ";
    result += "A={";
    for (int i = 0; i < groups[0].size(); i++)
    {
        result += to_string(groups[0][(size_t)i]);
        if (i != groups[0].size() - 1)
        {
            result += ",";
        }
    }
    result += "} B={";
    for (int i = 0; i < groups[1].size(); i++)
    {
        result += to_string(groups[1][(size_t)i]);
        if (i != groups[1].size() - 1)
        {
            result += ",";
        }
    }
    result += "}";
    return result;
}

// This function checks if a graph contains a negative cycle.
string Algorithms::negativeCycle(Graph &graph)
{

    if (graph.getWeightsType() != -1)
    {
        return "Graph does not contain a negative cycle";
    }

    // If the graph is already marked as containing a negative cycle, return the result immediately.
    if (graph.getContainsNegativeCycle())
    {
        return "Negative cycle detected";
    }

    // Use the bellman ford algorithm to detect a negative cycle.
    string helper = Algorithms::shortestPath(graph, 0, 0);

    // If the shortestPath function did not detect a negative cycle, return the result.
    if (helper != "Negative cycle detected")
    {
        return "Graph does not contain a negative cycle";
    }

    // If a negative cycle was detected, return the result.
    return helper;
}
