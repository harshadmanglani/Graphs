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
    void BFSUtil(queue<int> bfs, vector<bool>& visited);
    bool DFSUtil(int node, vector<int>& visited, bool cycleDetection);
    void printAllTopologicalSortsUtil(vector<bool> &visited, vector<int> &indegrees, vector<int>& result);
    public:
    Graph(int v)
    {
        this->v = v;
        nodes = new map<int, int>[v];
    }

    bool addDirectedEdge(int A, int B, int weight);
    bool addUndirectedEdge(int A, int B, int weight);
    map<int, int> returnNeighbors(int index);
    int returnWeight(int u, int v);
    vector<pair<pair<int, int>, int>> generateEdgeList();
    void removeDirectedEdge(int A, int B);
    void removeUndirectedEdge(int A, int B);
    bool printDFS(bool cycleDetection);
    void printBFS();
    int returnV();
    bool detectCycles();
    void printTopologicalSort();
    void printAllTopologicalSorts();
    bool isBipartite();
};

bool Graph::addDirectedEdge(int A, int B, int weight = 0)
{
    nodes[A].insert({B, weight});
    return true;
}

bool Graph::addUndirectedEdge(int A, int B, int weight = 0)
{
    this->addDirectedEdge(A, B, weight);
    this->addDirectedEdge(B, A, weight);
    return true;
}

/// returns neighbors for a node in the form {neighbor_node, weight}
map<int, int> Graph::returnNeighbors(int index)
{
    return nodes[index];
}

int Graph::returnWeight(int u, int v)
{
    map<int, int> neighbors = nodes[u];
    if(neighbors.find(v) == neighbors.end())
        return INT_MIN;
    return neighbors[v];
}

vector<pair<pair<int, int>, int>> Graph::generateEdgeList()
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

void Graph::removeDirectedEdge(int A, int B)
{
    nodes[A].erase(B);
}

void Graph::removeUndirectedEdge(int A, int B)
{
    removeDirectedEdge(A, B);
    removeDirectedEdge(B, A);
}

bool Graph::printDFS(bool cycleDetection=false)
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

bool Graph::DFSUtil(int node, vector<int>& visited, bool cycleDetection=false)
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
            return true;
    }
    visited[node] = 2;
    return false;
}

void Graph::printBFS()
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

void Graph::BFSUtil(queue<int> bfs, vector<bool>& visited)
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

int Graph::returnV()
{
    return this->v;
}

bool Graph::detectCycles()
{
    return printDFS(true);
}

/// Time Complexity: O(v)
/// Space Complexity: O(v+e)
void Graph::printTopologicalSort()
{
    // DFS with stack is an easy implementation - instead of printing the current vertex, push it in a stack
    // and empty the stack when DFS is over. The following algorithm follows a different approach - Kahn's algorithm.
    // 1. compute the indegree for each node and initialize the count of visited nodes as visited_count = 0
    // 2. pick all the nodes with a 0-indegree and add them in a queue
    // 3. dequeue, increment visisted_count, decrement indegrees of neighbors by 1 and if they become 0, enqueue them
    // 4. repeat step 2 until the queue is empty
    // 5. if visisted_count != v, a cycle exists - exit

    vector<int> indegrees(this->v, 0);
    vector<pair<pair<int, int>, int>> edges = this->generateEdgeList(); //O(e) space
    queue<int> zeroNodes;
    int visited_count = 0;

    // 1.
    for(int i = 0; i < edges.size(); ++i)
    {
        int dest = edges[i].first.second;
        indegrees[dest]++;
    }

    // 2. 
    for(int i = 0; i < this->v; ++i)
    {
        if(indegrees[i] == 0)
            zeroNodes.push(i);
    }

    // 3 and 4.
    while(!zeroNodes.empty())
    {
        int currentNode = zeroNodes.front();
        zeroNodes.pop();
        cout<<currentNode<<" ";
        visited_count++;

        map<int, int> neighbors = this->returnNeighbors(currentNode);
        for(auto it = neighbors.begin(); it != neighbors.end(); ++it)
        {
            indegrees[it->first]--;
            if(indegrees[it->first] == 0)
                zeroNodes.push(it->first);
        }
    }

    // 5.
    if(visited_count < this->v)
    {
        cout<<"A cycle exists..\n. Aborting.";
        return;
    }
}

void Graph::printAllTopologicalSorts()
{
    // 1. initialize all nodes as unvisited.
    // 2. choose an unvisited node with 0 indegree and mark it as visited.
    // 3. decrement indegrees of the chosen node's neighbors 
    // 4. call the recursive function again 
    // 5. backtrack, reset values and try other possibilities

    // 1.
    vector<int> indegrees(this->v, 0);
    vector<bool> visited(this->v, false);
    vector<pair<pair<int, int>, int>> edges = this->generateEdgeList();
    vector<int> result;
    for(int i = 0; i < edges.size(); ++i)
    {
        int dest = edges[i].first.second;
        indegrees[dest]++;
    }

    printAllTopologicalSortsUtil(visited, indegrees, result);
}

void Graph::printAllTopologicalSortsUtil(vector<bool> &visited, vector<int> &indegrees, vector<int>& result)
{
    bool flag = false;

    for(int i = 0; i < this->v; ++i)
    {
        if(indegrees[i] == 0 && !visited[i])
        {
            // decrement neighbors
            map<int, int> neighbors = this->returnNeighbors(i);
            for(auto it = neighbors.begin(); it != neighbors.end(); ++it)
            {
                indegrees[it->first]--;
            }
            
            // visit
            visited[i] = true;
            
            // add to the result
            result.push_back(i);
            printAllTopologicalSortsUtil(visited, indegrees, result);

            // undo - remove from the result
            result.erase(result.end()-1);

            // undo - unvisit
            visited[i] = false;

            // undo - increment neighbors
            for(auto it = neighbors.begin(); it != neighbors.end(); ++it)
            {
                indegrees[it->first]++;
            }
            flag = true;
        }
    }

    if(!flag)
    {
        for(int i = 0; i < result.size(); ++i)
            cout<<result[i]<<" ";
        cout<<"\n";
    }
}
#endif