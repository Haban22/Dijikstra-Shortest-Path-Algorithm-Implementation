#include <iostream>
#include <fstream>
#include <climits>
#include "MinHeap.h"

using namespace std;

class WeightedGraph
{
int** g;
int nVertices;
public:
int getNVertices() //returns the number of vertices
{
    return nVertices;
}

int getWeight(char v1,char v2)//returns the weight of the edge between the vertices v1 and v2
{
    return g[v1-'a'][v2-'a'];
}

int* returnNeighbors(int v)// returns the indices of the neighbors of the vertex v as an int array
{
    int* neighbors = new int[numNeighbors(v)];
    int count = 0;
    for (int i = 0; i < nVertices; i++)
    {
        if (g[v][i] != 0)
        {
            neighbors[count] = i;
            count++;
        }
    }
    return neighbors;
}

int numNeighbors(int v)//returns the number of neighbors of the vertex v
{
    int count = 0;
    for (int i = 0; i < nVertices; i++)
    {
        if (g[v][i] != 0)
        {
            count++;
        }
    }
    return count;
}

void loadGraphFromFile(ifstream& infile)//allocates the adjacency matrix & initializes edge weights from the specified file
{
    infile >> nVertices;
    int nEdges;
    infile >> nEdges;
    
    g = new int*[nVertices];

    for(int i = 0; i < nVertices; i++)
    {
        g[i] = new int[nVertices];
        for(int j = 0; j < nVertices; j++)
        {
            g[i][j] = 0;
        }
    }
    
    char v1, v2;
    int weight;
    for(int i = 0; i < nEdges; i++)
    {
        infile >> v1 >> v2 >> weight;
        g[v1 - 'a'][v2 - 'a'] = weight;
    }
}

void dijkstra(char startVertex, char* prev, Node distances[]) 
{
    MinHeap minHeap(nVertices);

    for (int i = 0; i < nVertices; ++i) 
    {
        distances[i].label = 'a' + i;   
        distances[i].cost = (startVertex - 'a' == i) ? 0 : INT_MAX;
        prev[i] = ' ';
        minHeap.insert(distances[i]);
    }

    while (!minHeap.isEmpty()) 
    {
        Node u = minHeap.extractMin();
        int uIndex = u.label - 'a';

        int* neighbors = returnNeighbors(uIndex);
        int neighborCount = numNeighbors(uIndex);

        for (int i = 0; i < neighborCount; ++i) 
        {
            int vIndex = neighbors[i];
            if (g[uIndex][vIndex] == INT_MAX) continue;
            int alt = u.cost + g[uIndex][vIndex];

            if (alt < distances[vIndex].cost) 
            {
                distances[vIndex].cost = alt;
                prev[vIndex] = u.label;
                minHeap.decreaseKey('a' + vIndex, alt);
            }
        }

        delete[] neighbors;
    }    
}
};