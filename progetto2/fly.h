//
// Created by mario on 31/05/2020.
//
#ifndef PROGETTO2_FLY_H
#define PROGETTO2_FLY_H
#define MAXLENCITY 25
#define un unsigned
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// A structure to represent an adjacency list node
struct AdjListNode
{   int dest;//number associated to city
    char *city;// destination city name
    int weight[2];//0:duration,1:price
    struct AdjListNode* next;
};

// A structure to represent an adjacency list
struct AdjList{
    char * city;//city name
    int visits;//number time user rent a fly to this city
    struct AdjListNode *head;//head of a node
};
// A structure to represent a graph of all flys.
// Size of array will be V (number of vertices in graph)
struct Graph{
    int V;
    struct AdjList *array;//list of all nodes
};

// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(char* city, int dest, int duration, int price);
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V,const char city[V][MAXLENCITY]);
// adding a new node into graph
void addNodeGraph(struct Graph* graph, char *city);
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, char* city, int price, int duration);
//deleting a node from the graph
void deleteNodeGraph(struct Graph* graph,int src, char* city);
// utility func to find index of a city
int findSrc(const struct AdjList* array,int nodes,const char *city);
//See if an edge exist
int checkEdge(struct Graph* graph, int src, const char* dest, int price, int duration );
//deleting an edge from the graph
void deleteEdgeGraph(struct Graph* graph,int src,char *dest);
// changing value of dist after deleting an element
void changeEdgeDist(struct Graph* graph,int src);
// A utility function to print all flys
void printGraph(const struct Graph* graph);
//adding some edge to the starter graph
void populateEdge(struct Graph* graph);
//find price of a route selected between two near city
int findPriceRoute(struct Graph* graph, int src, int dest);

#endif //PROGETTO2_FLY_H
