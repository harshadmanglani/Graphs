#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "graph.h"
#include "graphexamples.h"
using namespace std;

// change this to false to turn off debug print statements
bool debug = true;

// Doesn't work when negative weights are set
class Djikstra
{
    Graph *graph;
    int v;
    vector<int> distanceVector;

    public:
    Djikstra()
    {
        initialiseGraph();
        initialiseDistanceVector();
    }

    Djikstra(Graph *graph)
    {
        this->graph = graph;
        v = graph->returnV();
        initialiseDistanceVector();
    }

    void initialiseDistanceVector()
    {
        distanceVector.push_back(0);
        for(int i = 1; i < v; ++i)
            distanceVector.push_back(INT_MAX);
    }

    void initialiseGraph()
    {
        graph = graphA();
        v = graph->returnV();
        
        for(int i = 0; i < 9; ++i)
        {
            map<int, int> neighbors = graph->returnNeighbors(i);
            if(debug)
            cout<<"node: "<<i<<" neighbors: "<<neighbors.size()<<endl;
        }
    }

    int minDistance(map<int, bool>& visited)
    {
        int minValue = INT_MAX;
        int minVertex = -1;
        for(int i = 0; i < distanceVector.size(); ++i)
        {
            if(visited.find(i) == visited.end())
                if(distanceVector[i] < minValue)
                {
                    minValue = distanceVector[i];
                    minVertex = i;
                }
        }

        return minVertex;
    }

    void runDjikstrasAlgorithm()
    {
        map<int, bool> visited;
        while(visited.size() != v)
        {
            int minVertex = minDistance(visited);
            if(debug)
            cout<<"minVertex: "<<minVertex<<endl;
            if(minVertex == -1)
            {
                cout<<"There was an error.\n";
                return;
            }
            visited.insert({minVertex, true});
            map<int, int> neighbors = graph->returnNeighbors(minVertex);
            for(auto it = neighbors.begin(); it != neighbors.end(); ++it)
            {
                int vertex = it->first;
                int distance = it->second + distanceVector[minVertex];
                if(distance < distanceVector[vertex])
                {
                    distanceVector[vertex] = distance;
                }
                if(debug)
                cout<<"updated cost for "<<vertex<<" "<<distanceVector[vertex]<<endl;
            }
        }
    }

    int returnMinCost(int index)
    {
        return distanceVector[index];
    }

    void printCostTable()
    {
        for(int i = 0; i < distanceVector.size(); ++i)
        {
            cout<<i<<" : "<<distanceVector[i]<<endl;
        }
    }
};


int main()
{
    Djikstra obj(graphA());
    obj.runDjikstrasAlgorithm();
    obj.printCostTable();
    return 0;
}