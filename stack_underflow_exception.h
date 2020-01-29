#ifndef STACK_UNDERFLOW_EXCEPTION_H
#define STACK_UNDERFLOW_EXCEPTION_H

#include "runtime_exception.h"

class stack_underflow_exception : public runtime_exception {
        using runtime_exception::runtime_exception;
    public:
        virtual const char * what() const throw(){
            std::string temp = "Stack underflow exception\n";
            temp.append("with opcode: ");
            temp.append(assembler_strings::ops[this->op.code]);
            temp.append(" and operand: ");
            temp.append(assembler_strings::regs[this->op.target]);
            temp.append("\n");
            temp.append("At memory location: ");
            temp.append(std::to_string(this->memloc));
            return temp.c_str();
        }

};

#endif // STACK_UNDERFLOW_EXCEPTION_H
