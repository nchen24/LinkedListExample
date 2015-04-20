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

/* Function name:   safemalloc
 * Description:     A wrapper for malloc that asserts that malloc succeeded.
 * Return:          A void * that points to a block of memory of size size.
 * Parameters:
 *      - size:     The number of bytes to allocate.
 * Failure cases:   None.
 */
void *safemalloc(size_t size){
    void *p = malloc(size);
    assert(p);
    return p;
}

/* Function name:   makeList
 * Description:     Makes a list from the value v passed in.  All operations
 *                  that make new nodes ultimately reduce to this.
 * Return:          The new list.
 * Parameters:      
 *      - v:        An integer to use as the value of the new node.
 * Failure cases:   None.
 */
Node *makeList(int v){
    Node *newNode = safemalloc(sizeof(Node));
    newNode->val = v;
    newNode->next = NULL;
    return newNode;
}

/* Function name:   addToHead
 * Description:     Adds a new node with value v to the head of list l.  If l is
 *                  NULL, returns a new list with a node of value v.
 * Return:          The new list.
 * Parameters:
 *      - l:        An existing list to prepend to.
 *      - v:        The value of the new node.
 * Failure cases:   None.
 */
Node *addToHead(Node *l, int v){
    Node *newNode = makeList(v);
    newNode->next = l;
    return newNode;
}

/* Function name:   addToTail
 * Description:     Adds a node with value v to the end of list l.  If l is
 *                  NULL, returns a new list with a node of value v.
 * Return:          Returns a pointer to the new list.
 * Parameters
 *      - l:        An existing list.
 *      - v:        The value of the new node.
 * Failure cases:   None.
 */
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

/* Function name:   insertAtN
 * Description:     Inserts a new node BEFORE the Nth node of l.  That is, the
 *                  inserted node becomes the Nth node.  If l is NULL and n is
 *                  0, returns a new list with a node of value v.
 * Return:          The new list.
 * Parameters
 *      - l:        An existing list.
 *      - v:        The value of the new node.
 *      - n:        The place to insert into.
 * Failure cases:   If n < 0 or n > length(l), then an assertion will be
 *                  triggered, and a NULL list returned.
 */
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

/* Function name:   deleteAtN
 * Description:     Deletes the Nth Node of list l.
 * Return:          The list, minus the deleted node.
 * Parameters
 *      - l:        An existing list.
 *      - n:        The place to delete.
 * Failure cases:   If n < 0 or n > length(l), then an assertion will be
 *                  triggered, and a NULL list returned.
 */
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

/* Function name:   changeValueAtN
 * Description:     Changes the value at the Nth node of list l to v.
 * Return:          The list, with the nth node's value altered.
 * Parameters
 *      - l:        An existing list.
 *      - v:        The new value to change to.
 *      - n:        The node to modify.
 * Failure cases:   If n < 0 or n > length(l), then an assertion will be
 *                  triggered, and a NULL list returned.
 */
Node *changeValueAtN(Node *l, int v, int n){
    Node *toChange = traverseToN(l, n);
    if(!toChange)
        return NULL;
    toChange->val = v;
    return l;
}

/* Function name:   getNumElements
 * Description:     Determines the length of list l.
 * Return:          The length of l, as represented by an int.
 * Parameters
 *      - l:        An existing list.
 * Failure cases:   None.
 */
int getNumElements(Node *l){
    int c = 0;
    for(Node *iter = l ; l ; l = l->next)
        c++;
    return c;
}

/* Function name:   findElement
 * Description:     Finds the first node that contains value v.
 * Return:          A pointer to the first node that contains value v.  Returns
 *                  NULL if no such node exists.
 * Parameters
 *      - l:        An existing list.
 *      - v:        The value to search for.
 * Failure cases:   None.
 */
Node *findElement(Node *l, int v){
    for(Node *iter = l ; iter ; iter = iter->next)
        if(iter->val == v)
            return iter;
    return NULL;
}

/* Function name:   delList
 * Description:     Deletes the whole list pointed at by l.
 * Return:          Nothing.
 * Parameters
        - l:        The list to delete.
 * Failure cases:   None.
 */
void delList(Node *l){
    Node *iter = l;
    while(iter){
        Node *next = iter->next;
        free(iter);
        iter = next;
    }
}

/* Function name:   printList
 * Description:     Prints the list, separated by a space and terminated by a
 *                  newline.
 * Return:          Nothing.
 * Parameters
        - l:        An existing list.
 * Failure cases:   None.
 */
void printList(Node *l){
    for(Node *iter = l ; iter ; iter = iter->next){
        printf("%d ", iter->val);
    }
    printf("\n");
}

/* Function name:   traverseToN
 * Description:     Gets a pointer to the nth node in the list, like indexing
 *                  into an array.  Note: this is only a helper function, not a
 *                  public function.
 * Return:          A pointer to the nth node.
 * Parameters
        - l:        An existing list.
        - n:        The number to go to.
 * Failure cases:   If n < 0 or n > length(l), then an assertion will be
 *                  triggered, and a NULL list returned.
 */
static Node *traverseToN(Node *l, int n){
    myassert(nIsInRange(l, n));
    Node *iter = l;
    for(int i = 0 ; i < n ; i++){
        iter = iter->next;
    }
    return iter;
}

/* Function name:   nIsInRange
 * Description:     Determines if n is within the range of list l (that is, is
 *                  greater than 0 and less than length(l)).
 * Return:          True if 0 < n < length(l), false otherwise.
 * Parameters
        - l:        An existing list.
        - n:        The value to test.
 * Failure cases:   None.
 */
static bool nIsInRange(Node *l, int n){
    if(n < 0 || n > getNumElements(l))
        return false;
    return true;
}
