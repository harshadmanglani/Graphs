#include "graph.h"
#include "graphexamples.h"
#include <bits/stdc++.h>
using namespace std;

int main()
{
    Graph *cycleDetection = graphA();
    cout<<"Does a cycle exist? "<< cycleDetection->detectCycles();
    cout<<"\n\n\n";
    Graph *topologicalSort = graphB();
    topologicalSort->printTopologicalSort();
    cout<<"\n\n\n";
    topologicalSort->printAllTopologicalSorts();
}