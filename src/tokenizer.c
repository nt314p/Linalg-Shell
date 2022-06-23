#include "list.h"
#include "tokenizer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static inline int IsDigit(char c)
{
    return c >= '0' && c <= '9';
}

static inline int IsNumerical(char c)
{
    return IsDigit(c) || c == '.';
}

static inline int IsLetter(char c)
{
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

static inline int IsIdentifier(char c)
{
    return IsLetter(c) || c == '_' || IsDigit(c);
}

static inline int IsElementWiseOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '\\' || c == '/' || c == '^';
}

void PrintToken(Token* token)
{
    char* tokenName;

    switch (token->type)
    {
    case TokenTypeBad:
        tokenName = "TokenTypeBad";
        break;
    case TokenTypeWhitespace:
        tokenName = "TokenTypeWhitespace";
        break;
    case TokenTypeOpenParenthesis:
        tokenName = "TokenTypeOpenParenthesis";
        break;
    case TokenTypeCloseParenthesis:
        tokenName = "TokenTypeCloseParenthesis";
        break;
    case TokenTypeOpenSquareBrace:
        tokenName = "TokenTypeOpenSquareBrace";
        break;
    case TokenTypeCloseSquareBrace:
        tokenName = "TokenTypeCloseSquareBrace";
        break;
    case TokenTypePlus:
        tokenName = "TokenTypePlus";
        break;
    case TokenTypeMinus:
        tokenName = "TokenTypeMinus";
        break;
    case TokenTypeAsterisk:
        tokenName = "TokenTypeAsterisk";
        break;
    case TokenTypeForwardSlash:
        tokenName = "TokenTypeForwardSlash";
        break;
    case TokenTypeBackslash:
        tokenName = "TokenTypeBackslash";
        break;
    case TokenTypeCaret:
        tokenName = "TokenTypeCaret";
        break;
    case TokenTypeEquals:
        tokenName = "TokenTypeEquals";
        break;
    case TokenTypePeriod:
        tokenName = "TokenTypePeriod";
        break;
    case TokenTypeIdentifier:
        tokenName = "TokenTypeIdentifier";
        break;
    case TokenTypeNumberLiteral:
        tokenName = "TokenTypeNumberLiteral";
        break;
    }

    printf("%s: ", tokenName);

    if (token->type != TokenTypeIdentifier && token->type != TokenTypeNumberLiteral)
        printf("%c", token->charValue);
    else
        printf(token->value);

    printf("; column: %d\n", token->columnNumber);
}

void Tokenize(List* tokenList, const char* input)
{
    ListInitialize(tokenList, 20, sizeof(Token));

    unsigned int inputLength = strlen(input);
    unsigned int cursorIndex = 0;
    unsigned int multiCharStartIndex = 0; // the start index of the multichar token inside the input string
    TokenType tokenType;
    char currentToken;

    while (cursorIndex < inputLength)
    {
        tokenType = TokenTypeBad;
        currentToken = input[cursorIndex];
        multiCharStartIndex = cursorIndex;
        int isSingleCharacterToken = 1;

        if (IsNumerical(currentToken))
        {
            cursorIndex++;
            while (cursorIndex < inputLength && IsNumerical(input[cursorIndex]))
            {
                // '.' may be part of an element-wise operator instead of a number literal
                if (input[cursorIndex] == '.' && cursorIndex + 1 < inputLength)
                {
                    // don't consume . if it preceeds an element wise operator
                    if (IsElementWiseOperator(input[cursorIndex + 1])) break;
                }
                cursorIndex++;
            }

            tokenType = TokenTypeNumberLiteral;
            isSingleCharacterToken = 0;
        }

        if (IsLetter(currentToken)) {
            cursorIndex++;

            while (cursorIndex < inputLength && IsIdentifier(input[cursorIndex]))
            {
                cursorIndex++;
            }

            tokenType = TokenTypeIdentifier;
            isSingleCharacterToken = 0;
        }

        switch (currentToken)
        {
        case '\t':
        case ' ':
            tokenType = TokenTypeWhitespace;
            break;
        case '(':
            tokenType = TokenTypeOpenParenthesis;
            break;
        case ')':
            tokenType = TokenTypeCloseParenthesis;
            break;
        case '+':
            tokenType = TokenTypePlus;
            break;
        case '-':
            tokenType = TokenTypeMinus;
            break;
        case '*':
            tokenType = TokenTypeAsterisk;
            break;
        case '/':
            tokenType = TokenTypeForwardSlash;
            break;
        case '\\':
            tokenType = TokenTypeBackslash;
            break;
        case '^':
            tokenType = TokenTypeCaret;
            break;
        case '=':
            tokenType = TokenTypeEquals;
            break;
        case '.':
            tokenType = TokenTypePeriod;
            break;
        }

        Token* token = (Token*)ListAddInPlace(tokenList);
        token->type = tokenType;

        if (isSingleCharacterToken)
        {
            token->columnNumber = cursorIndex + 1;
            token->charValue = currentToken;
            cursorIndex++;
        }
        else
        {
            token->columnNumber = multiCharStartIndex + 1;
            int tokenStringLength = cursorIndex - multiCharStartIndex;
            token->value = (char*)malloc(tokenStringLength + 1);
            memcpy(token->value, input + multiCharStartIndex, tokenStringLength);
            token->value[tokenStringLength] = 0;
        }
    }
}