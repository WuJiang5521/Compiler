/*
 * translate.h
 * Copyright (C) 2018 weihao <blackhatdwh@gmail.com>
 *
 * Distributed under terms of the MIT license.
 * used to translate concrete syntax tree to abstract syntax tree
 */

#ifndef TRANSLATE_H
#define TRANSLATE_H
#include "tree.h"
#include "cst.h"

#define DEFAULT_INT = 0;
#define DEFAULT_LONG = 0;
#define DEFAULT_CHAR = 0;
#define DEFAULT_STRING = "";
#define DEFAULT_PTR = nullptr

using namespace ast;

class Translator {
public:
    static Base* translate(cst_tree tree);
};


#endif /* !TRANSLATE_H */
