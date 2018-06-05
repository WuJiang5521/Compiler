/*
 * symtab.h
 * Copyright (C) 2018 weihao <blackhatdwh@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SYMTAB_H
#define SYMTAB_H

#define ID_MAX_LEN 50
#define SYM_TAB_LEN 50

struct symTabNode {
    char id[ID_MAX_LEN];
    char type;
};

typedef struct symTabNode sym_tab_node;
typedef struct symTabNode* sym_tab_node_ptr;


#endif /* !SYMTAB_H */
