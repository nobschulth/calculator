#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>

typedef enum Type {
    OPERATOR,
    FUNCTION,
    VALUE,
    OPEN_BR,
    CLOSE_BR,
    END,
    UNKNOWN
} Type;

typedef struct Token {
    Type type;
    char* value;
    size_t len; 
} Token;

//len is the len of the returned token
Token* tokenize_str(char* str, size_t* return_len);
Type get_token_type(char* str, size_t* to_size);
#endif
