#include "list.h"
#include "tokenizer.h"
#include <stdio.h>

#define MAX_INPUT_SIZE 256

int main()
{
    char inputBuffer[MAX_INPUT_SIZE] = { 0 };
    setbuf(stdout, NULL);
    printf("Initialized\n\n");
    fgets(inputBuffer, MAX_INPUT_SIZE, stdin);

    List tokenList;
    Tokenize(&tokenList, inputBuffer);

    for (int i = 0, n = tokenList.count; i < n; i++)
    {
        PrintToken(ListGetPtr(tokenList, i, Token));
    }

    return 0;
}