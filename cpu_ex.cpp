#include "cpu_ex.h"


cpu_ex::cpu_ex(char * msg, opcode op){
    this -> op = op;
    this -> msg = msg;
}
std::string cpu_ex::what() const throw(){
    std::string t_msg = "CPU Exception caught: ";
    t_msg += msg;
    t_msg += " via opcode: ";

    return t_msg;
}
