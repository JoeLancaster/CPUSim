#include "mutable_cpu.h"

void mutable_CPU::set_reg(unsigned char reg, unsigned char value){
    this -> REGISTERS[reg] = value;
}
void mutable_CPU::set_mem(unsigned char memloc, unsigned char value){
    this -> mem[memloc] = value;
}
void mutable_CPU::assign_mem(unsigned char * mem){
    this -> mem = mem;
}
void mutable_CPU::assign_stack(std::vector<unsigned char> * stack){
    this -> stack = stack;
}
void mutable_CPU::set_PSW(PSW psw){
    this -> psw = psw;
}
