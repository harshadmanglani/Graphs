#ifndef GRAPHEXAMPLES_H
#define GRAPHEXAMPLES_H
#include "graph.h"

/// your standard GeeksForGeeks graph, also works for prim's and kruskal's
/// does not have negative weights or cycles
/// Djikstra output
/// Vertex   Distance from Source
/// 0................0
/// 1................4
/// 2................12
/// 3................19
/// 4................21
/// 5................11
/// 6................9
/// 7................8
/// 8................14
Graph* graphA()
{
    Graph* graph = new Graph(9);
    graph->addUndirectedEdge(0, 1, 4);
    graph->addUndirectedEdge(0, 7, 8);
    graph->addUndirectedEdge(2, 1, 8);
    graph->addUndirectedEdge(7, 1, 11);
    graph->addUndirectedEdge(7, 8, 7);
    graph->addUndirectedEdge(7, 6, 1);
    graph->addUndirectedEdge(2, 8, 2);
    graph->addUndirectedEdge(8, 6, 6);
    graph->addUndirectedEdge(2, 5, 4);
    graph->addUndirectedEdge(6, 5, 2);
    graph->addUndirectedEdge(3, 5, 14);
    graph->addUndirectedEdge(2, 3, 7);
    graph->addUndirectedEdge(3, 4, 9);
    graph->addUndirectedEdge(5, 4, 10);
    return graph;
}

Graph* graphB()
{

    /// has negative weights but no cycles
    /// Bellman Ford output
    /// Vertex   Distance from Source
    /// 0            0
    /// 1            1
    /// 2            3
    /// 3            5
    /// 4            0
    /// 5            4
    /// 6            3

    Graph *graph = new Graph(7);
    graph->addDirectedEdge(0, 2, 5);
    graph->addDirectedEdge(0, 3, 5);
    graph->addDirectedEdge(0, 1, 6);
    graph->addDirectedEdge(1, 4, -1);
    graph->addDirectedEdge(2, 1, -2);
    graph->addDirectedEdge(2, 4, 1);
    graph->addDirectedEdge(3, 2, -2);
    graph->addDirectedEdge(3, 5, -1);
    graph->addDirectedEdge(5, 6, 3);
    graph->addDirectedEdge(4, 6, 3);
    return graph;
}

Graph* graphC()
{
    /// has negative weights and a negative weight cycle
    /// Bellman Ford needs to handle this graph gracefully

    Graph *graph = new Graph(4);
    graph->addDirectedEdge(0, 1, 4);
    graph->addDirectedEdge(0, 3, 5);
    graph->addDirectedEdge(3, 2, 3);
    graph->addDirectedEdge(2, 1, -10);
    graph->addDirectedEdge(1, 3, 5);
    return graph;
}

Graph* graphD()
{
    /// Traveling salesman
    /// Minimum weight Hamiltonian Cycle = 80
    
    Graph *graph = new Graph(4);
    graph->addUndirectedEdge(0, 1, 10);
    graph->addUndirectedEdge(0, 2, 15);
    graph->addUndirectedEdge(2, 1, 35);
    graph->addUndirectedEdge(0, 3, 20);
    graph->addUndirectedEdge(3, 1, 25);
    graph->addUndirectedEdge(3, 2, 30);
    return graph;
}

Graph *graphE()
{
    Graph *graph = new Graph(4);
    graph->addDirectedEdge(0, 1, 10);
    graph->addDirectedEdge(0, 2, 15);
    graph->addDirectedEdge(0, 3, 20);
    graph->addDirectedEdge(1, 0, 5);
    graph->addDirectedEdge(1, 2, 9);
    graph->addDirectedEdge(1, 3, 10);
    graph->addDirectedEdge(2, 0, 6);
    graph->addDirectedEdge(2, 1, 13);
    graph->addDirectedEdge(2, 3, 12);
    graph->addDirectedEdge(3, 0, 8);
    graph->addDirectedEdge(3, 1, 8);
    graph->addDirectedEdge(3, 2, 9);
    return graph;
}

Graph *graphWithCycle()
{
    Graph *graph = new Graph(4);
    graph->addDirectedEdge(0, 1, 10);
    graph->addDirectedEdge(1, 2, 10);
    graph->addDirectedEdge(2, 3, 10);
    graph->addDirectedEdge(3, 1, 10);
    return graph;
}
#endif