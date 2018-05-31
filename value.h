//
// Created by WuJiang on 2018/5/31.
//

#ifndef SPLCOMPILER_VALUE_H
#define SPLCOMPILER_VALUE_H

#include <string>
#include <vector>
#include "common.h"

class Value {
    int baseType; // 0: int 1: real 2: char 3: boolean 4: set 5: array 6: record
    Address address;
    union {
        Integer integerValue;
        Real realValue;
        Char charValue;
        Boolean booleanValue;
        std::vector<Value> childrenValue; // a list of the value of children
    };
};

#endif //SPLCOMPILER_VALUE_H
