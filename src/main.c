#include "list.h"
#include "tokenizer.h"
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 256

int main()
{
    char inputBuffer[MAX_INPUT_SIZE] = { 0 };
    setbuf(stdout, NULL);
    printf("Initialized\n\n");

    fgets(inputBuffer, MAX_INPUT_SIZE, stdin);
    int inputLength = strlen(inputBuffer);
    if (inputBuffer[inputLength - 1] == '\n')
    {
        inputBuffer[inputLength - 1] = '\0';
    }

    List tokenList;
    Tokenize(&tokenList, inputBuffer);

    Token currToken;
    int tokenIndex = 0;
    for (int columnNumber = 1; columnNumber <= inputLength; columnNumber++)
    {
        currToken = ListGet(tokenList, tokenIndex, Token);
        if (currToken.columnNumber == columnNumber)
        {
            if (currToken.type != TokenTypeWhitespace) 
                printf("^");
            else
                printf(" ");
            tokenIndex++;
        }
        else
        {
            printf(" ");
        }
    }

    printf("\n");

    for (int i = 0, n = tokenList.count; i < n; i++)
    {
        PrintToken(ListGetPtr(tokenList, i, Token));
    }

    return 0;
}