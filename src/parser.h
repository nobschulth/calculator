#ifndef PARSER_H
#define PARSER_H

#include <malloc.h>
#include <stddef.h>
#include "node.h"

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

Node* compile_ast(Token* tokens, size_t len);
size_t get_lowest_op(Token* tokes, size_t len);
int get_token_level(Token* token);
Node* 
#endif


