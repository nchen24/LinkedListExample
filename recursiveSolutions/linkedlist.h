#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef struct Node{
    int val;
    struct Node *next;
} Node;

// Make a new list from value v
Node *makeList(int v);                          // #1

// Add a new node with value v before list l
Node *addToHead(Node *l, int v);                // #3

// Add a new node with value v at the end of list l
Node *addToTail(Node *l, int v);                // #7

// Add a new node at position in with value v in list l
Node *insertAtN(Node *l, int v, int n);         // #9

// Delete node at position n in list l
Node *deleteAtN(Node *l, int n);                // #10

// Change value of the node at position in list l to value v
Node *changeValueAtN(Node *l, int v, int n);    // #8

// Get the number of elements in list l
int getNumElements(Node *l);                    // #4

// Return the node that contains value v in list l
Node *findElement(Node *l, int v);              // #5

// Delete list l
void delList(Node *l);                          // #6

// Print list l
void printList(Node *l);                        // #2


static Node* traverseToN(Node *l, int n);
static bool nIsInRange(Node *l, int n);

#endif
