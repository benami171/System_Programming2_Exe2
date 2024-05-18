#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    ariel::Graph g4;
    g4.loadGraph(expectedGraph);
    CHECK((g3 == g4));
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g5.loadGraph(graph2);
    ariel::Graph g6;
    vector<vector<int>> weightedGraph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g6.loadGraph(weightedGraph2);
    ariel::Graph g7 = g5 + g6;

    vector<vector<int>> expectedGraph2 = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    ariel::Graph g8;
    g8.loadGraph(expectedGraph2);
    CHECK(g7 == g8);

    SUBCASE("Test graph addition with assignment")
    {
        g1 += g2;
        CHECK((g1 == g4) == true);
        CHECK((g1 != g3) == false);
    }

    SUBCASE("Test unary +")
    {
        ariel::Graph g5 = +g1;
        CHECK((g5 == g1) == true);
    }

    SUBCASE("Addition of two graphs with different dimensions")
    {
        ariel::Graph g6;
        vector<vector<int>> graph2 = {
            {0, 5, 0, 0, 7, 5},
            {1, 0, 1, 8, 0, 5},
            {0, 5, 0, 1, 0, 5},
            {0, 0, 1, 0, 1, 5},
            {7, 0, 0, 1, 0, 5},
            {5, 5, 5, 5, 5, 0}};
        g6.loadGraph(graph2);
        CHECK_THROWS(g1 + g6);
        CHECK_THROWS(g1 += g6);
    }

    SUBCASE("Test algorithms")
    {
        CHECK(g3.getIsDirected() == false);
        CHECK(ariel::Algorithms::isConnected(g3) == true);
        CHECK(ariel::Algorithms::isContainsCycle(g3) != "0");
        CHECK(ariel::Algorithms::isBipartite(g3) == "Graph is not Bipartite");
        CHECK(ariel::Algorithms::shortestPath(g3, 1, 2) == "1->2");
    }
}
TEST_CASE("Test graph subtraction")
{

    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    ariel::Graph g1;
    g1.loadGraph(graph);
    vector<vector<int>> graph2 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    ariel::Graph g2;
    g2.loadGraph(graph2);
    ariel::Graph g3 = g2 - g1;

    vector<vector<int>> negativeGraph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};

    ariel::Graph g4;
    g4.loadGraph(negativeGraph);
    CHECK((g3 == g1) == true);

    SUBCASE("Test subtraction with assignment")
    {
        g2 -= g1;
        CHECK((g2 == g1) == true);
        CHECK((g2 != g3) == false);
    }

    SUBCASE("Test unary -")
    {
        ariel::Graph g5 = -g1;
        CHECK((g5 == g4) == false);
    }

    SUBCASE("Subtraction of two graphs with different dimensions")
    {
        ariel::Graph g6;
        vector<vector<int>> graph2 = {
            {0, 5, 0, 0, 7, 5},
            {1, 0, 1, 8, 0, 5},
            {0, 5, 0, 1, 0, 5},
            {0, 0, 1, 0, 1, 5},
            {7, 0, 0, 1, 0, 5},
            {5, 5, 5, 5, 5, 0}};
        g6.loadGraph(graph2);
        CHECK_THROWS(g1 - g6);
        CHECK_THROWS(g1 -= g6);
    }
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    ariel::Graph g5;
    g5.loadGraph(expectedGraph);
    CHECK((g4 == g5) == true);

    SUBCASE("Test graph multiplication with scalar both ways")
    {
        ariel::Graph g6 = g1 * 2;
        ariel::Graph g7 = 2 * g1;
        vector<vector<int>> expectedGraph2 = {
            {0, 2, 0},
            {2, 0, 2},
            {0, 2, 0}};
        ariel::Graph g8;
        g8.loadGraph(expectedGraph2);

        CHECK((g6 == g8) == true);
        CHECK((g7 == g8) == true);

        ariel::Graph g2 = g1 * 2;
        g2 = -2 * g2;
        vector<vector<int>> expectedGraph = {
            { 0,-4, 0},
            {-4, 0,-4},
            { 0,-4, 0}};
        ariel::Graph g13;
        g13.loadGraph(expectedGraph);
        CHECK((g2 == g13) == true);
    }

    SUBCASE("Multiplication of two graphs with different dimensions")
    {
        ariel::Graph g9;
        vector<vector<int>> graph2 = {
            {0, 5, 0, 0, 7, 5},
            {1, 0, 1, 8, 0, 5},
            {0, 5, 0, 1, 0, 5},
            {0, 0, 1, 0, 1, 5},
            {7, 0, 0, 1, 0, 5},
            {5, 5, 5, 5, 5, 0}};
        g9.loadGraph(graph2);
        CHECK_THROWS(g1 * g9);
    }

    SUBCASE("Test graph multiplication with scalar assignments")
    {
        ariel::Graph g11;
        ariel::Graph g12;
        vector<vector<int>> graph2 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};

        vector<vector<int>> graph3 = {
            {0, 2, 0},
            {2, 0, 2},
            {0, 2, 0}};
        g11.loadGraph(graph2);
        g12.loadGraph(graph3);
        g11 *= 2;
        CHECK((g11 == g12) == true);
    }
}

TEST_CASE("Test Graph division")
{
    vector<vector<int>> graph = {
        {0, 4, 0},
        {2, 0, 2},
        {0, 4, 0}};
    ariel::Graph g1;
    g1.loadGraph(graph);

    g1 /= 2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 0},
        {1, 0, 1},
        {0, 2, 0}};

    ariel::Graph g2;
    g2.loadGraph(expectedGraph);
    CHECK((g1 == g2) == true);  

}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}

TEST_CASE("Test Increment and Decrement operators")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 0, 1},
        {1, 0, 0},
        {0, 1, 0}};
    vector<vector<int>> graph2 = {
        {0, 0, 3},
        {3, 0, 0},
        {0, 3, 0}};
    vector<vector<int>> graph3 = {
        {0, 0, 1},
        {1, 0, 0},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    g2.loadGraph(graph2);
    ariel::Graph g3;
    g3.loadGraph(graph3);
    g1++;
    ++g1;
    CHECK((g1 == g2) == true); // supposed to be equal, ++ on zero matrix is still zero matrix

    g1--;
    --g1;
    CHECK((g1 == g3) == true); // supposed to be equal, -- on zero matrix is still zero matrix

    ariel::Graph g4;
    vector<vector<int>> zeroMat = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g4.loadGraph(zeroMat);
    ariel::Graph g5;
    g5.loadGraph(zeroMat);
    g5++;
    ++g5;
    CHECK((g4 == g5) == true); // supposed to be equal, ++ on zero matrix is still zero matrix
}