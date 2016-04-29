#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;
 
// Number of vertices in given graph
#define V 8
 
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));
 
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}
 
// max flow from s to t
int fordFulkerson(int graph[V][V], int s, int t)
{
    int u, v;
 
    int rGraph[V][V];
    
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];
 
    int parent[V];
 
    int max_flow = 0;
 
    while (bfs(rGraph, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
       max_flow += path_flow;
    }
   
    // Return the overall flow
    return max_flow;
}
 
// Driver program to test above functions
int main()
{
    // Let us create a graph shown in the above example
    int graph[V][V] = { {0, 10, 5, 15, 0, 0, 0, 0},
                        {0, 0, 4, 0, 9, 15, 0, 0},
                        {0, 0, 0, 4, 0, 8, 0, 0},
                        {0, 0, 0, 0, 0, 0, 30, 0},
                        {0, 0, 0, 0, 0, 15, 0, 10},
                        {0, 0, 0, 0, 0, 0, 15, 10},
                        {0, 0, 6, 0, 0, 0, 0, 10},
                        {0, 0, 0, 0, 0, 0, 0, 0}
                      };
 
    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 7);
   return 0;
}
