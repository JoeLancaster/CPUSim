#ifndef REGISTER_NOT_FOUND_EXCEPTION_H
#define REGISTER_NOT_FOUND_EXCEPTION_H

#include <exception>

class register_not_found_exception : public std::exception {
    private:
        std::string reg;
    public:
        register_not_found_exception(std::string & reg){
            this -> reg = reg;
        }
        virtual const char * what() const throw(){
            std::string temp;
            temp.append("Unkown register: ");
            temp.append(reg);
            return temp.c_str();
        }

};

#endif // REGISTER_NOT_FOUND_EXCEPTION_H
