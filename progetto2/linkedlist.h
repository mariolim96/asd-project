//
// Created by mario on 04/06/2020.
//

#ifndef PROGETTO2_LINKEDLIST_H
#define PROGETTO2_LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node
{
    char *src;//start city
    char *dest;//destination city
    int price;
    struct Node *next;
};

//linked list function
void push(struct Node** head_ref, char *src, char *dest, int price);
void deleteNode(struct Node **head_ref, char *src, char *dest);
void printlist(struct Node* head_ref);
#endif //PROGETTO2_LINKEDLIST_H
