#include <stdio.h>
#include <stdlib.h>

#include "node.h"

Node* create_node_num(double num) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (n == NULL) {        
        fprintf(stderr, "Failed to allocate memory!");                    
        return 0;   
    }
    n->has_num = true;
    n->value.num = num;
    return n;
} 

Node* create_node_next(Node* r_node, Node* l_node, double (*func)(double, double)) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (n == NULL) {        
        fprintf(stderr, "Failed to allocate memory!");                    
        return 0;   
    }        
    n->has_num = false;
    n->value.next.r_node = r_node;
    n->value.next.l_node = l_node;
    n->value.next.func = func;

    return n;
}

Node* compute_node(Node* node) {
    if (node->has_num) { return node; } 
    //compute the other nodes if they have no values
    Node* r_node = compute_node(node->value.next.r_node);
    Node* l_node = compute_node(node->value.next.l_node);

    
    
    //do the computing (and then he said "It's computing time!" and computed all over the place)
    double l_val = l_node->value.num;
    double r_val = r_node->value.num;
 
    double res = node->value.next.func(l_val, r_val);
    //printf("Res: %lf, r_val %lf, l_val %lf\n", res, r_val, l_val);
    free(node);
    free(r_node);
    free(l_node);

    return create_node_num(res);
}
