#ifndef CPU_EXCEPTION_H
#define CPU_EXCEPTION_H

#include "runtime_exception.h"
#include "assembler_strings.h"

class cpu_exception : public runtime_exception {
        using runtime_exception::runtime_exception; //gives us access to the superclass constructor
    public:
        virtual const char * what() const throw(){
            std::string temp = "The CPU threw an exception with the opcode: ";
            temp.append(assembler_strings::ops[this->op.code]);
            temp.append(" and operand: ");
            temp.append(std::to_string((unsigned short) this->op.target));
            temp.append("\n");
            temp.append("At memory location: ");
            temp.append(std::to_string(this->memloc));
            return temp.c_str();
        }
};

#endif // CPU_EXCEPTION_H
