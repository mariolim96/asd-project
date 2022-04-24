//
// Created by mario on 01/06/2020.
//
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <unistd.h>
#include <conio.h>
#include "users.h"

void Usernode(struct User **node, char *username, char *password){
    (*node) = (struct User*)malloc(sizeof(struct User_tree));
    (*node)->username = (char*)malloc((strlen(username)+1)*sizeof(char));
    (*node)->password = (char*)malloc((strlen(password)+1)*sizeof(char));
    strcpy((*node)->username, username);
    strcpy((*node)->password, password);
    (*node)->points=0;
    (*node)->flightlist=NULL;

}
// functions for balance and height of a tree
int nodeHeight(struct User_tree *stud){
    int hl,hr;
    hl=stud && stud->left?stud->left->height:0;
    hr=stud && stud->right?stud->right->height:0;
    return hl>hr?hl+1:hr+1;
}
int isBalanced(struct User_tree *stud) {
    int hl, hr;
    hl = stud && stud->left ? stud->left->height : 0;
    hr = stud && stud->right ? stud->right->height : 0;
    return hl - hr;
}
//rotations
void LLrotation(struct User_tree**stud){
    struct User_tree *lchild=(*stud)->left;

    (*stud)->left=lchild->right; //NULL
    (*stud)->height= nodeHeight((*stud));

    lchild->right=(*stud);
    lchild->height = nodeHeight(lchild);
    (*stud) = lchild;
}//rotate right
void RRrotation(struct User_tree **stud){
    struct User_tree *lchild=(*stud)->right;

    (*stud)->right=lchild->left;
    (*stud)->height= nodeHeight(*stud);

    lchild->left=(*stud);
    lchild->height = nodeHeight(lchild);
    (*stud) = lchild;
}//rotate left
void LRrotation(struct User_tree **stud){
    RRrotation(&(*stud)->left);
    LLrotation(&(*stud));
}
void RLrotation(struct User_tree **stud){
    LLrotation(&(*stud)->right);
    RRrotation(&(*stud));
}

// inserting a User into User tree
void insertUser(struct User_tree **stud, char * username, char *password){
    if(*stud == NULL){
        *stud = (struct User_tree*) malloc(sizeof(struct User_tree));
        Usernode(&(*stud)->user, username, password);
        (*stud)->left = (*stud)->right = NULL;
        (*stud)->height=1;
        return;
    }else if(strcmp((*stud)->user->username, username)< 0){
        insertUser(&(*stud)->right, username, password);
    } else if (strcmp((*stud)->user->username, username)> 0)
        insertUser(&(*stud)->left, username,password);
    else {
       printf("\n\t\t\tUsername already exist");
       sleep(2);
       return;
    }
    (*stud)->height=nodeHeight(*stud);
    if(isBalanced(*stud) == 2 && isBalanced((*stud)->left) == 1)
        LLrotation(&(*stud));

    else if(isBalanced(*stud) == 2 && isBalanced((*stud)->left) == -1)
        LRrotation(&(*stud));

    else if(isBalanced(*stud) == -2 && isBalanced((*stud)->right) == -1)
        RRrotation(&(*stud));

    else if(isBalanced(*stud) == -2 && isBalanced((*stud)->right) == 1)
        RLrotation(&(*stud));
}

//helper function to find a User and his password
int findUser(struct User_tree **stud, char* username, char *password){
    if(*stud==NULL){
        return -1;
    }
    if(strcmp((*stud)->user->username, username)< 0){
        return findUser(&(*stud)->right, username, password);
    } else if (strcmp((*stud)->user->username, username) > 0)
        return findUser(&(*stud)->left, username, password);
    else if (strcmp((*stud)->user->username, username) == 0){
        if(strcmp((*stud)->user->password, password) == 0)
            return 1; // user and pass correct
        else return 0;//user name exist
    }
    return -1;//no user with this username
}

struct User* getUser(struct User_tree **stud, char* username, char *password){
    if(*stud==NULL){
        return NULL;
    }
    if(strcmp((*stud)->user->username, username)< 0){
        return getUser(&(*stud)->right, username, password);
    } else if (strcmp((*stud)->user->username, username) > 0)
        return getUser(&(*stud)->left, username, password);
    else if (strcmp((*stud)->user->username, username) == 0){
        if(strcmp((*stud)->user->password, password) == 0)
            return (*stud)->user;
        else return NULL;
    }
    return NULL;
}
// In order printing Users and rented flys
void printFlysForEachUser(struct User_tree **users){
    if((*users)!=NULL){
        printFlysForEachUser(&(*users)->left) ;
        if((*users)->user->username){
            printf("\n\t\t\tusername User: %s",(*users)->user->username);
            printlist((*users)->user->flightlist);
        }
        printFlysForEachUser(&(*users)->right);
    }
}

//adding, deleting  and getting points
void addPoints(struct User **node,int points){
    (*node)->points = (*node)->points + points;
}
void deletePoints(struct User **node,int points){
    (*node)->points = (*node)->points - points;
}
int getPoints(struct User **node){
    return (*node)->points;
}