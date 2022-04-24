//
// Created by mario on 01/06/2020.
//

#include "heap.h"

// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist){
    struct MinHeapNode* minHeapNode =(struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
struct MinHeap* createMinHeap(int capacity){
    struct MinHeap* minHeap =(struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =(struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b){
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap, int idx){
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
        smallest = right;

    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}
// A utility function to check if the given minHeap is empty or not
int isEmpty(struct MinHeap* minHeap){
    return minHeap->size == 0;
}
// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap){
    if (isEmpty(minHeap))
        return NULL;
    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];
    // Replace root node with last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
    return root;
}
// Function to decrease dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    // In this while see if child is less then father and swap
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
        // move to parent index
        i = (i - 1) / 2;
    }
}
// A utility function to check if a given vertex 'v' is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}

void dijkstra(struct Graph* graph, int src,  int type, int dist[],int parent[]){

    int V = graph->V;// Get the number of vertices in graph
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
    // Initialize min heap with all vertices. dist value of all vertices
    for (int v = 0; v < V; ++v){
        parent[v] = -2;
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;

    }
    // Make dist value of src vertex as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;

    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    // Initially size of min heap is equal to V
    minHeap->size = V;

    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(minHeap)){
        // Extract the vertex with minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number

        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL){
            int v = pCrawl->dest;
            // If shortest distance to v is not finalized yet, and distance to v
            // through u is less than its previously calculated distance
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight[type] + dist[u] < dist[v]){
                dist[v] = dist[u] + pCrawl->weight[type];
                parent[v] = u;
                // update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
        pCrawl = pCrawl->next;
        }
    }
    // print the calculated shortest distances
    //printArr(graph,dist, V, type);
    //printBestFly(graph,  dist, V, type);
}
//dijkstra for src and destination(the code change a bit but is the same)
void dijkstraSrcDest(struct Graph* graph, int src, int dest,  int type, int dist[], int parent[]){

    int V = graph->V;// Get the number of vertices in graph
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);

    // Initialize min heap with all vertices. dist value of all vertices
    for (int v = 0; v < V; ++v){
        parent[v] = -2;
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;

    }
    // Make dist value of src vertex as 0 so that it is extracted first
    //minHeap->array[src] = newMinHeapNode(src, dist[src]);
    //minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    // Initially size of min heap is equal to V
    minHeap->size = V;

    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(minHeap)){
        // Extract the vertex with minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number
        // if u is the destination we can stop the iteration
        if (u==dest){
            return;
        }
        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL){
            int v = pCrawl->dest;
            // If shortest distance to v is not finalized yet, and distance to v
            // through u is less than its previously calculated distance
            if (/*!sptSet[v] && */isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
                    pCrawl->weight[type] + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight[type];
                parent[v] = u;
                // update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
    // print the calculated shortest distances
    //printArr(graph,dist, V, type);
    //printBestFly(graph,  dist, V, type);
}
// A utility function used to print the solution
void printAllCities(struct Graph* graph,int src, int dist[],int prec[], int path[], int type)
{
    int pathdim;
    char types[3][20]={"duration","price"};
    printf("\n\t\t\tCities from %s | %s | path",graph->array[0].city,types[type]);
    for (int i = 1; i < graph->V; ++i){
        if (src!=i){
            findPath(src,i,prec,path,&pathdim);
            printf("\n\t\t\t%s: %d", graph->array[i].city, dist[i]);
            printPath(graph, path, pathdim);
        }
    }

        //dest=findSrc(graph->array,graph->V,g)


}
//printing best fly from src and no dest for duration ,price
int printBestFly(struct Graph* graph, int src, const int dist[], int type){

    char types[3][20]={"Shorter","Economic"};
    int j=INT_MAX;
    int idx=-1;
    for (int i = 0; i < graph->V; ++i){
        if(src != i){
            if(dist[i] != 0 && j>dist[i]){
                j=dist[i];
                idx=i;
            }
        }

    }
    if(idx == -1){
        return -1;
    }
    printf("\n\t\t\t%s flight from %s is %s(price:%d)",types[type],
                graph->array[src].city,graph->array[idx].city, j);
    return idx;
}
//best flight with city and destination
void printBestFlyCity(struct Graph* graph,int src, int dest, const int dist[], int type){
    char types[3][20]={"shorter","economic","most popular"};


    printf("\n\t\t\t%s flight from %s to %s is: %d", types[type],
            graph->array[src].city,graph->array[dest].city, dist[dest]);

}
// finding the most visited city
int printMostPopularCity(struct Graph* graph, int dist[], int src , int parent[]) {
    dijkstra(graph, src, 1, dist, parent);
    int nvisits = 0;
    int idx = -1;
    for (int i = 0; i < graph->V; ++i) {
        // if dest exist and have max n. of visits
        if (dist[i] != INT_MAX && dist[i] != 0 && nvisits < graph->array[i].visits) {
            nvisits = graph->array[i].visits;
            idx = i;
        }
    }
    if (idx != -1){
        printf("\n\t\t\tMost popular flight from %s is %s with %d visitors", graph->array[src].city,
               graph->array[idx].city, graph->array[idx].visits);
    printf("\n\t\t\tPrice of this flight is %d", dist[idx]);
    }
    else
        printf("\n\t\t\tNo popular flight from this departure");
    return idx;
}
// find the path between src and destination and his price
void findPath(int src, int dest, const int prec[], int path[],int *j){
    // if prec is defined backtrack
    int count=0;
    if(prec[dest] != -2 ){
        int u=dest;
        //backtracking all back nodes
        while( u>=0 && (prec[u] != -2 || u == src)){
            path[count] = u;
            count++;
            u=prec[u];
        }
    }
    //taking trace of path array dimension
    (*j)=count;

}
//printing path founded by find path
void printPath(struct Graph* graph, const int path[],int count){
    printf("\tPath: ");
    for(int i = count - 1; i >= 0; i--){
        printf("->%s",graph->array[path[i]].city);
    }
}
//find a price path
int findPathPrice(struct Graph* graph, const int path[],int count){
    int price=0;
    for(int i = count - 1; i > 0; i--){
        price+=findPriceRoute(graph, path[i],path[i-1]);
    }
    return price;
}

// print all city and popularity
void printCityPopularity(struct Graph* graph){
    for(int i = 0; i < graph->V; i++){
        printf("\n\t\t\t%s have %d visits", graph->array[i].city, graph->array[i].visits);
    }
}
