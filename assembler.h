#ifndef ASSEMBLER_H
#define ASSEMBLER_H

//#include <boost/xpressive/xpressive.hpp>
#include <QRegExp>
#include "assembler_exception.h"
#include "assembler_strings.h"
#include <sstream>
#include <iostream>
#include "opcode.h"

namespace Assembler{
        bool validate(std::string);
        const QRegExp syntax_regex("HLT$|[A-Z]+:(\\d+|(R[0-9]{1}|A|SP|PC)$)"); //validates syntax
        opcode assemble_line(std::string & line){
            if(!validate(line)){
                throw assembler_exception(line);
            }
            else{
                unsigned int colon_index = line.find_first_of(':');
                std::string code = line.substr(0, colon_index);       //split the string at the colon to get the opcode and operand
                std::string operand = line.substr(colon_index + 1);
                opcode assembled_op;
                assembled_op.code = assembler_strings::findOp(code);
                if(isdigit(operand[0]) == 0){
                    assembled_op.target = assembler_strings::findReg(operand); //operands are either RX or XXX where x is a number. this checks to see if it should assemble
                                                                               //an integer literal or a register
                }
                else{
                    assembled_op.target = atoi(operand.c_str());
                }
                return assembled_op;
            }
        }
        bool validate(std::string line){
            return syntax_regex.exactMatch(line.c_str());
        }
        std::string clean(std::string line){ //the assemble_line function assumes only correctly formatted input so this function removes all comments and whitespace
            std::stringstream clean_string;
            foreach(char c, line){
                if(c == ';'){
                    return clean_string.str();
                }
                if(c != ' ' && c != '\t'){
                    clean_string << c;
                }
            }
            return clean_string.str();
        }
}


#endif // ASSEMBLER_H
