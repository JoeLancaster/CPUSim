#include "assembler_strings.h"
#include "opcode_not_found_exception.h"
#include "register_not_found_exception.h"

namespace assembler_strings{
        //simple linear searches through the arrays to look for the specified register/opcode
        unsigned char findReg(std::string & reg){
            for(unsigned short i = 0; i < g_TOTAL_REG_COUNT; i++){
                if(reg.compare(regs.at(i)) == 0){
                    return i;
                }
            }
            throw register_not_found_exception(reg);
        }
        unsigned char findOp(std::string & op){
            for(unsigned short i = 0; i < OPS::F_COUNT; i++){
                if(op.compare(ops.at(i)) == 0){
                    return i;
                }
            }
            throw opcode_not_found_exception(op);
        }
}
