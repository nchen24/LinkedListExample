#include <stdio.h>
#include <time.h>
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
    for(int i = 0 ; i < n ; i++)
        list = addToHead(list, arc4random());
    return list;
}
Node *makeRandListOfSizeN_bounded(int n, int upperBound){
    Node *list = NULL;
    for(int i = 0 ; i < n ; i++)
        list = addToHead(list, arc4random_uniform(upperBound));
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

    for(int i = 0 ; i < (int)getArrLen(testCases) ; i++){
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
    for(int i = 0 ; i < (int)getArrLen(vals) ; i++){
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

    assert((int)getArrLen(testCases) == (int)getArrLen(answers));

    Node *list= NULL;
    assert(findElement(list, testCases[0]) == NULL);

    for(int i = 0 ; i < (int)getArrLen(vals) ; i++){
        list = addToHead(list, vals[i]);
    }

    for(int i = 0 ; i < (int)getArrLen(vals) ; i++){
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

void testAddToTail(){
    int vals[] = {0, 3, -153, 33895, 3049, 101010};
    Node *list = NULL;
    for(int i = 0 ; i < (int)getArrLen(vals) ; i++){
        list = addToTail(list, vals[i]);
    }
    DArray test = arrayify(list);
    assert(test.size == (int)getArrLen(vals));
    for(int i = 0 ; i < (int)getArrLen(vals) ; i++){
        assert(test.contents[i] == vals[i]);
    }
    free(test.contents);
    delList(list);
    printf(">> Test add to tail completed! <<\n");
}
void testChangeValueAtN(){
    int vals[] = {16,   1024,   99, -10,    -54098};
    int poss[] = {0,    40,     22, 99,     32};
    Node *list = makeRandListOfSizeN(100);

    changeValueAtN(list, 0, -1);  // Should cause an error in your way of choice!
    changeValueAtN(list, 0, 300);

    for(int i = 0 ; i < (int)getArrLen(vals) ; i++){
        changeValueAtN(list, vals[i], poss[i]);
    }

    DArray arr = arrayify(list);

    for(int i = 0 ; i < (int)getArrLen(vals) ; i++){
        assert(arr.contents[i] == arr.contents[i]);
        printf("Test %d in testChangeValueAtN passed!\n", i);
    }

    free(arr.contents);
    delList(list);

    printf(">> Test change value at n completed! <<\n");
}

void testInsertAtN(){
    Node *list = makeRandListOfSizeN(100);
    int vals[] = {16,   1024,   99, -10,    -54098};
    int poss[] = {0,    40,     22, 99,     32};

    // Test insertion into null list
    Node *test = NULL;
    test = insertAtN(test, vals[0], poss[0]);
    assert(test->val == vals[0]);

    // Insert at various places
    for(int i = 0 ; i < (int)getArrLen(vals) ; i++){
        list = insertAtN(list, vals[i], poss[i]);
    }

    // Ensure length is correct
    assert(getNumElements(list) == 100 + (int)getArrLen(vals));

    // Insert random value at end
    int newRandVal = arc4random();
    list = insertAtN(list, newRandVal, getNumElements(list));

    DArray arr = arrayify(list);
    // Ensure that value (plus a couple other inserted ones) are correct
    assert(arr.contents[arr.size-1] == newRandVal);
    assert(arr.contents[poss[0]] == vals[0]);
    assert(arr.contents[poss[2]] == vals[2]);

    free(arr.contents);
    delList(list);
    delList(test);
    printf(">> Test insert at n completed! <<\n");
}

void testDeleteAtN(){
    Node *list = makeRandListOfSizeN(100);

    list = deleteAtN(list, 99);
    list = deleteAtN(list, 0);
    deleteAtN(list, 99); // Should cause an error in your way of choice!

    int origSize = getNumElements(list);
    for(int i = 0 ; i < origSize ; i++){ // Alternative way of deleting the list
        list = deleteAtN(list, 0);
    }
    assert(getNumElements(list) == 0);
    printf(">> Test delete at n completed! <<\n");
}

void stressTests(){
    for(int i = 0 ; i <= 1000 ; i++){
        Node *list = makeRandListOfSizeN(i * 1000);
        delList(list);
        if(!(i%50)){
            printf("Made and deleted list of size %d...\n", i*1000);
        }
    }

    int hellListSize = 10000000;
    Node *list = makeRandListOfSizeN_bounded(hellListSize, 5000000);
    printList(list);

    for(int i = 0 ; i < 5000000 ; i++){
        Node *t = findElement(list, i);
        if(t){
            int pos = getNumElements(t->next);
            printf("Found %d in list at pos %d!\n", i, pos);
            break;
        }
    }
    for(int i = 0 ; i < 3000 ; i++){
        int op = arc4random() % 4;
        switch(op){
            case 0: list = insertAtN(list, arc4random(),
                              arc4random_uniform(hellListSize)); break;
            case 1: list = deleteAtN(list, arc4random_uniform(hellListSize)); break;
            case 2: list = changeValueAtN(list, arc4random(),
                                   arc4random_uniform(hellListSize)); break;
            case 3: list = addToTail(list, arc4random()); break;
        }
        if(!(i%50))
            printf("%d random operations completed...\n", i);
    }
    delList(list);
}

int main(){
    srand(time(0));
    testMakeList(); // Also tests print
    testAddToHead();
    testGetNumElements();
    testFindElement();
    testDelList();
    testAddToTail();
    testChangeValueAtN();
    testInsertAtN();
    testDeleteAtN();

    printf(">> All basic tests completed! <<\n");
    printf(">> Now starting stress tests... <<\n");
    stressTests();
    printf(">> Congratulations, stress tests passed! <<\n");

    return 0;
}
