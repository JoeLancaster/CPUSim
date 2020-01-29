#ifndef REGS_H
#define REGS_H

#include "build_constants.h"

enum : unsigned char{
    A = g_GENERAL_REG_COUNT, //enum for the specialised registers
    PC,
    SP
};

#endif // REGS_H
