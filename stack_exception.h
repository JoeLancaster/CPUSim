#ifndef STACK_EXCEPTION_H
#define STACK_EXCEPTION_H

#include "runtime_exception.h"
#include "assembler_strings.h"
#include "opcode.h"

class stack_exception : public runtime_exception {
    protected:
        unsigned char stack_size;
    public:
        explicit stack_exception(opcode op, unsigned short memloc, unsigned char stack_size){
            this->op = op;
            this->memloc = memloc;
            this->stack_size = stack_size;
        }

};


#endif // STACK_EXCEPTION_H
