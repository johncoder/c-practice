#include <assert.h>
#include <stdio.h>
#include "min-heap.h"

int
MinHeap_Test_1()
{
    min_heap Heap;
    MinHeap_Create(&Heap, 1024);
    for (int i = 10; i > 0; --i)
    {
        MinHeap_Add(&Heap, i);
    }
    MinHeap_Print(&Heap);
    int Head = 0;
    int Result = MinHeap_Poll(&Heap, &Head);
    MinHeap_Free(&Heap);
    if (Result == MinHeap_OK && Head == 1)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int
MinHeap_Test_2()
{
    min_heap Heap;
    MinHeap_Create(&Heap, 1024);
    int Values[] = {52, 43, 13, 18, 22,
                    32, 9, 11, 2, 134};
    int SortedValues[] = {2, 9, 11, 13, 18,
                          22, 32, 43, 52, 134};
    for (int i = 0; i < 10; i++)
    {
        MinHeap_Add(&Heap, Values[i]);
    }
    MinHeap_PrintPretty(&Heap);
    for (int i = 0; i < 10; i++)
    {
        int Value = 0;
        int Result = MinHeap_Poll(&Heap, &Value);
        if (Result == MinHeap_OK)
        {
            if (Value != SortedValues[i])
            {
                printf("?(%i, %i)\n", Value, SortedValues[i]);
                MinHeap_PrintPretty(&Heap);
            }
            else
            {
                printf("%i, ", Value);
            }
        }
        else
        {
            printf("Error(%i)", Result);
        }
    }
    MinHeap_PrintPretty(&Heap);
    MinHeap_Free(&Heap);
    return -1;
}

void
MinHeap_Tests()
{
    int Result = MinHeap_Test_1();
    if (!Result)
    {
        printf("Test 1 failed.\n");
    }
    else
    {
        printf("Test 1 passed!\n");
    }
    Result = 0;
    Result = MinHeap_Test_2();
    if (!Result)
    {
        printf("Test 2 failed.\n");
    }
    else
    {
        printf("Test 2 passed!\n");
    }
}
