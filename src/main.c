#include "calcparser.h"
#include <stdio.h>

int main() {
    struct calc_node* expressionTree = calc_tree_new();
    calc_tree_populate("5 + 3 ", expressionTree);
    printf("Value: %.2f\n", calc_evaluate(expressionTree));
    calc_tree_free(expressionTree);
}