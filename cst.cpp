/*
 * cst.cpp
 * Copyright (C) 2018 weihao <blackhatdwh@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "cst.h"
#include <stdlib.h>

cst_tree create_node(int ival, int case_id, cst_tree t1, cst_tree t2, cst_tree t3, cst_tree t4, cst_tree t5) {
    cst_node* new_node = (cst_node*)malloc(sizeof(cst_node));
    new_node->item = ival;
    new_node->node_id = case_id;
    new_node->first = t1;
    new_node->second = t2;
    new_node->third = t3;
    new_node->fourth = t4;
    new_node->fifth = t5;
    return new_node;
}
