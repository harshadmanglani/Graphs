#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

// adjacency list implementation
// an array of maps where:
// key: <source, dest>
// value: weight


class Graph
{
    map<int, int> *nodes;
    int v;

    public:
    Graph(int v)
    {
        this->v = v;
        nodes = new map<int, int>[v];
    }

    bool addDirectedEdge(int A, int B, int weight = 0)
    {
        nodes[A].insert({B, weight});
        return true;
    }

    bool addUndirectedEdge(int A, int B, int weight = 0)
    {
        this->addDirectedEdge(A, B, weight);
        this->addDirectedEdge(B, A, weight);
        return true;
    }

    map<int, int> returnNeighbors(int index)
    {
        return nodes[index];
    }

    int returnWeight(int u, int v)
    {
        map<int, int> neighbors = nodes[u];
        if(neighbors.find(v) == neighbors.end())
            return INT_MIN;
        return neighbors[v];
    }

    vector<pair<pair<int, int>, int>> generateEdgeList()
    {
        vector<pair<pair<int, int>, int>> edges;
        for(int i = 0; i < v; ++i)
        {
            for(map<int, int>::iterator it = nodes[i].begin(); it != nodes[i].end(); ++it)
            {
                edges.push_back({{i, it->first}, it->second});
            }
        }
        return edges;
    }

    void removeDirectedEdge(int A, int B)
    {
        nodes[A].erase(B);
    }

    void removeUndirectedEdge(int A, int B)
    {
        removeDirectedEdge(A, B);
        removeDirectedEdge(B, A);
    }

    bool printDFS(bool cycleDetection=false)
    {
        vector<int> visited(v, 0);
        // 0 : unvisited
        // 1 : visiting
        // 2 : visited
        if(!cycleDetection)
        cout<<"Depth First Search:\n";
        for(int i = 0; i < v; ++i)
        {
            if(DFSUtil(i, visited, cycleDetection))
                return true;
        }
        return false;
    }

    bool DFSUtil(int node, vector<int>& visited, bool cycleDetection=false)
    {
        if(visited[node] == 1)
            return true;
        //visit
        visited[node] = 1;
        if(!cycleDetection)
        cout<<node<<" ";
        //traverse the depth
        for(auto it = nodes[node].begin(); it != nodes[node].end(); ++it)
        {
            // DFSUtil(neighbor, visited);
            if(visited[it->first] != 2 && DFSUtil(it->first, visited, cycleDetection))
                return false;
        }
        visited[node] = 2;
        return false;
    }

    void printBFS()
    {
        queue<int> bfs;
        vector<bool> visited(v, false);
        cout<<"Breadth First Search:\n";
        for(int i = 0; i < v; ++i)
        {
            if(!visited[i])
            {
                bfs.push(i);
                BFSUtil(bfs, visited);
            }
        }
    }

    void BFSUtil(queue<int> bfs, vector<bool>& visited)
    {
        while(!bfs.empty())
        {
            int node = bfs.front();
            bfs.pop();
            //visit node
            if(visited[node])
                continue;
        
            visited[node] = true;
            cout<<node<<" ";
            for(auto it = nodes[node].begin(); it != nodes[node].end(); ++it)
            {
                if(!visited[it->first])
                    bfs.push(it->first);
            }
        }
    }

    int returnV()
    {
        return this->v;
    }

    bool detectCycles()
    {
        return printDFS(true);
    }
};

#endif