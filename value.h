//
// Created by WuJiang on 2018/5/31.
//

#ifndef SPLCOMPILER_VALUE_H
#define SPLCOMPILER_VALUE_H

#include <string>
#include <vector>
#include "common.h"

class Value {
public:
    int base_type; // 0: int 1: real 2: char 3: boolean 4: set 5: array 6: record
    ADDRESS address;
    union return_value {
        INTEGER integer_value;
        REAL real_value;
        CHAR char_value;
        BOOLEAN boolean_value;
        std::vector<Value*> children_value; // a list of the value of children
    } val;
};

#endif //SPLCOMPILER_VALUE_H
