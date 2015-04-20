#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "linkedlist.h"

#define getArrLen(arr) (sizeof(arr) / sizeof(arr[0]))

void testMakeList(){
    int testCases[] = {8, 'n', -1, 149327859816738, -583492752983568732};

    for(int i = 0 ; i < getArrLen(testCases) ; i++){
        Node *test;
        test = makeList(testCases[i]);
        printList(test);
    }

    printf(">> Test make list completed! <<\n");

}

void testAddToHead(){
    Node *test = NULL;
    test = addToHead(test, 5);
    printList(test);
    test = addToHead(test, 19);
    printList(test);
    printf(">> Test add to head completed! <<\n");
}

void testGetNumElements(){
    int vals[] = {0, 3, -153, 33895, 3049, 101010};
    Node *test = NULL;
    assert(getNumElements(test) == 0);
    for(int i = 0 ; i < getArrLen(vals) ; i++){
        test = addToHead(test, vals[i]);
        assert(getNumElements(test) == i+1);
    }
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

    printf(">> Test find element completed! <<\n");
}

int main(){
    testMakeList();
    testAddToHead();
    testGetNumElements();
    testFindElement();

    return 0;
}
