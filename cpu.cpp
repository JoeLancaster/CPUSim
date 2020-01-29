#include "cpu.h"
#include "stack_overflow_exception.h"
#include "stack_underflow_exception.h"
#include <string.h>

const std::function<void(unsigned char, CPU*)> CPU::ftab[OPS::F_COUNT] = {
    [](unsigned char reg, CPU * c){c -> REGISTERS[A] += c -> REGISTERS[reg];},
    [](unsigned char reg, CPU * c){c -> REGISTERS[A] &= c -> REGISTERS[reg];},
    [](unsigned char target, CPU * c){c -> REGISTERS[PC] = target;},
    [](unsigned char target, CPU * c){if(c -> psw.Z == 1){c -> REGISTERS[PC] = target;}},
    [](unsigned char target, CPU * c){if(c -> psw.Z == 0){c -> REGISTERS[PC] = target;}},
    [](unsigned char target, CPU * c){if(c -> REGISTERS[0] != c -> REGISTERS[A]){c -> REGISTERS[PC] = target;}},
    [](unsigned char target, CPU * c){if(c -> REGISTERS[0] == c -> REGISTERS[A]){c -> REGISTERS[PC] = target;}},
    [](unsigned char reg, CPU * c){c -> REGISTERS[A] |= c -> REGISTERS[reg];},
    [](unsigned char reg, CPU * c){c -> REGISTERS[A] -= c -> REGISTERS[reg];},
    [](unsigned char reg, CPU * c){c -> REGISTERS[A] ^= c -> REGISTERS[reg];},
    [](unsigned char reg, CPU * c){c -> stack -> push_back(c -> REGISTERS[reg]); c -> REGISTERS[SP]++;},
    [](unsigned char reg, CPU * c){c -> REGISTERS[reg] = c -> stack -> back();c -> stack -> pop_back();c -> REGISTERS[SP]--;},
    [](unsigned char reg, CPU * c){c -> REGISTERS[reg] <<= 1;},
    [](unsigned char reg, CPU * c){c -> REGISTERS[reg] >>= 1;},
    [](unsigned char reg, CPU * c){c -> abort = true;},
    [](unsigned char data, CPU * c){c -> REGISTERS[A] = data;},
    [](unsigned char reg, CPU * c){c -> REGISTERS[reg] = c -> REGISTERS[A];},
    [](unsigned char reg, CPU * c){c -> REGISTERS[reg]++;},
    [](unsigned char reg, CPU * c){c -> REGISTERS[reg]--;}
    /*
     * this is an array of lambda functions that represent all of the CPU's instructions
     * they are in the exact same order as the OPS enum so they can be accessed that way
     * using this method allows for the elimination of an extremely long if else tree
     * all functions are passed a pointer to a CPU object since they are not member functions of the class
     * and hence do not have access to the 'this' pointer. Though the functionality is the exact same, they just have to be passed 'this' explicitly.
     */
};

CPU::CPU(){
    this -> pop_count = this -> push_count = this -> abort = 0;
    this -> stack = new std::vector<unsigned char>();
    this -> mem = new unsigned char[this -> MEM_SIZE];
    memset(mem, 0, this -> MEM_SIZE);
	memset(this -> REGISTERS, 0, REG_COUNT);
}
CPU::~CPU(){
    delete stack;
    delete[] mem;
}
void CPU::reset(){
    delete stack;
    this -> pop_count = this -> push_count = this -> abort = 0;
    this -> stack = new std::vector<unsigned char>();
    memset(mem, 0, MEM_SIZE);
    memset(this -> REGISTERS, 0, REG_COUNT);
}
void CPU::tick(){
    static opcode op;
    op.code = mem[REGISTERS[PC]];
    op.target = mem[++REGISTERS[PC]];
    if(op.code == OPS::PUSH && this->REGISTERS[SP] == 255){
        this->abort = true;
        throw stack_overflow_exception(op, this->REGISTERS[PC]);
    }
    else if(op.code == OPS::POP && this->REGISTERS[SP] == 0){
        this->abort = true;
        throw stack_underflow_exception(op, this->REGISTERS[PC]);
    }
    REGISTERS[PC]++;
    ftab[op.code](op.target, this); //calls the lambda function equal to op.code
    if(this -> REGISTERS[A] == 0){ //sets the "zero" register
        psw.Z = 1;
    }
    else{
        psw.Z = 0;
    }
}
void CPU::load(const char * const file_name){
    /*
        Since the CPU's memory is just a contiguous 256 bytes in memory,
        C's file IO is more appropriate.
    */
    FILE * program_file;
    program_file = fopen(file_name, "rb"); //open file in binary mode.
    long int file_size = 0;
    if(file_size > 255){
        return;
    }
    fseek(program_file, 0, SEEK_END);
    file_size = ftell(program_file);
    fseek(program_file, 0, SEEK_SET);
    fread(mem, file_size, 1, program_file);
    fclose(program_file);
}
//simple 'getter' functions
const unsigned char* const CPU::get_regs() const{
	return this -> REGISTERS;
}
const unsigned short CPU::get_pop_count() const{
	return this -> pop_count;
}
const unsigned short CPU::get_push_count() const{
	return this -> push_count;
}
const unsigned short CPU::get_reg_count() const{
	return this -> REG_COUNT;
}
const std::vector<unsigned char> * CPU::get_stack() const{
    return this -> stack;
}
const PSW CPU::get_psw() const{
	return this -> psw;
}
const unsigned char * const CPU::get_mem() const{
    return this -> mem;
}
