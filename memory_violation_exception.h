#ifndef MEMORY_VIOLATION_EXCEPTION_H
#define MEMORY_VIOLATION_EXCEPTION_H

#include "runtime_exception.h"
#include "assembler_strings.h"

class memory_violation_exception : public runtime_exception {
        using runtime_exception::runtime_exception;
    public:
        virtual const char * what() const throw(){
            std::string temp = "The CPU tried to access an invalid memory location.\n";
            temp.append("Caused by opcode: ");
            temp.append(assembler_strings::ops[this->op.code]);
            temp.append(" and operand: ");
            temp.append(std::to_string(this->op.target));
            temp.append("\n");
            temp.append("At memory location: ");
            temp.append(std::to_string(this->memloc));
            return temp.c_str();
        }
};

#endif // MEMORY_VIOLATION_EXCEPTION_H
