#include "List.h"
#include <string.h>

#define MAX_TOKEN_VALUE_LENGTH 256

typedef enum TokenType
{
    TokenTypeBad,

    TokenTypeWhitespace,
    TokenTypeOpenParenthesis,
    TokenTypeCloseParenthesis,
    TokenTypeOpenSquareBrace,
    TokenTypeCloseSquareBrace,

    TokenTypePlus,
    TokenTypeMinus,
    TokenTypeAsterisk,
    TokenTypeForwardSlash,
    TokenTypeCaret,
    TokenTypeEquals,

    TokenTypeIdentifier,
    TokenTypeNumberLiteral
} TokenType;

typedef struct Token
{
    char* value;
    unsigned int columnNumber; // used for logging purposes
    TokenType type;
} Token;

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

void Tokenize(List* tokenList, const char* input)
{
    ListInitialize(tokenList, 20, sizeof(Token));

    unsigned int inputLength = strlen(input);

    char strValue[MAX_TOKEN_VALUE_LENGTH];

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
                if (currentToken == '.' && cursorIndex + 1 < inputLength)
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

        // tokenize everything else

    }
}