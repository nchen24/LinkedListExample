#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "linkedlist.h"

#define getArrLen(arr) (sizeof(arr) / sizeof(arr[0]))
#define DELETE_DEFINED 1
#define GETLENGTH_DEFINED 1

typedef struct DArray{
    int size;
    int *contents;
} DArray;

Node *makeRandListOfSizeN(int n){
    Node *list = NULL;
    for(int i = 0 ; i < n ; i++){
        list = addToHead(list, arc4random());
    }
    return list;
}

DArray arrayify(Node *list){
    DArray arr;
    arr.size = getNumElements(list);
    arr.contents = malloc(sizeof(int) * arr.size);
    Node *iter = list;
    for(int i = 0 ; i < arr.size ; i++){
        arr.contents[i] = iter->val;
        iter = iter->next;
    }
    return arr;
}

void testMakeList(){
    int testCases[] = {8, 'n', -1, 149327859816738, -583492752983568732};

    for(int i = 0 ; i < getArrLen(testCases) ; i++){
        Node *list;
        list = makeList(testCases[i]);
        printList(list);
#if DELETE_DEFINED
        delList(list);
#endif
    }

    printf(">> Test make list completed! <<\n");

}

void testAddToHead(){
    Node *list = NULL;
    list = addToHead(list, 5);
    printList(list);
    list = addToHead(list, 19);
    printList(list);
#if DELETE_DEFINED
        delList(list);
#endif
    printf(">> Test add to head completed! <<\n");
}

void testGetNumElements(){
    int vals[] = {0, 3, -153, 33895, 3049, 101010};
    Node *list= NULL;
    assert(getNumElements(list) == 0);
    for(int i = 0 ; i < getArrLen(vals) ; i++){
        list = addToHead(list, vals[i]);
        assert(getNumElements(list) == i+1);
    }
#if DELETE_DEFINED
        delList(list);
#endif
    printf(">> Test get num elements completed! <<\n");
}

void testFindElement(){
    int vals[] = {0, 3, -153, 33895, 3049, 101010};
    int testCases[] = {3,   101010, -10,    0,      15,     1};
    bool answers[] =  {true, true,  false,  true,   false,  false};

    assert(getArrLen(testCases) == getArrLen(answers));

    Node *list= NULL;
    assert(findElement(list, testCases[0]) == NULL);

    for(int i = 0 ; i < getArrLen(vals) ; i++){
        list = addToHead(list, vals[i]);
    }

    for(int i = 0 ; i < getArrLen(vals) ; i++){
        Node *temp = findElement(list, testCases[i]);
        assert((temp != NULL) == answers[i]);
        printf("Test %d in testFindElement passed!\n", i);
    }
#if DELETE_DEFINED
        delList(list);
#endif

    printf(">> Test find element completed! <<\n");
}

void testDelList(){
    Node *list = NULL;
    delList(list);

    list = makeRandListOfSizeN(10);
    //printList(list);
    delList(list);

    list = makeRandListOfSizeN(100);
    //printList(list);
    delList(list);
    printf(">> Test del list completed! <<\n");
}

int main(){
    srand(time(0));
    testMakeList(); // Also tests print
    testAddToHead();
    testGetNumElements();
    testFindElement();
    testDelList();

    return 0;
}
