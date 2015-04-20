#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef struct Node{
    int val;
    Node *next;
} Node;

Node *makeList(int v);
Node *addToHead(Node *l, int v);
void addToTail(Node *l, int v);
void addToAtN(Node *l, int v, int n);
void deleteAtN(Node *l, int n);
void changeValueAtN(Node *l, int n);
int getNumElements(Node *l);
Node *findElement(Node *l, int v);
void delList(Node *l);
void printList(Node *l);


static Node* traverseToN(Node *l, int n);

#endif
