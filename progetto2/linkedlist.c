//
// Created by mario on 04/06/2020.
//

#include "linkedlist.h"

void push(struct Node** head_ref,  char *src, char *dest, int price){

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->src = (char*)malloc((strlen(src)+1)*sizeof(char));
    new_node->dest = (char*)malloc((strlen(dest)+1)*sizeof(char));
    strcpy(new_node->src, src);
    strcpy(new_node->dest, dest);
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
    new_node->price = price;
}

void deleteNode(struct Node **head_ref, char *src, char *dest){
    struct Node* temp = *head_ref, *prev;
    // If head node itself holds the key to be deleted
    if (temp != NULL && strcpy(temp->src, src) == 0 && strcpy(temp->dest, dest) == 0){
        *head_ref = temp->next;   // Changed head
        free(temp->src);
        free(temp->dest);
        free(temp);               // free old head
        return;
    }
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && strcpy(temp->src, src) != 0 && strcpy(temp->dest, dest) != 0){
        prev = temp;
        temp = temp->next;
    }
    // If key was not present in linked list
    if (temp == NULL) return;
    // Unlink the node from linked list
    prev->next = temp->next;
    // Free memory
    free(temp->src);
    free(temp->dest);
    free(temp);
}

void printlist(struct Node* head_ref){
    // no flight
    if(head_ref == NULL){
        printf("\n\t\t\tNo flight rented");
        return;
    }
    // printing all flight
    while (head_ref){
        printf("\n\t\t\tfrom %s to %s(price:%d)",head_ref->src, head_ref->dest, head_ref->price);
        head_ref=head_ref->next;
    }

}