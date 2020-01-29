#ifndef OPS_H
#define OPS_H

namespace OPS{
    enum OPS : unsigned char {
        ADD = 0,
        AND, //1
        JMP, //2
        JZ,  //3 etc.
        JNZ,
        JNE,
        JE,
        OR,
        SUB,
        XOR,
        PUSH,
        POP,
        SL,
        SR,
        HLT,
        LD,
        MV,
        INC,
        DEC,
        F_COUNT //make sure this is always the last item in this enum.
    };
}

#endif
