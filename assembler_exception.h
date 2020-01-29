#ifndef ASSEMBLER_EXCEPTION_H
#define ASSEMBLER_EXCEPTION_H

#include <exception>
#include <string>


class assembler_exception : public std::exception {
    private:
        std::string line;
    public:
        assembler_exception(std::string & line){
            this -> line = line;
        }
        virtual const char * what() const throw(){
            std::string temp = "Invalid line: ";
            temp.append(line);
            return temp.c_str();
        }
};

#endif
