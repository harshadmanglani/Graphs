#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "graph.h"
#include "graphexamples.h"
using namespace std;

// change this to false to turn off debug print statements
bool debug = true;

bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
    return a.second < b.second;
}

class KruskalMST
{
    Graph *graph;
    int v;

    public:
    KruskalMST(Graph *graph)
    {
        this->graph = graph;
        v = graph->returnV();
    }

    void runKruskalAndPrintMST()
    {
        vector<pair<pair<int, int>, int>> edges = graph->generateEdgeList();
        Graph MST(v);
        sort(edges.begin(), edges.end(), cmp);
        auto it = edges.begin();
        int numberOfEdges = 0;
        while(numberOfEdges != this->v - 1)
        {
            int u = it->first.first;
            int v = it->first.second;
            int weight = it->second;
            // NOTE: this is a weird hack, we convert edges from an undirected graph to a directed graph in code to make this work.
            MST.addDirectedEdge(u, v, weight);
            numberOfEdges++;
            if(debug)
                cout<<u<<" -> "<<v<<": "<<weight<<" added";
            if(MST.detectCycles())
            {
                MST.removeDirectedEdge(u, v);
                numberOfEdges--;
                cout<<" and then removed.";
            }
            cout<<endl;
            ++it;
        }
    }

};


int main()
{
    // NOTE: pass undirected graphs only
    KruskalMST obj(graphA());
    obj.runKruskalAndPrintMST();
    return 0;
}