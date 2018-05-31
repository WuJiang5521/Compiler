//
// Created by WuJiang on 2018/5/31.
//

#ifndef SPLCOMPILER_TYPE_H
#define SPLCOMPILER_TYPE_H

#include <string>
#include <vector>
#include "common.h"

#define T_INTEGER 0
#define T_REAL 1
#define T_CHAR 2
#define T_BOOLEAN 3
#define T_SET 4
#define T_ARRAY 5
#define T_RECORD 6

class Type {
    std::string name; // use what name to find this value, may be empty
    int base_type; // 0: int 1: real 2: char 3: boolean 4: set 5: array 6: record 7~n: other type defined by user
    int children_num; // the number of children
    std::vector<Type> child_type; // a list of the type of children
};

int addType();

extern std::vector<Type> type_list;

#endif //SPLCOMPILER_TYPE_H
