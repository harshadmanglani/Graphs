#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

bool debug = true;
//adjacency list
//an array of linked lists or an array of dynamic arrays


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

    vector<pair<int, int>> generateEdgeList()
    {
        vector<pair<int, int>> edges;
        for(int i = 0; i < v; ++i)
        {
            for(map<int, int>::iterator it = nodes[i].begin(); it != nodes[i].end(); ++it)
            {
                edges.push_back({i, it->first});
            }
        }
        return edges;
    }

    //TODO: come back to this

    // bool removeDirectedEdge(int A, int B)
    // {
    //     Node *src = this->nodes[A];
    //     Node *dest = this->nodes[B];
    //     src->removeNeighbor(dest);
    //     return true;
    // }

    // bool removeUndirectedEdge(int A, int B)
    // {
    //     this->removeDirectedEdge(A, B);
    //     this->removeDirectedEdge(B, A);
    //     return true;
    // }

    void printDFS()
    {
        vector<bool> visited(v, false);
        cout<<"Depth First Search:\n";
        for(int i = 0; i < v; ++i)
        {
            DFSUtil(i, visited);
        }
    }

    void DFSUtil(int node, vector<bool>& visited)
    {
        if(visited[node])
            return;

        //visit
        visited[node] = true;
        cout<<node<<" ";
        //traverse the depth
        for(auto it = nodes[node].begin(); it != nodes[node].end(); ++it)
        {
            // DFSUtil(neighbor, visited);
            DFSUtil(it->first, visited);
        }
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
        return true;
    }
};

Graph* graphA()
{

    // does not have negative weights or cycles
    // Djikstra output
    // Vertex   Distance from Source
    // 0                0
    // 1                4
    // 2                12
    // 3                19
    // 4                21
    // 5                11
    // 6                9
    // 7                8
    // 8                14

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

    // has negative weights but no cycles
    // Bellman Ford output
    // Vertex   Distance from Source
    // 0            0
    // 1            1
    // 2            3
    // 3            5
    // 4            0
    // 5            4
    // 6            3

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
    // has negative weights and a negative weight cycle
    // Bellman Ford needs to handle this graph gracefully

    Graph *graph = new Graph(4);
    graph->addDirectedEdge(0, 1, 4);
    graph->addDirectedEdge(0, 3, 5);
    graph->addDirectedEdge(3, 2, 3);
    graph->addDirectedEdge(2, 1, -10);
    graph->addDirectedEdge(1, 3, 5);
    return graph;
}

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
        // TODO: add check to call runDjikstrasAlgorithm before calling printCostTable
        for(int i = 0; i < distanceVector.size(); ++i)
        {
            cout<<i<<" : "<<distanceVector[i]<<endl;
        }
    }
};

// Doesn't work when a negative weight cycle is present
class BellmanFord{
    Graph *graph;
    int v;
    vector<int> distanceVector;

    public:
    BellmanFord()
    {
        initialiseGraph();
        initialiseDistanceVector();
    }

    BellmanFord(Graph *graph)
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
        graph = graphB();
        v = graph->returnV();
        for(int i = 0; i < v; ++i)
        {
            map<int, int> neighbors = graph->returnNeighbors(i);
            if(debug)
            cout<<"node: "<<i<<" neighbors: "<<neighbors.size()<<endl;
        }
    }

    void runBellmanFordAlgorithm()
    {
        vector<pair<int, int>> edges = graph->generateEdgeList();
        bool updateFlag = true;
        for(int r = 0; r < v - 1; ++r)
        {
            // stop looping when you reach the final set of distances
            if(!updateFlag)
                break;
            updateFlag = false;
            for(int i = 0; i < edges.size(); ++i)
            {
                int u = edges[i].first;
                int v = edges[i].second;
                if(debug)
                cout<<"edge: "<<u<<"->"<<v<<endl;
                int weight = graph->returnWeight(u, v);
                if(weight == INT_MIN)
                {
                    cout<<"An error occured.\n";
                    return;
                }
                if(distanceVector[u] + weight < distanceVector[v])
                {
                    distanceVector[v] = distanceVector[u] + weight;
                    updateFlag = true;
                }
            }
        }
        if(negativeCycleCheck(edges))
        {
            cout<<"Negative cycle detected. Discarding weights.\n";
            distanceVector.clear();
        }
    }

    // TODO: this isn't working right
    bool negativeCycleCheck(vector<pair<int, int>> edges)
    {
        for(int i = 0; i < edges.size(); ++i)
        {
            int u = edges[i].first;
            int v = edges[i].second;
            if(debug)
            cout<<"edge: "<<u<<"->"<<v<<endl;
            int weight = graph->returnWeight(u, v);
            if(weight == INT_MIN)
            {
                cout<<"An error occured.Aborting.\n";
                return true;
            }
            if(distanceVector[u] + weight < distanceVector[v])
            {
                // negative cycle
                return true;
            }
        }
        return false;
    }

    void printCostTable()
    {
        // TODO: add check to call runDjikstrasAlgorithm before calling printCostTable
        for(int i = 0; i < distanceVector.size(); ++i)
        {
            cout<<i<<" : "<<distanceVector[i]<<endl;
        }
    }

};


int main()
{
    // Uncomment the below line to turn off debugging.
    // debug = false;
    BellmanFord obj(graphB());
    obj.runBellmanFordAlgorithm();
    obj.printCostTable();
    // Djikstra obj(graphA());
    // obj.runDjikstrasAlgorithm();
    // obj.printCostTable();
    return 0;
}