#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "min-heap.h"

void
MinHeap_Create(min_heap *Heap, int Size)
{
    Heap->Heap = malloc(sizeof(int) * Size);
    memset(Heap->Heap, 0, sizeof(int) * Size);
    Heap->Capacity = Size;
    Heap->Size = 0;
}

void
MinHeap_Free(min_heap *Heap)
{
    if (Heap->Heap)
    {
        free(Heap->Heap);
    }
}

void
MinHeap_Print(min_heap *Heap)
{
    for (int i = 0; i < Heap->Size; i++)
    {
        printf("%i = %i, ", i, MinHeap_Value(Heap, i));
    }
    printf("|\n");
}

void
MinHeap_PrintPretty(min_heap *Heap)
{
    int Level = 0;
    int Left = 1;
    printf("\nLevel 0: ");
    for (int i = 0; i < Heap->Size; i++)
    {
        if (Left == 0)
        {
            if (Level == 1)
            {
                Level = 2;
            }
            else
            {
                Level++;
            }
            printf("\nLevel %i: ", Level);
            Left = Level * 2;
        }
        if (Left % 2 == 0 && MinHeap_Exists(Heap, MinHeap_Parent(i)))
        {
            printf("[%i]", MinHeap_Value(Heap, MinHeap_Parent(i)));
        }
        printf("%i%c", MinHeap_Value(Heap, i), Left % 2 == 0 ? '+' : ' ');
        Left--;
    }
    printf("__\n");
}

void
MinHeap_Heapify(min_heap *Heap, int Direction)
{
    assert(Direction == MinHeap_Up ||
           Direction == MinHeap_Down);

    if (Direction == MinHeap_Up)
    {
        int Position = Heap->Size - 1;
        while (MinHeap_Exists(Heap, MinHeap_Parent(Position)) &&
               MinHeap_Value(Heap, MinHeap_Parent(Position)) >
               MinHeap_Value(Heap, Position))
        {
            MinHeap_Swap(Heap, Position, MinHeap_Parent(Position));
            Position = MinHeap_Parent(Position);
        }
    }
    else if (Direction == MinHeap_Down)
    {
        int Position = 0;
        while (MinHeap_Exists(Heap, MinHeap_ChildLeft(Position)))
        {
            int Smaller = MinHeap_ChildLeft(Position);

            if (MinHeap_Exists(Heap, MinHeap_ChildRight(Position)) &&
                MinHeap_Value(Heap, MinHeap_ChildRight(Position)) <
                MinHeap_Value(Heap, MinHeap_ChildLeft(Position)))
            {
                Smaller = MinHeap_ChildRight(Position);
            }

            if (MinHeap_Value(Heap, Position) > MinHeap_Value(Heap, Smaller))
            {
                MinHeap_Swap(Heap, Position, Smaller);
                Position = Smaller;
            }
            else
            {
                break;
            }
        }
    }
}

minheap_result
MinHeap_Poll(min_heap *Heap, int *Value)
{
    if (MinHeap_Empty(Heap))
    {
        return MinHeap_ErrorEmpty;
    }
    *Value = Heap->Heap[0];
    MinHeap_Swap(Heap, 0, Heap->Size - 1);
    Heap->Size--;
    MinHeap_Heapify(Heap, MinHeap_Down);
    return MinHeap_OK;
}

minheap_result
MinHeap_Add(min_heap *Heap, int Value)
{
    if (MinHeap_Full(Heap))
    {
        return MinHeap_ErrorFull;
    }

    Heap->Heap[Heap->Size] = Value;
    Heap->Size++;
    MinHeap_Heapify(Heap, MinHeap_Up);
    return MinHeap_OK;
}
