#ifndef IROPERAND_H
#define IROPERAND_H

#include <string>
#include<vector>


namespace ir {

enum class Type {
    Int,
    Float,
    IntLiteral,
    FloatLiteral,
    IntPtr,
    FloatPtr,
    null
};

std::string toString(Type t);

struct Operand {
    std::string name;
    Type type;
    Operand(std::string = "null", Type = Type::null);

    // bool isNull();
};



}
#endif
