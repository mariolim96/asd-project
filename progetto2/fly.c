//
// Created by mario on 31/05/2020.
//


#include "fly.h"
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(char* city,int dest, const int duration, int price)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->city = (char*)malloc((strlen(city)+1)*sizeof(char));
    strcpy(newNode->city,city);
    newNode->dest = dest;
    newNode->next = NULL;
    newNode->weight[0] = duration;
    newNode->weight[1] = price;
    return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(const int V,const char city[V][MAXLENCITY]){

    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    // Create an array of adjacency lists.
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
    // Initialize each adjacency list as empty by
    // making head as NULL
    int i;
    for (i = 0; i < V; i++){
        graph->array[i].city = (char*)malloc((strlen(city[i]) + 1)*sizeof(char));
        strcpy(graph->array[i].city,city[i]);
        graph->array[i].head = NULL;
        graph->array[i].visits = rand();
    }
    return graph;
}
// adding a new node into graph
void addNodeGraph(struct Graph* graph, char *city){
    graph->V=graph->V+1;
    graph->array=realloc(graph->array,(graph->V)*sizeof(struct AdjList));
    graph->array[graph->V-1].city=(char *)malloc((strlen(city)+1)*sizeof(char));
    strcpy(graph->array[graph->V-1].city,city);
    graph->array[graph->V-1].head=NULL;
    graph->array[graph->V-1].visits = rand();

}
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, const int src, int dest, char *city, const int price, const int duration){
    // Add an edge from src to city.A new node is added to the adjacency list of src.The node is added at the start
    if(checkEdge(graph, src, city, price, duration)){
        struct AdjListNode* newNode = newAdjListNode(city,dest, duration, price);
        newNode->next = graph->array[src].head;
        graph->array[src].head = newNode;
    } else{
        printf("\n\t\t\tthis air route already exist, we change duration and price");
        sleep(2);
    }

}

//See if an edge exist
int checkEdge(struct Graph* graph, const int src, const char *city, const int price, const int duration){
    struct AdjListNode *temp = graph->array[src].head;
    while(temp != NULL){
        if(strcmp(temp->city,city) == 0){
            temp->weight[0]=duration;
            temp->weight[1]=price;
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}
//deleting a node from the graph
void deleteNodeGraph(struct Graph* graph, int src,char *city){
    struct AdjListNode *temp = graph->array[src].head;
    struct AdjListNode *prec;
    //remove adjlist of temp
    while(graph->array[src].head){
        temp=graph->array[src].head;
        graph->array[src].head=graph->array[src].head->next;
        free(temp->city);
        free(temp);
    }
    //deleting the edge by moving the nodes by one and realloc
    for(int i=src+1; i < graph->V;i++){
        graph->array[i-1]=graph->array[i];
    }
    graph->V--;
    graph->array=realloc(graph->array,(graph->V)*sizeof(struct AdjList));
    //removing the edge from all other adjacency list
    for(int i = 0; i < graph->V; i++){
        deleteEdgeGraph(graph,i, city);
    }
    // changing value of dist after deleting an element
    for(int i=src; i < graph->V;i++) {
        changeEdgeDist(graph,i);
    }
}
// changing value of dist after deleting an element
void changeEdgeDist(struct Graph* graph,int src){
    for(int i = 0; i < graph->V; i++){
        if(i != src){
            struct AdjListNode *temp = graph->array[i].head;
            while (temp && strcmp(temp->city,graph->array[src].city) != 0){
                temp=temp->next;
            }
            if(temp != NULL)
                temp->dest=src;
        }
    }
}
//deleting an edge from the graph
void deleteEdgeGraph(struct Graph* graph,int src,char *dest){
    struct AdjListNode *temp = graph->array[src].head;
    struct AdjListNode *prev;
    // if the city to remove is in head
    if(temp!=NULL && strcmp(temp->city,dest) == 0){
        graph->array[src].head =  temp->next;
        free(temp->city);
        free(temp);
        return;
    }
    //if the city is in the middle or last
    while (temp!=NULL && strcmp(temp->city,dest) != 0){
        prev=temp;
        temp=temp->next;
    }
    // if the city not founded
    if(temp==NULL) return;
    //removing the city
    prev->next = temp->next;
    free(temp->city);
    free(temp);

}
// utility func to find index of a city
int findSrc(const struct AdjList* array,const int nodes,const char *city){
    //comparing city names and returning idx
    for(int i = 0; i < nodes; i++){
        if(strcmp(array[i].city,city) == 0){
            return i;
        }
    }
    return -1;
}
//find price of a route selected between two near city
int findPriceRoute(struct Graph* graph, int src, int dest){
    struct AdjListNode *temp=graph->array[src].head;
    while (temp!=NULL && temp->dest!=dest){
        temp=temp->next;
    }
    // if edge exist return the price weight
    return temp!= NULL ? temp->weight[1] : -1;
}
//adding some edge to the starter graph
void populateEdge(struct Graph* flys){
    addEdge(flys,findSrc(flys->array,flys->V,"london"),findSrc(flys->array,flys->V,"mykonos"),"mykonos",3,40);
    addEdge(flys,findSrc(flys->array,flys->V,"london"),findSrc(flys->array,flys->V,"prague"),"prague",1,80);
    addEdge(flys,findSrc(flys->array,flys->V,"mykonos"),findSrc(flys->array,flys->V,"london"),"london",4,40);
    addEdge(flys,findSrc(flys->array,flys->V,"mykonos"),findSrc(flys->array,flys->V,"barcellona"),"barcellona",4,40);
    addEdge(flys,findSrc(flys->array,flys->V,"mykonos"),findSrc(flys->array,flys->V,"prague"),"prague",8,32);
    addEdge(flys,findSrc(flys->array,flys->V,"mykonos"),findSrc(flys->array,flys->V,"crete"),"crete",31,45);
    addEdge(flys,findSrc(flys->array,flys->V,"mykonos"),findSrc(flys->array,flys->V,"naples"),"naples",45,60);
    addEdge(flys,findSrc(flys->array,flys->V,"prague"),findSrc(flys->array,flys->V,"rome"),"rome",2,90);
    addEdge(flys,findSrc(flys->array,flys->V,"prague"),findSrc(flys->array,flys->V,"crete"),"crete",34,49);
    addEdge(flys,findSrc(flys->array,flys->V,"crete"),findSrc(flys->array,flys->V,"naples"),"naples",4,40);
    addEdge(flys,findSrc(flys->array,flys->V,"crete"),findSrc(flys->array,flys->V,"berlin"),"berlin",3,30);
    addEdge(flys,findSrc(flys->array,flys->V,"naples"),findSrc(flys->array,flys->V,"rome"),"rome",30,10);
    addEdge(flys,findSrc(flys->array,flys->V,"rome"),findSrc(flys->array,flys->V,"milan"),"milan",14,40);
    addEdge(flys,findSrc(flys->array,flys->V,"milan"),findSrc(flys->array,flys->V,"crete"),"crete",11,50);
    addEdge(flys,findSrc(flys->array,flys->V,"milan"),findSrc(flys->array,flys->V,"london"),"london",6,63);
    addEdge(flys,findSrc(flys->array,flys->V,"berlin"),findSrc(flys->array,flys->V,"milan"),"milan",15,46);
    addEdge(flys,findSrc(flys->array,flys->V,"barcellona"),findSrc(flys->array,flys->V,"rome"),"rome",35,78);
    addEdge(flys,findSrc(flys->array,flys->V,"barcellona"),findSrc(flys->array,flys->V,"crete"),"crete",36,87);
    addEdge(flys,findSrc(flys->array,flys->V,"milan"),findSrc(flys->array,flys->V,"berlin"),"berlin",30,40);

    //
    addEdge(flys,findSrc(flys->array,flys->V,"naples"),findSrc(flys->array,flys->V,"new york"),"new york",12,53);
    addEdge(flys,findSrc(flys->array,flys->V,"naples"),findSrc(flys->array,flys->V,"instanbul"),"instanbul",11,56);
    addEdge(flys,findSrc(flys->array,flys->V,"naples"),findSrc(flys->array,flys->V,"kuala"),"kuala",6,34);

    addEdge(flys,findSrc(flys->array,flys->V,"antalya"),findSrc(flys->array,flys->V,"kuala"),"kuala",3,45);
    addEdge(flys,findSrc(flys->array,flys->V,"barcellona"),findSrc(flys->array,flys->V,"palermo"),"palermo",12,54);

    addEdge(flys,findSrc(flys->array,flys->V,"new york"),findSrc(flys->array,flys->V,"paris"),"paris",30,40);
    addEdge(flys,findSrc(flys->array,flys->V,"paris"),findSrc(flys->array,flys->V,"venice"),"venice",12,78);

    addEdge(flys,findSrc(flys->array,flys->V,"tokyo"),findSrc(flys->array,flys->V,"antalya"),"antalya",6,12);
    addEdge(flys,findSrc(flys->array,flys->V,"istanbul"),findSrc(flys->array,flys->V,"venice"),"venice",11,76);

    addEdge(flys,findSrc(flys->array,flys->V,"paris"),findSrc(flys->array,flys->V,"singapore"),"singapore",3,78);
    addEdge(flys,findSrc(flys->array,flys->V,"singapore"),findSrc(flys->array,flys->V,"dubai"),"dubai",12,45);
    addEdge(flys,findSrc(flys->array,flys->V,"osaka"),findSrc(flys->array,flys->V,"dubai"),"dubai",8,74);
    addEdge(flys,findSrc(flys->array,flys->V,"tokyo"),findSrc(flys->array,flys->V,"dubai"),"dubai",5,45);

    addEdge(flys,findSrc(flys->array,flys->V,"istanbul"),findSrc(flys->array,flys->V,"antalya"),"antalya",11,45);



}
// A utility function to print all flys
void printGraph(const struct Graph* graph){
    int v;
    for (v = 0; v < graph->V; v++)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n\t\t\tFlys from %s\n\t\t\t : ", graph->array[v].city);
        while (pCrawl){
            printf("->%s", pCrawl->city);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}