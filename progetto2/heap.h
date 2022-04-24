//
// Created by mario on 01/06/2020.
//

#ifndef PROGETTO2_HEAP_H
#define PROGETTO2_HEAP_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "fly.h"
// Structure to represent a min heap

struct MinHeapNode
{
    int  v;
    int dist;
};
struct MinHeap
{
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array;
};
// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist);
// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity);
// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
//A standard function to heapify at given idx
void minHeapify(struct MinHeap* minHeap, int idx);
// A utility function to check if the given minHeap is empty or not
int isEmpty(struct MinHeap* minHeap);
// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
// Function to decrease dist value of a given vertex v. This function
void decreaseKey(struct MinHeap* minHeap, int v, int dist);
// A utility function to check if a given vertex 'v' is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int v);
// A utility function used to print the solution
void printAllCities(struct Graph* graph,int src, int dist[],int prec[], int path[], int type);
//dijkstra algorithm for shortest path
void dijkstra(struct Graph* graph, int src, int type, int dist[],int parent[]);
//dijkstra algorithm for shortest path from source and destination
void dijkstraSrcDest(struct Graph* graph, int src, int dest, int type, int dist[], int parent[]);
//printing best fly from src and no dest for duration ,price
int  printBestFly(struct Graph* graph, int src, const int dist[], int type);
//best flight with city and destination
void printBestFlyCity(struct Graph* graph,int src, int dest, const int dist[], int type);
// finding the most visited city
int printMostPopularCity(struct Graph* graph, int dist[], int src, int parent[]);
// find the path between src and destination
void findPath(int src, int dest, const int prec[], int path[], int *count);
//printing path founded by find path
void printPath(struct Graph* graph, const int path[],int count);
//find a price path
int findPathPrice(struct Graph* graph, const int path[],int count);
// print all city and popularity
void printCityPopularity(struct Graph* graph);
#endif //PROGETTO2_HEAP_H
