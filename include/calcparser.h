#ifndef _CALC_PARSER_H_
#define _CALC_PARSER_H_

#include <stdbool.h>

enum calc_opcode {
    add,
    subtract,
    multiply,
    divide,
    modulo
};

enum calc_status {
    ok,
    invalid_paran
};

struct calc_node {
    int left_is_num;
    int right_is_num;
    float left_num_val;
    float right_num_val;
    struct calc_node* left;
    struct calc_node* right;
    enum calc_opcode opcode;
};

float calc_evaluate(struct calc_node* root_node);

struct calc_node* calc_tree_new();

int calc_count_nodes(struct calc_node* root_node);

enum calc_status calc_tree_populate(char* expression, struct calc_node* tree);

bool calc_tree_free(struct calc_node* tree);

#endif