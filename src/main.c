#include "list.h"
#include <stdio.h>

#define MAX_INPUT_SIZE 256

int main()
{
    setbuf(stdout, NULL);
    printf("Initialized\n\n");

    List a;
    ListInitializeDefault(&a, sizeof(int));

    for (int i = 0; i < 30; i++)
    {
        *(int*)ListAddInPlace(&a) = i;
    }

    for (int i = 0; i < a.count; i++)
    {
        printf("%d, ", ListGet(a, i, int));
    }
    printf("\n");

    printf("Count is: %d\n", a.count);
    printf("Capacity is: %d\n\n", a.capacity);

    for (int i = 28; i >= 0; i -= 2)
    {
        ListRemove(&a, i);
    }

    for (int i = 0; i < a.count; i++)
    {
        printf("%d, ", ListGet(a, i, int));
    }
    printf("\n");

    printf("Count is: %d\n", a.count);
    printf("Capacity is: %d\n\n", a.capacity);


    int nOne = -1;
    ListInsert(&a, 0, &nOne);
    ListInsert(&a, 3, &nOne);

    for (int i = 0; i < a.count; i++)
    {
        printf("%d, ", ListGet(a, i, int));
    }
    printf("Count is: %d\n", a.count);
    printf("Capacity is: %d\n", a.capacity);

    ListDelete(&a);

    return 0;
}