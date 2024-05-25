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

        ariel::Graph g20;
        vector<vector<int>> negativeCycle = {
            {0, 1, 0},
            {1, 0, 1},
            {0, -2, 0}};
        g20.loadGraph(negativeCycle);
        vector<vector<int>> graph21 = {
            {0, 0, 1},
            {0, 0, 0},
            {0, 3, 0}};
        ariel::Graph g21;
        ariel::Graph g22;
        g21.loadGraph(graph21);
        g22 = g20 + g21; // this will cancel the negative cycle of g20
        CHECK(ariel::Algorithms::shortestPath(g20, 0, 2) == "Negative cycle detected");
        CHECK(ariel::Algorithms::shortestPath(g22, 0, 2) == "0->2");
        CHECK(ariel::Algorithms::negativeCycle(g22) == "Graph does not contain a negative cycle");
        CHECK(g3.getIsDirected() == false);
        CHECK(ariel::Algorithms::isConnected(g3) == true);
        CHECK(ariel::Algorithms::isContainsCycle(g3) != "0");
        CHECK(ariel::Algorithms::isBipartite(g3) == "Graph is not Bipartite");
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

    ariel::Graph g10;
    vector<vector<int>> graph10{
        {0, -1, 0},
        {2, 0, 1},
        {0, -3, 0}};
    g10.loadGraph(graph10);
    ariel::Graph g11;
    vector<vector<int>> expectedGraph{
        {0, 1, 0},
        {-2, 0, -1},
        {0, 3, 0}};
    g11.loadGraph(expectedGraph);

    SUBCASE("Test unary -")
    {
        ariel::Graph g12 = -g10;
        CHECK((g11 == g12) == true);
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

        // example of using shortestPath and how after subtraction it makes a shorter path available between two graphs.
        vector<vector<int>> longPath{
            {0, 2, 5},
            {8, 0, 6},
            {0, 3, 0}};
        vector<vector<int>> graph8{
            {0, 1, 0},
            {8, 0, 3},
            {0, 3, 0}};
        ariel::Graph g7;
        ariel::Graph g8;
        g7.loadGraph(longPath);
        g8.loadGraph(graph8);
        CHECK(ariel::Algorithms::shortestPath(g7, 0, 2) == "0->2");
        ariel::Graph g9 = g7 - g8;
        CHECK(ariel::Algorithms::shortestPath(g9, 0, 2) == "0->1->2");
        CHECK(ariel::Algorithms::isBipartite(g9) == "Graph is not Bipartite");
        CHECK(ariel::Algorithms::isConnected(g9) == false);
        CHECK(ariel::Algorithms::isContainsCycle(g9) == "0");
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
            {0, -4, 0},
            {-4, 0, -4},
            {0, -4, 0}};
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

    CHECK_THROWS(g1 /= 0);
    // CHECK((g1 == g2) == true); // division by zero is still the same matrix
}

TEST_CASE("Test Increment and Decrement operators")
{
    SUBCASE("prefix incremention")
    {
        ariel::Graph g1;
        vector<vector<int>> graph = {
            {0, 0, 1},
            {1, 0, 0},
            {0, 1, 0}};
        g1.loadGraph(graph);

        ariel::Graph g2;
        vector<vector<int>> expectedGraph = {
            {0, 0, 2},
            {2, 0, 0},
            {0, 2, 0}};
        g2.loadGraph(expectedGraph);

        ariel::Graph g3;
        ariel::Graph g4;
        vector<vector<int>> zeroMat = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}};
        g3.loadGraph(zeroMat);
        g4.loadGraph(zeroMat);
        ++g1;
        ++g3;
        CHECK((g1 == g2) == true);
        CHECK((g3 == g4) == true); //++ on zero matrix is still zero matrix
    }

    SUBCASE("postfix incremention")
    {
        ariel::Graph g1;
        vector<vector<int>> graph = {
            {0, 0, 1},
            {1, 0, 0},
            {0, 1, 0}};
        vector<vector<int>> graph2 = {
            {0, 0, 2},
            {2, 0, 0},
            {0, 2, 0}};

        g1.loadGraph(graph);
        ariel::Graph g2;
        g2.loadGraph(graph2);
        g1++;
        CHECK((g1 == g2) == true);

        ariel::Graph g3;
        ariel::Graph g4;
        vector<vector<int>> zeroMat = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}};
        g3.loadGraph(zeroMat);
        g4.loadGraph(zeroMat);
        g3++;

        CHECK((g3 == g4) == true); //++ on zero matrix is still zero matrix
    }
    SUBCASE("prefix reduction")
    {
        ariel::Graph g1;
        vector<vector<int>> graph = {
            {0, 0, 1},
            {1, 0, 0},
            {0, 1, 0}};
        g1.loadGraph(graph);

        ariel::Graph g2;
        vector<vector<int>> expectedGraph = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}};
        g2.loadGraph(expectedGraph);

        --g1;
        CHECK((g1 == g2) == true);
        --g1;
        CHECK((g1 == g2) == true); // -- on zero matrix is still zero matrix

        ariel::Graph g3;
        vector<vector<int>> graph3 = {
            {0, 1, 3},
            {-1, 0, 3},
            {2, -1, 0}};
        g3.loadGraph(graph3);
        CHECK((ariel::Algorithms::shortestPath(g3, 0, 2) == "0->2"));
        --g3; // causing a negative cycle in the graph
        CHECK((ariel::Algorithms::shortestPath(g3, 0, 2) == "Negative cycle detected"));
    }
    SUBCASE("postfix reduction")
    {
        ariel::Graph g1;
        vector<vector<int>> graph = {
            {0, 0, 1},
            {1, 0, 0},
            {0, 1, 0}};
        vector<vector<int>> graph2 = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}};

        g1.loadGraph(graph);
        ariel::Graph g2;
        g2.loadGraph(graph2);
        g1--;
        CHECK((g1 == g2) == true);
        g1--;
        CHECK((g1 == g2) == true); // -- on zero matrix is still zero matrix
    }
}

TEST_CASE("Test comparison operators >,<,>=,<=,==,!=")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 2, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);

    CHECK((g1 < g2) == false);
    CHECK((g1 > g2) == true); // the graphs are not contained in each other and g2 is undirected graph with less edges.
    CHECK((g1 <= g2) == false);
    CHECK((g1 >= g2) == true); // g1 > g2
    CHECK((g1 == g2) == false);
    CHECK((g1 != g2) == true);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 5},
        {0, 0}};
    g3.loadGraph(graph3);
    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 0, 5},
        {0, 0, 0},
        {5, 0, 0}};
    g4.loadGraph(graph4);
    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 1, 5},
        {0, 0, 5},
        {0, 0, 0}};
    g5.loadGraph(graph5);
    ariel::Graph g6;
    vector<vector<int>> graph6 = {
        {0, 1, 5},
        {0, 0, 0},
        {0, 0, 0}};
    g6.loadGraph(graph6);
    CHECK((g3 < g4) == true); // g4 contains g3
    CHECK((g3 < g5) == true); // g5 contains g3
    CHECK((g3 < g6) == true); // g6 does not contain g3 but it has more edges
    CHECK((g3 > g6) == false);
    CHECK((g3 <= g6) == true);
    CHECK((g3 >= g6) == false);
    CHECK((g6.isContains(g3)) == false);

    ariel::Graph g7;
    vector<vector<int>> graph7 = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g7.loadGraph(graph7);

    ariel::Graph g8;
    vector<vector<int>> graph8 = {
        {0, 1},
        {2, 0}};
    g8.loadGraph(graph8);

    ariel::Graph g9;
    vector<vector<int>> graph9 = {
        {0, 1, 0},
        {2, 0, 0},
        {0, 0, 0}};

    g9.loadGraph(graph9);
    CHECK((g9 == g8) == false);
    CHECK((g7 < g8) == true); // g8 doesnt contain g7 but it has more edges.
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
