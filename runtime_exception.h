#ifndef RUNTIME_EXCEPTION_H
#define RUNTIME_EXCEPTION_H

#include <exception>
#include "opcode.h"

class runtime_exception : public std::exception {
    protected:
        opcode op;
        unsigned short memloc;
    public:
        explicit runtime_exception(opcode op, unsigned short memloc){
            this->op = op;
            this->memloc = memloc;
        }
};

#endif // RUNTIME_EXCEPTION_H
