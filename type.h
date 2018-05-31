//
// Created by WuJiang on 2018/5/31.
//

#ifndef SPLCOMPILER_TYPE_H
#define SPLCOMPILER_TYPE_H

#include <string>
#include <vector>
#include "common.h"

#define tInt 0
#define tReal 1
#define tChar 2
#define tBoolean 3
#define tSet 4
#define tArray 5
#define tRecord 6

class Type {
    std::string name; // use what name to find this value, may be empty
    int baseType; // 0: int 1: real 2: char 3: boolean 4: set 5: array 6: record 7~n: other type defined by user
    int childrenNum; // the number of children
    std::vector<Type> childType; // a list of the type of children
};

int add_type();

extern std::vector<Type> typeList;

#endif //SPLCOMPILER_TYPE_H
