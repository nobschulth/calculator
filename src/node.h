#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct Node Node;

typedef union Value {
    struct {
        double (*func)(double, double); //the function that gets executed on the r and l values (the first double is the l_value, the second the r_value)
        Node* r_node;
        Node* l_node;
    } next;   
    double num; //a number
} Value;

struct Node {
    Value value;
    bool has_num; //if false: has adjacent nodes 
}; 

Node* create_node_num(double num); //creates a node by a double
Node* create_node_next(Node* r_node, Node* l_node, double (*func)(double, double)); //creates node by adjacent nodes and an operator function
Node* compute_node(Node* node); //recursively calculates the result of the node tree
#endif
