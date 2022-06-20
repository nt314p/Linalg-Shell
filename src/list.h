#pragma once

typedef struct List
{
    unsigned int count;
    unsigned int capacity;
    unsigned int elementSize;
    void* data;
} List;

List* ListInitialize(unsigned int capacity, unsigned int elementSize);
List* ListInitializeDefault(unsigned int elementSize);
void ListDelete(List* list);
void ListAdd(List* list, void* value);
void* ListGet(List* list, unsigned int index);
void ListRemove(List* list, unsigned int index);
void ListInsert(List* list, unsigned int index, void* value);