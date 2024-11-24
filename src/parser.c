#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>
#include "parser.h"
#include "node.h"
#include "math_funcs.h"

Token* tokenize_str(char* str, size_t* return_len) {
    Token* tokens = NULL;
    *return_len = 0;
    //the position in str
    size_t str_pos = 0;
    //exit condition is \\0
    for (;;) {
        //if not operator or not bracket: check if number, if not check if function
        size_t to_size = 0;
        Type ty = get_token_type(str + str_pos, &to_size);
        str_pos += to_size + 1;
        if (ty == END) {
            break;
        }
        char* val = str + str_pos;
        if (tokens == NULL) {
            tokens = malloc(sizeof(Token));
            return_len++;
        } else {
            tokens = realloc(tokens, sizeof(Token) * *++return_len);
            
        }
        tokens[*return_len - 1].type = ty;
        tokens[*return_len - 1].value = val;
        tokens[*return_len - 1].len = to_size + 1;
    }
    return tokens;    
}

Type get_token_type(char* str, size_t* to_size) {
    if (str[0] == '+' || str[0] == '-' || str[0] == '/' || str[0] == '*') {
        return OPERATOR;
    }
    if (isdigit(str[0]) || str[0] == '.') {
        //increment size if continues
        if (get_token_type(str + 1, to_size) == VALUE) {
            *to_size += 1;
        }
        return VALUE;
    }
    if (str[0] == '\0') {
        return END;
    }
    return UNKNOWN;
}


Node* compile_ast(Token* tokens, size_t len) {
    for (int i = 0; i < len; i++) {
        
    }        
}

