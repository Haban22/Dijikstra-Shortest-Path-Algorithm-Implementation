#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

struct Node 
{
    char label;
    int cost;
};

class MinHeap 
{
    Node* heap;
    int* pos;
    int _size;
    int capacity;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void swapNode(Node &a, Node &b) 
    {
        Node temp = a;
        a = b;
        b = temp;
    }

    void heapify(int i) 
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < _size && heap[l].cost < heap[smallest].cost)
            smallest = l;
        if (r < _size && heap[r].cost < heap[smallest].cost)
            smallest = r;

        if (smallest != i) 
        {
            pos[heap[i].label - 'a'] = smallest;
            pos[heap[smallest].label - 'a'] = i;
            swapNode(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }

public:
    MinHeap(int capacity) : _size(0), capacity(capacity) 
    {
        heap = new Node[capacity];
        pos = new int[capacity];
    }

    ~MinHeap() 
    {
        delete[] heap;
        delete[] pos;
    }

    bool isEmpty() 
    {
        return _size == 0;
    }

    void insert(Node node) 
    {
        if (_size == capacity) 
        {
            cout << "Heap is full" << endl;
            return;
        }
        int i = _size++;
        heap[i] = node;
        pos[node.label - 'a'] = i;
        while (i != 0 && heap[parent(i)].cost > heap[i].cost) 
        {
            pos[heap[i].label - 'a'] = parent(i);
            pos[heap[parent(i)].label - 'a'] = i;
            swapNode(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void decreaseKey(char label, int newCost) 
    {
        int i = pos[label - 'a'];
        heap[i].cost = newCost;
        while (i != 0 && heap[parent(i)].cost > heap[i].cost) {
            pos[heap[i].label - 'a'] = parent(i);
            pos[heap[parent(i)].label - 'a'] = i;
            swapNode(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    Node extractMin() 
    {
        if (_size <= 0) {
            cout << "Heap is empty" << endl;
            return Node();
        }
        if (_size == 1) {
            return heap[--_size];
        }

        Node root = heap[0];
        heap[0] = heap[--_size];
        pos[heap[0].label - 'a'] = 0;
        heapify(0);

        return root;
    }
};
#endif