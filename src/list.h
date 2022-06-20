#pragma once

typedef struct List
{
    unsigned int count;
    unsigned int capacity;
    unsigned int elementSize;
    void* data;
} List;

#define ListGet(list, index, DATATYPE) *((DATATYPE*)list.data + index)

void ListInitialize(List* list, unsigned int capacity, unsigned int elementSize);
void ListInitializeDefault(List* list, unsigned int elementSize);
void ListDelete(List* list);
void ListAdd(List* list, void* value);
void* ListAddInPlace(List* list);
void ListRemove(List* list, unsigned int index);
void ListInsert(List* list, unsigned int index, void* value);