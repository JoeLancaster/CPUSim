#ifndef MUTABLE_CPU_H
#define MUTABLE_CPU_H

#include "cpu.h"
#include "psw.h"

class mutable_CPU : public CPU{
    public:
        void set_reg(unsigned char, unsigned char);
        void set_mem(unsigned char, unsigned char);
        void assign_mem(unsigned char *);
        void assign_stack(std::vector<unsigned char> *);
        void set_PSW(PSW psw);
        //void set_IO(unsigned char);
};

#endif
