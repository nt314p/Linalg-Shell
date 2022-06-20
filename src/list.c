#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define DEFAULT_CAPACITY 8

static void Resize(List* list, unsigned int newCapacity)
{
    list->data = realloc(list->data, newCapacity);
    list->capacity = newCapacity;
}

List* ListInitializeDefault(unsigned int elementSize)
{
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) return NULL;
    list->count = 0;
    list->capacity = DEFAULT_CAPACITY;
    list->elementSize = elementSize;
    list->data = malloc(DEFAULT_CAPACITY * elementSize);
    return list;
}

List* ListInitialize(unsigned int capacity, unsigned int elementSize)
{
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) return NULL;
    list->count = 0;
    list->capacity = capacity;
    list->elementSize = elementSize;
    list->data = malloc(capacity * elementSize);
    return list;
}

void ListDelete(List* list)
{
    free(list->data);
    free(list);
}

void ListAdd(List* list, void* value)
{
    if (list->count + 1 > list->capacity)
        Resize(list, list->capacity * 2);

    unsigned int elementSize = list->elementSize;
    void* dest = (char*)list->data + elementSize * list->count;
    memcpy(dest, value, elementSize);
    list->count++;
}

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

inline void* ListGet(List* list, unsigned int index)
{
    return (void*)((char*)list->data + index * list->elementSize);
}