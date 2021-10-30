#include <algorithm>
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
using namespace std;
 
class Graph {
    int V; 
    vector<int>* adj; 
public:
    Graph(int V)
    {
        this->V = V;
        adj = new vector<int>[V];
    }
    ~Graph() { delete[] adj; }
 
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void removeEdge(int u, int v);
 
    void printEulerCircuit();
    void eulerCircuit(int s);
 

    int DFSCount(int v, bool visited[]);
 
    bool isValidNextEdge(int u, int v);
};
 
void Graph::printEulerCircuit()
{

    int u = 0;
    for (int i = 0; i < V; i++)
        if (adj[i].size() & 1) {
            u = i;
            break;
        }

    eulerCircuit(u);
    cout << endl;
}
 
void Graph::eulerCircuit(int u)
{

    vector<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;
 
        if (v != -1 && isValidNextEdge(u, v)) {
            cout << u << "-" << v << "  ";
            removeEdge(u, v);
            eulerCircuit(v);
        }
    }
}
 
bool Graph::isValidNextEdge(int u, int v)
{

    int count = 0; 
 
    for (auto i = adj[u].begin(); i != adj[u].end(); ++i)
        if (*i != -1)
            count++;
    if (count == 1)
        return true;
 
 
    bool visited[V];
    memset(visited, false, V);
    int count1 = DFSCount(u, visited);
 
    removeEdge(u, v);
    memset(visited, false, V);
    int count2 = DFSCount(u, visited);
 
    addEdge(u, v);
 
    return (count1 > count2) ? false : true;
}
 
void Graph::removeEdge(int u, int v)
{
    vector<int>::iterator iv
        = find(adj[u].begin(), adj[u].end(), v);
    *iv = -1;
 
    vector<int>::iterator iu
        = find(adj[v].begin(), adj[v].end(), u);
    *iu = -1;
}
 
int Graph::DFSCount(int v, bool visited[])
{
    visited[v] = true;
    int count = 1;
 
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
        if (*i != -1 && !visited[*i])
            count += DFSCount(*i, visited);
 
    return count;
}
 
int main()
{
    ifstream infile("fleury_input.txt");
    int N;
    infile>>N;

    Graph G1(N);

    int a, b;
    while (infile >> a >> b)
    {
        G1.addEdge(a, b);
    }

    G1.printEulerCircuit();
    return 0;
}