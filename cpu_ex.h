#ifndef CPU_EX_H
#define CPU_EX_H

#include "opcode.h"

#include <cstdlib>
#include <string>

class cpu_ex{
    private:
        char * msg;
        opcode op;
    public:
        std::string what() const throw();
        cpu_ex(char *, opcode);
};

#endif // CPU_EX_H
