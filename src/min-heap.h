#define MinHeap_Empty(Heap) (Heap->Size == 0)
#define MinHeap_Last(Heap) (Heap->Heap[Heap->Size - 1])
#define MinHeap_Full(Heap) (Heap->Size == Heap->Capacity)
#define MinHeap_Parent(Position) ((Position - 1) / 2)
#define MinHeap_ChildLeft(Position) ((Position * 2) + 1)
#define MinHeap_ChildRight(Position) ((Position * 2) + 2)
#define MinHeap_Value(Heap, Position) (Heap->Heap[Position])
#define MinHeap_Exists(Heap, Position) (Position >= 0 && Position < Heap->Size)
#define MinHeap_Swap(Heap, A, B) do { \
    int Temp = Heap->Heap[A];         \
    Heap->Heap[A] = Heap->Heap[B];    \
    Heap->Heap[B] = Temp;             \
} while (0);

typedef struct
{
    int *Heap;
    int Capacity;
    int Size;
} min_heap;

typedef enum
{
    MinHeap_Up,
    MinHeap_Down,
    NUM_MINHEAP_DIRECTION
} minheap_direction;

typedef enum
{
    MinHeap_OK,
    MinHeap_ErrorOutOfBounds,
    MinHeap_ErrorEmpty,
    MinHeap_ErrorFull,
} minheap_result;

void MinHeap_Create(min_heap *Heap, int Size);
void MinHeap_Free(min_heap *Heap);
void MinHeap_Print(min_heap *Heap);
void MinHeap_PrintPretty(min_heap *Heap);
minheap_result MinHeap_Add(min_heap *Heap, int Value);
minheap_result MinHeap_Poll(min_heap *Heap, int *Value);
