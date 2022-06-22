#pragma once

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
    TokenTypeBackslash,
    TokenTypeCaret,
    TokenTypeEquals,
    TokenTypePeriod,

    TokenTypeIdentifier,
    TokenTypeNumberLiteral
} TokenType;

typedef struct Token
{
    union {
        char* value;
        char charValue;
    };
    unsigned int columnNumber; // used for logging purposes
    TokenType type;
} Token;

void Tokenize(List* tokenList, const char* input);
void PrintToken(Token* token);
