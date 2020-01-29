#ifndef CPU_H
#define CPU_H


#include "opcode.h"
#include "ops.h"
#include "build_constants.h"
#include "regpair.h"
#include "regs.h"
#include "psw.h"
#include <vector>
#include <stack>


#include <functional>

class CPU{
	private:
		unsigned short pop_count, push_count;
        static const unsigned char REG_COUNT = g_TOTAL_REG_COUNT;
		static const unsigned short STACK_SIZE = g_STACK_SIZE;
		static const unsigned short MEM_SIZE = g_MEM_SIZE;
		static const std::function<void(unsigned char, CPU *)> ftab[OPS::F_COUNT];
    protected:
		unsigned char * mem; //memory for constants and code
        std::vector<unsigned char> * stack;
        /*
         * the 'stack' is a vector because traditional stack data structures are not random access
         * however a vector is a good alternative because it has the same operations as a stack
         * e.g push pop but also allows random access for updating the GUI's widgets
         */
		unsigned char REGISTERS[REG_COUNT];
		PSW psw;
	public:
        bool abort; //whether the CPU can be executed or not
		CPU();
		~CPU();
		void tick();
		void reset();
		void load(const char * const file_name);
        const unsigned char* const get_regs() const;
		const unsigned short get_pop_count() const;
		const unsigned short get_push_count() const;
		const unsigned short get_reg_count() const;
        const std::vector<unsigned char> * get_stack() const;
		const PSW get_psw() const;
		const unsigned char * const get_mem() const;
};

#endif
