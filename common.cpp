/*
 * common.cpp
 * Copyright (C) 2018 weihao <blackhatdwh@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include "common.h"

extern int yylineno;

std::string getOpNameByID(int id) {
    switch (id) {
        case OP_ADD:
            return "+";
        case OP_MINUS:
            return "-";
        case OP_MULTI:
            return "*";
        case OP_RDIV:
            return "/";
        case OP_DDIV:
            return "//";
        case OP_MOD:
            return "%";
        case OP_AND:
            return "&&";
        case OP_OR:
            return "||";
        case OP_SMALL:
            return "<";
        case OP_LARGE:
            return ">";
        case OP_SMALL_EQUAL:
            return "<=";
        case OP_LARGE_EQUAL:
            return ">=";
        case OP_EQUAL:
            return "=";
        case OP_NOT_EQUAL:
            return "<>";
        case OP_DOT:
            return ".";
        case OP_INDEX:
            return "[]";
        case OP_OPPO:
            return "-";
        case OP_ABS:
            return "abs";
        case OP_PRED:
            return "pred";
        case OP_SUCC:
            return "succ";
        case OP_ODD:
            return "odd";
        case OP_CHR:
            return "chr";
        case OP_ORD:
            return "ord";
        case OP_NOT:
            return "!";
    }
}

void yyerror(const char *info) {
    fprintf(stderr, "line %d: %s\n", yylineno, info);
    exit(1);
}
