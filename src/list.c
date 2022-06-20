#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define DEFAULT_CAPACITY 16

static void Resize(List* list, unsigned int newCapacity)
{
    list->data = realloc(list->data, newCapacity * list->elementSize);
    list->capacity = newCapacity;
}

void ListInitializeDefault(List* list, unsigned int elementSize)
{
    list->count = 0;
    list->capacity = DEFAULT_CAPACITY;
    list->elementSize = elementSize;
    list->data = malloc(DEFAULT_CAPACITY * elementSize);
}

void ListInitialize(List* list, unsigned int capacity, unsigned int elementSize)
{
    list->count = 0;
    list->capacity = capacity;
    list->elementSize = elementSize;
    list->data = malloc(capacity * elementSize);
}

void ListDelete(List* list)
{
    free(list->data);
}

// Adds the value to the end of the list
void ListAdd(List* list, void* value)
{
    if (list->count + 1 > list->capacity)
        Resize(list, list->capacity * 2);

    unsigned int elementSize = list->elementSize;
    void* dest = (char*)list->data + elementSize * list->count;
    memcpy(dest, value, elementSize);
    list->count++;
}

// Allocates a space in memory at the end of the array and returns the pointer to that memory
// The pointer can then be used to initialize an object in place
void* ListAddInPlace(List* list)
{
    unsigned int count = list->count;
    if (count + 1 > list->capacity)
        Resize(list, list->capacity * 2);

    list->count = count + 1;
    return (char*)list->data + list->elementSize * count;
}

// Inserts the value into the list at the given index
void ListInsert(List* list, unsigned int index, void* value)
{
    if (list->count + 1 > list->capacity)
        Resize(list, list->capacity * 2);

    unsigned int elementSize = list->elementSize;
    unsigned int count = list->count;

    char* indexPtr = (char*)list->data + elementSize * index;

    memmove(indexPtr + elementSize, indexPtr, (count - index) * elementSize);
    memcpy(indexPtr, value, elementSize);
    list->count++;
}

// Removes the element at the given index
void ListRemove(List* list, unsigned int index)
{
    unsigned int newCount = list->count - 1;

    unsigned int elementSize = list->elementSize;
    char* indexPtr = (char*)list->data + elementSize * index;

    memmove(indexPtr, indexPtr + elementSize, (newCount - index) * elementSize);

    list->count = newCount;

    if (newCount < list->capacity / 2)
        Resize(list, list->capacity / 2);
}