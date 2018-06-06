//
// Created by WuJiang on 2018/5/31.
//

#ifndef SPLCOMPILER_COMMON_H
#define SPLCOMPILER_COMMON_H
#include <string>

#define INTEGER int
#define REAL float
#define CHAR char
#define BOOLEAN bool
#define ADDRESS unsigned long

// 双目：依次为 加 减 乘 除 整除 取余 与 或 非 小于 大于 小于等于 大于等于 等于 不等于
#define OP_ADD 0
#define OP_MINUS 1
#define OP_MULTI 2
#define OP_RDIV 3
#define OP_DDIV 4
#define OP_MOD 5
#define OP_AND 6
#define OP_OR 7
#define OP_SMALL 8
#define OP_LARGE 9
#define OP_SMALL_EQUAL 10
#define OP_LARGE_EQUAL 11
#define OP_EQUAL 12
#define OP_NOT_EQUAL 13
#define OP_DOT 14
#define OP_INDEX 15
// 单目：依次为 取反 绝对值 前驱 后继 奇偶判定 转字符 转Ascii码
#define OP_OPPO 20
#define OP_NOT 21
#define OP_ABS 22
#define OP_PRED 23
#define OP_SUCC 24
#define OP_ODD 25
#define OP_CHR 26
#define OP_ORD 27
#define OP_SQR 28
#define OP_SQRT 29

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
        case OP_NOT:
            return "!";
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
        case OP_SQR:
            return "sqr";
        case OP_SQRT:
            return "sqrt";
    }
}

#endif //SPLCOMPILER_COMMON_H
