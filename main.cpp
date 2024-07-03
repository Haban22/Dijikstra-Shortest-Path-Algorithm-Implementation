#include <iostream>
#include <fstream>
#include <climits>
#include "MinHeap.h"
#include "WeightedGraph.h"


using namespace std;

int main() {
    ifstream file("graph.txt");
    if (!file.is_open()) 
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    WeightedGraph graph;
    graph.loadGraphFromFile(file);

    string start;
    file >> start;
    
    char startVertex;
    file >> startVertex;

    Node* distances = new Node[graph.getNVertices()];
    char* prev = new char[graph.getNVertices()];

    graph.dijkstra(startVertex, prev, distances);

    cout << "Node\tCost\tPrevious" << endl;
    for (int i = 0; i < graph.getNVertices(); ++i) 
    {
        cout << distances[i].label << "\t" << distances[i].cost << "\t" << prev[i] << endl;
    }

    delete[] distances;
    delete[] prev;

    return 0;
}