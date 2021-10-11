#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "calcparser.h"

float calc_evaluate(struct calc_node* node) {
    float left, right;
    if (node->left_is_num) {
        left = node->left_num_val;
    } else {
        left = calc_evaluate(node->left);
    }
    if (node->right_is_num) {
        right = node->right_num_val;
    } else {
        right = calc_evaluate(node->right);
    }
    switch (node->opcode) {
        case add:
            return left + right;
        case subtract:
            return left - right;
        case multiply:
            return left * right;
        case divide:
            return left / right;
        case modulo:
            return (int)left % (int)right;
        default:
            return -1.f;
    }
}

struct calc_node* calc_tree_new() {
    struct calc_node* tree = malloc(sizeof(struct calc_node));
    tree->left_is_num = false;
    tree->left = 0;
    tree->right_is_num = false;
    tree->right = 0;
    return tree;
}

int calc_count_nodes(struct calc_node* root_node) {
    int count = 0;
    if (root_node->left_is_num) {
        count++;
    } else {
        count += calc_count_nodes(root_node->left);
    }
    if (root_node->right_is_num) {
        count++;
    } else {
        count += calc_count_nodes(root_node->right);
    }
    return count;
}

enum calc_status calc_tree_populate(char* expression, struct calc_node* tree) {
    char* expr_cpy = malloc(sizeof(*expression));
    strcpy(expr_cpy, expression);

    char num_buffer[100];
    int num_loc = -1;

    bool in_paran = false;
    int paran_depth = 0;

    do {
        char current = *expr_cpy;
        
        if (isspace(current)) {
            if (num_loc != -1) {
                /* end of number */
                num_buffer[++num_loc] = '\0';
                num_loc = -1;
                printf("Found number token: %s\n", num_buffer);
                if (!tree->left_is_num) {
                    tree->left_num_val = atof(num_buffer);
                    tree->left_is_num = true;
                } else {
                    tree->right_num_val = atof(num_buffer);
                    tree->right_is_num = true;
                }
            }
            continue;
        }

        if (isdigit(current) || current == '-' || current == '.') {
            /* number */
            num_buffer[++num_loc] = current;
            continue;
        }

        switch (current) {
            case '(':
                in_paran = true;
                paran_depth++;
                continue;
            case ')':
                if (!in_paran) {
                    return invalid_paran;
                }
                in_paran = true;
                paran_depth--;
                continue;
            case '+':
                tree->opcode = add;
                continue;
            case '-':
                tree->opcode = subtract;
                continue;
            case '*':
                tree->opcode = multiply;
                continue;
            case '/':
                tree->opcode = divide;
                continue;
            case '%':
                tree->opcode = modulo;
                continue;
        }

    } while (*++expr_cpy);

    if (paran_depth) {
        return invalid_paran;
    }

    printf("Populating calc tree with expression \"%s\" with %d nodes\n", expression, calc_count_nodes(tree));
    return ok;
}

bool calc_tree_free(struct calc_node* tree) {
    if (tree == NULL) {
        return false;
    }
    
    if (!tree->left_is_num) {
        calc_tree_free(tree->left);
    }
    
    if (!tree->right_is_num) {
        calc_tree_free(tree->right);
    }

    free(tree);

    return true;
}