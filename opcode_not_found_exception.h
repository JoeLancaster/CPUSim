#ifndef OPCODE_NOT_FOUND_EXCEPTION_H
#define OPCODE_NOT_FOUND_EXCEPTION_H


#include <exception>
#include <string>

class opcode_not_found_exception : public std::exception {
    private:
        std::string opcode;
    public:
        opcode_not_found_exception(std::string & opcode){
            this -> opcode = opcode;
        }
        virtual const char * what() const throw(){
            std::string temp;
            temp.append("Unknown opcode: ");
            temp.append(opcode);
            return temp.c_str();
        }
};


#endif // OPCODE_NOT_FOUND_EXCEPTION_H
