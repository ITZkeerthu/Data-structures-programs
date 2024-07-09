#include <stdio.h>
#include <stdlib.h>

// Define the MinHeap structure
typedef struct {
    int *heapList;
    int currentSize;
} MinHeap;

// Function prototypes
MinHeap* createMinHeap();
void percUp(MinHeap *heap, int i);
void insert(MinHeap *heap, int k);
void percDown(MinHeap *heap, int i);
int minChild(MinHeap *heap, int i);
int delMin(MinHeap *heap);
void buildHeap(MinHeap *heap, int *alist, int size);
int main() {
    // Example usage with user input
    MinHeap *minh = createMinHeap();
    int size, i, element;

    // Prompt user to enter the size of the heap
    printf("Enter the size of the heap: ");
    scanf("%d", &size);

    // Prompt user to enter elements of the heap
    int *inputArray = (int*) malloc(size * sizeof(int));
    printf("Enter %d elements to build the heap:\n", size);
    for (i = 0; i < size; i++) {
        scanf("%d", &element);
        inputArray[i] = element;
    }

    // Build the heap from user input
    buildHeap(minh, inputArray, size);
    
    // Output the sorted elements (using delMin to extract the min element repeatedly)
    printf("Elements in sorted order:\n");
    for (i = 0; i < size; i++) {
        printf("%d\n", delMin(minh));
    }

    // Free allocated memory
    free(inputArray);
    free(minh->heapList);
    free(minh);
    
    return 0;
}

// Function to create a new MinHeap
MinHeap* createMinHeap() {
    MinHeap *heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->heapList = (int*) malloc(sizeof(int));
    heap->currentSize = 0;
    return heap;
}

// Function to maintain heap property after inserting an element
void percUp(MinHeap *heap, int i) {
    while (i / 2 > 0) {
        if (heap->heapList[i] < heap->heapList[i / 2]) {
            // Swap elements
            int tmp = heap->heapList[i];
            heap->heapList[i] = heap->heapList[i / 2];
            heap->heapList[i / 2] = tmp;
        }
        i = i / 2;
    }
}

// Function to insert a new element into the heap
void insert(MinHeap *heap, int k) {
    heap->currentSize++;
    heap->heapList = (int*) realloc(heap->heapList, (heap->currentSize + 1) * sizeof(int));
    heap->heapList[heap->currentSize] = k;
    percUp(heap, heap->currentSize);
}

// Function to maintain heap property after removing the root element
void percDown(MinHeap *heap, int i) {
    int mc;
    while ((i * 2) <= heap->currentSize) {
        mc = minChild(heap, i);
        if (heap->heapList[i] > heap->heapList[mc]) {
            // Swap elements
            int tmp = heap->heapList[i];
            heap->heapList[i] = heap->heapList[mc];
            heap->heapList[mc] = tmp;
        }
        i = mc;
    }
}

// Function to find the index of the smaller child of a node
int minChild(MinHeap *heap, int i) {
    int leftChild = i * 2;
    int rightChild = i * 2 + 1;
    if (rightChild > heap->currentSize) {
        return leftChild;
    } else {
        if (heap->heapList[leftChild] < heap->heapList[rightChild]) {
            return leftChild;
        } else {
            return rightChild;
        }
    }
}

// Function to remove and return the smallest element from the heap
int delMin(MinHeap *heap) {
    int retval = heap->heapList[1];
    heap->heapList[1] = heap->heapList[heap->currentSize];
    heap->currentSize--;
    percDown(heap, 1);
    return retval;
}

// Function to build a heap from an array
void buildHeap(MinHeap *heap, int *alist, int size) {
    int i;
    heap->currentSize = size;
    heap->heapList = (int*) malloc((size + 1) * sizeof(int));
    for (i = 1; i <= size; i++) {
        heap->heapList[i] = alist[i - 1];
    }
    for (i = size / 2; i > 0; i--) {
        percDown(heap, i);
    }
}
