#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef struct Node{
    int val;
    Node *next;
} Node;

Node *makeList(int v);
Node *addToHead(Node *l, int v);
Node *addToTail(Node *l, int v);
Node *addToAtN(Node *l, int v, int n);
Node *deleteAtN(Node *l, int n);
Node *changeValueAtN(Node *l, int n);
int getNumElements(Node *l);
Node *findElement(Node *l, int v);
void delList(Node *l);
void printList(Node *l);


static Node* traverseToN(Node *l, int n);

#endif
