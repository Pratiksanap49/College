#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int source;
    int destination;
    int weight;
};

void bellmanFord(int numberOfVertices, int numberOfEdges, vector<Edge> &edges, int sourceVertex) {
    vector<int> distance(numberOfVertices, INT_MAX);
    distance[sourceVertex] = 0;

    for (int i = 1; i <= numberOfVertices - 1; i++) {
        for (int j = 0; j < numberOfEdges; j++) {
            int u = edges[j].source;
            int v = edges[j].destination;
            int w = edges[j].weight;

            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
            }
        }
    }

    // Check for negative weight cycle
    for (int j = 0; j < numberOfEdges; j++) {
        int u = edges[j].source;
        int v = edges[j].destination;
        int w = edges[j].weight;

        if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
            cout << "Graph contains a negative weight cycle!" << endl;
            return;
        }
    }

    cout << "Vertex\tDistance from Source\n";
    for (int i = 0; i < numberOfVertices; i++) {
        cout << i << "\t" << distance[i] << endl;
    }
}

int main() {
    int numberOfVertices, numberOfEdges;
    cout << "Enter the number of vertices: ";
    cin >> numberOfVertices;
    cout << "Enter the number of edges: ";
    cin >> numberOfEdges;

    vector<Edge> edges;
    
    for (int i = 0; i < numberOfEdges; i++)
    {
        int sourceVertex;
        int destinationVertex;
        int edgeweight;
        cout << "Enter source vertex of "<<i+1<<": ";
        cin >> sourceVertex;
        cout << "Enter destination vertex "<<i+1<<": ";
        cin >> destinationVertex;
        cout << "Enter edge weight "<<i+1<<": ";
        cin >> edgeweight;

        edges.push_back({sourceVertex, destinationVertex, edgeweight});
    }

    int sourceVertex;
    cout << "Enter the source vertex: ";
    cin >> sourceVertex;

    bellmanFord(numberOfVertices, numberOfEdges, edges, sourceVertex);

    return 0;
}
