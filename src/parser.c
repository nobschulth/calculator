#include <stddef.h>
#include <ctype.h>
#include "parser.h"

Token* tokenize_str(char* str, size_t* return_len) {
    Token* tokens;
    return_len = 0;
    //the position in str
    size_t str_pos = 0;
    //exit condition is \\0
    for (;;) {
        //if not operator or not bracket: check if number, if not check if function
        size_t to_size = 0;
        Type ty = get_token_type(str + str_pos, &to_size);
        str_pos += to_size + 1;
    }    
}

Type get_token_type(char* str, size_t* to_size) {
    if (str[0] == '+' || str[0] == '-' || str[0] == '/' || str[0] == '*') {
        return OPERATOR;
    }
    if (isdigit(str[0]) || str[0] == '.') {
        
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
