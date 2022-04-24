//
// Created by mario on 01/06/2020.
//

#ifndef PROGETTO2_USERS_H
#define PROGETTO2_USERS_H
#include "linkedlist.h"
#include "heap.h"
struct User{
    char * username;
    char *password;
    int points;
    struct Node *flightlist;
};
struct User_tree{
    int height;
    struct User *user;
    struct User_tree *left;
    struct User_tree *right;
};

//create a User node
void Usernode(struct User **node, char *username, char *password );
//tree rotation and height
int nodeHeight(struct User_tree *stud);
int isBalanced(struct User_tree *stud);
void LLrotation(struct User_tree **stud);
void RRrotation(struct User_tree **stud);
void LRrotation(struct User_tree **stud);
void RLrotation(struct User_tree **stud);

//inserting a new user and password
void insertUser(struct User_tree **stud, char * username, char *password);
//helper function to find and get a User
int findUser(struct User_tree **stud, char *username, char *password);
struct User* getUser(struct User_tree **stud, char* username, char *password);
//printing functions(INORDER)
void printFlysForEachUser(struct User_tree **users);

//function for points
void addPoints(struct User **node, int points);
void deletePoints(struct User **node, int points);
int getPoints(struct User **node);
#endif //PROGETTO2_USERS_H
