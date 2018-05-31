//
// Created by WuJiang on 2018/5/31.
//

#ifndef SPLCOMPILER_COMMON_H
#define SPLCOMPILER_COMMON_H

#define INTEGER int
#define REAL float
#define CHAR char
#define BOOLEAN bool
#define ADDRESS long

// 双目：依次为 加 减 乘 除 整除 取余 与 或 非
#define OP_ADD 0
#define OP_MINUS 1
#define OP_MULTI 2
#define OP_RDIV 3
#define OP_DDIV 4
#define OP_MOD 5
#define OP_AND 6
#define OP_OR 7
#define OP_NOT 8
// 单目：依次为 取反 绝对值 前驱 后继 奇偶判定 转字符 转Ascii码
#define OP_OPPO 20
#define OP_ABS 21
#define OP_PRED 22
#define OP_SUCC 23
#define OP_ODD 24
#define OP_CHR 25
#define OP_ORD 26

#endif //SPLCOMPILER_COMMON_H
