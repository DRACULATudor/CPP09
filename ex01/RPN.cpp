#include "RPN.hpp"

RPN::RPN() : _stck(){}

RPN::RPN(const RPN &copy) : _stck(copy._stck){}

RPN  &RPN::operator=(const RPN &assign)
{
    if (this != &assign)
        this->_stck = assign._stck;
    return *this;
}

void RPN::addToStck(std::string val)
{
    int dot_count = 0;
    for (size_t i = 0; i < val.length(); ++i)
    {
        if (isdigit(val[i]))
        {

            return false;
        }
    }
    if (dot_count > 1)
        return false;
    
    return true;
}

void RPN::StartStack(std::string ecuasion)
{
    for (size_t i = 0; i < ecuasion.length(); i++)
    {
        addToStck(ecuasion);
    }
    
}

RPN::~RPN(){}
