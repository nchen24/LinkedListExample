#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"

// Macro that allows for assertions to not halt the program.
#define myassert(b) \
    do{\
        if(!b){\
            printf("Assertion failed in %s\n", __FUNCTION__);\
            return NULL;\
        }\
    } while(0);

#define RECURSIVE 0

// Asserts that malloc succeeded
void *safemalloc(size_t size){
    void *p = malloc(size);
    assert(p);
    return p;
}

// Makes a list from the value v passed in.  All operations that make new nodes
// ultimately reduce to this.
Node *makeList(int v){
    Node *newNode = safemalloc(sizeof(Node));
    newNode->val = v;
    newNode->next = NULL;
    return newNode;
}

// Prepends a node with value v to l
Node *addToHead(Node *l, int v){
    Node *newNode = makeList(v);
    newNode->next = l;
    return newNode;
}

#if RECURSIVE
// Recursive solution to add to the tail of list l.  Note: This code is slightly
// messy!
Node *addToTail(Node *l, int v){
    if(!l)  // List is null, make a new one and return
        return makeList(v);
    if(!l->next){ // Next is null, i.e. at the tail, add node and return
        l->next = makeList(v);
        return l; // This return does nothing, simply eliminates need for wrapper
    }
    addToTail(l->next, v);
    return l;
}
#else
Node *addToTail(Node *l, int v){
    if(!l)
        return makeList(v);

    Node *iter = l;
    while(iter->next){
        iter = iter->next;
    }
    iter->next = makeList(v);
    return l;
}
#endif

Node *insertAtN(Node *l, int v, int n){
    if(!l)
        return makeList(v);
    if(n == 0){
        return addToHead(l, v);
    }
    Node *before = traverseToN(l, n-1);
    assert(before);
    Node *after = before->next;
    before->next = makeList(v);
    before->next->next = after;
    return l;
}
Node *deleteAtN(Node *l, int n){
    myassert(nIsInRange(l, n));
    if(n == 0){
        Node *after = l->next;
        free(l);
        return after;
    }
    Node *toDelBefore = traverseToN(l, n-1);
    Node *toDelAfter = toDelBefore->next->next;
    free(toDelBefore->next);
    toDelBefore->next = toDelAfter;

    return l;
}

Node *changeValueAtN(Node *l, int v, int n){
    Node *toChange = traverseToN(l, n);
    if(!toChange)
        return NULL;
    toChange->val = v;
    return l;
}

#if RECURSIVE
int getNumElements(Node *l){
    return !l ? 0 : 1 + getNumElements(l->next);
}
#else
int getNumElements(Node *l){
    int c = 0;
    for(Node *iter = l ; l ; l = l->next)
        c++;
    return c;
}
#endif

#if RECURSIVE
Node *findElement(Node *l, int v){
    if(!l)
        return NULL;
    if(l->val == v)
        return l;
    return findElement(l->next, v);
}
#else
Node *findElement(Node *l, int v){
    for(Node *iter = l ; iter ; iter = iter->next)
        if(iter->val == v)
            return iter;
    return NULL;
}
#endif

#if RECURSIVE
void delList(Node *l){
    if(!l)
        return;
    Node *temp = l->next;
    free(l);
    delList(temp);
}
#else
void delList(Node *l){
    Node *iter = l;
    while(iter){
        Node *next = iter->next;
        free(iter);
        iter = next;
    }
}
#endif

#if RECURSIVE
void printList(Node *l){
    if(!l){
        printf("\n");
        return;
    }
    printf("%d ", l->val);
    printList(l->next);
}
#else
void printList(Node *l){
    for(Node *iter = l ; iter ; iter = iter->next){
        printf("%d ", iter->val);
    }
    printf("\n");
}
#endif

#if RECURSIVE
static Node *traverseToN(Node *l, int n){
    myassert(nIsInRange(l, n));
    if(!l)
        return NULL;
    if(n == 0)
        return l;
    return traverseToN(l->next, n-1);
}
#else
static Node *traverseToN(Node *l, int n){
    myassert(nIsInRange(l, n));
    Node *iter = l;
    for(int i = 0 ; i < n ; i++){
        iter = iter->next;
    }
    return iter;
}
#endif

static bool nIsInRange(Node *l, int n){
    if(n < 0 || n > getNumElements(l))
        return false;
    return true;
}
