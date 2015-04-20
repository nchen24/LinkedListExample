#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef struct Node{
    int val;
    Node *next;
} Node;

Node *makeList(int v);                  // #1
Node *addToHead(Node *l, int v);        // #3
Node *addToTail(Node *l, int v);        // #7
Node *addToAtN(Node *l, int v, int n);  // #9
Node *deleteAtN(Node *l, int n);        // #10
Node *changeValueAtN(Node *l, int n);   // #8
int getNumElements(Node *l);            // #4
Node *findElement(Node *l, int v);      // #5
void delList(Node *l);                  // #6
void printList(Node *l);                // #2


static Node* traverseToN(Node *l, int n);

#endif
