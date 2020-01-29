#ifndef ASSEMBLER_STRINGS_H
#define ASSEMBLER_STRINGS_H

#include <string>
#include <array>
#include "ops.h"
#include "build_constants.h"
#include <iostream>

namespace assembler_strings{
        //arrays used by the assembler
        const std::array<std::string, OPS::F_COUNT> ops = {
            "ADD",
            "AND",
            "JMP",
            "JZ",
            "JNZ",
            "JNE",
            "JE",
            "OR",
            "SUB",
            "XOR",
            "PUSH",
            "POP",
            "SL",
            "SR",
            "HLT",
            "LD",
            "MV",
            "INC",
            "DEC",
        };
        const std::array <std::string, g_TOTAL_REG_COUNT> regs = {
            "R0",
            "R1",
            "R2",
            "R3",
            "R4",
            "R5",
            "R6",
            "R7",
            "R8",
            "R9",
            "A",
            "PC",
            "SP"
        };
        extern unsigned char findReg(std::string &);
        extern unsigned char findOp(std::string &);
}

#endif // OPCODE_STRINGS_H
