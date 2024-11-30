#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "parser.h"
#include "util.h"


int main() {    
    printf("\n--- Calculator ---\nEquation: ");
    char* str = get_line();
    size_t token_len = 0;

    Token* tokens = tokenize_str(str, &token_len);
    Node* ast = compile_ast(tokens, token_len);    
    ast = compute_node(ast);
    
    printf("Result: %g\n", ast->value.num);
    
    free(ast);
    free(tokens);
    free(str);
    return 0;
}
