#include "ir/ir_operand.h"

#include <string>
#include <utility>
#include <vector>

ir::Operand::Operand(std::string  n, Type t): name(std::move(n)), type(t) {};
// bool ir::Operand::isNull(){return type == Type::null;}

