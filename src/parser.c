#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "node.h"
#include "math_funcs.h"
#include "util.h"

Token* tokenize_str(char* str, size_t* return_len) {
    Token* tokens = NULL;
    *return_len = 0;
    
    //the position in str
    size_t str_pos = 0;
    //exit condition is \\0
    for (;;) {
        if (str[str_pos] == ' ') {
            str_pos += 1;
            continue;
        }
        //if not operator or not bracket: check if number, if not check if function
        size_t to_size = 0;
        Type ty = get_token_type(str + str_pos, &to_size);
        str_pos += to_size + 1;
        if (ty == END) {
            break;
        }
        char* val = str + str_pos - 1 - to_size;
        if (tokens == NULL) {
            tokens = malloc(sizeof(Token));
            if (tokens == NULL) {
                fprintf(stderr, "Failed to allocate memory!");
                exit(1);
            }
            *return_len += 1;
            
        } else {
            *return_len += 1;
            tokens = realloc(tokens, sizeof(Token) * *return_len);            
            if (tokens == NULL) {
                fprintf(stderr, "Failed to allocate memory!");
                exit(1);
            }
            
        }

        tokens[(*return_len) - 1].type = ty;       
        tokens[(*return_len) - 1].value = val;
        tokens[(*return_len) - 1].len = to_size + 1;
                
    }
    return tokens;    
}

Type get_token_type(char* str, size_t* to_size) {
    if (str[0] == '+' || str[0] == '-' || str[0] == '/' || str[0] == '*' || str[0] == '^') {
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
    printf("Syntax Error: unknown symbol: ");
    print_invalid_str(str, (*to_size) + 1);
    printf("\n");
    exit(1);   
}


Node* compile_ast(Token* tokens, size_t len) {
    Node* node;
    size_t highest_i = get_highest_op(tokens, len);
    double num;
    switch (tokens[highest_i].type) {
        case OPERATOR:
            switch (tokens[highest_i].value[0]) {
                case '+':
                    node = create_node_next(NULL, NULL, op_add);                                 
                    break;       
                case '-':
                    node = create_node_next(NULL, NULL, op_sub);                                 
                    break;
                case '*':
                    node = create_node_next(NULL, NULL, op_mul);                                 
                    break;
                case '/':
                    node = create_node_next(NULL, NULL, op_div);                                 
                    break;
                case '^':
                    node = create_node_next(NULL, NULL, op_pow);                                 
                    break;
        
            }
            
            node->value.next.l_node = compile_ast(tokens, highest_i);
            node->value.next.r_node = compile_ast(tokens + highest_i + 1, len - highest_i - 1);
            break;
        case VALUE:
            num = str_to_double(tokens[highest_i].value, tokens[highest_i].len);            
            node = create_node_num(num);
            break;
    }
    return node;
}

size_t get_highest_op(Token* tokens, size_t len) {
    size_t highest_i = 0;
    Token* highest = &tokens[0];
    for (size_t i = len - 1; i > 0; i--) {
        if (get_token_level(&tokens[i]) > get_token_level(highest)) {
            highest = &tokens[i];
            highest_i = i;
        }
    }
    return highest_i;
    
}

int get_token_level(Token* token) {
    switch(token->type) {
        case OPERATOR:
            switch(token->value[0]) {
                case '+':
                case '-':
                    return 3;
                case '*':
                case '/':
                    return 2;
                case '^':
                    return 1;
            }
            break;
        case VALUE:
            return 0;
            break;
    }
    return -1;
}

double str_to_double(char* str, size_t len) {
    char* new_str = malloc(sizeof(char) * (len + 1));
    if (new_str == NULL) {
        fprintf(stderr, "Failed to allocate memory!");
        return 0;
    }
    for (int i = 0; i < len; i++) {
        new_str[i] = str[i];
    }
    new_str[len] = '\0';

    double res = strtod(new_str, NULL);
    
    free(new_str);

    return res;
}
