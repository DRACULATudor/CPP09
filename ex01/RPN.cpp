#include "RPN.hpp"

RPN::RPN() : _stck() {}

RPN::RPN(const RPN &copy) : _stck(copy._stck) {}

RPN &RPN::operator=(const RPN &assign)
{
    if (this != &assign)
        this->_stck = assign._stck;
    return *this;
}

int doRPN(int firstelem, int secondelem, char sign)
{
    if (sign == '-')
    {
        return firstelem - secondelem;
    }
    else if (sign == '+')
    {
        return firstelem + secondelem;
    }
    else if (sign == '*')
    {
        return firstelem * secondelem;
    }
    else if (sign == '/' && secondelem != 0)
    {
        return firstelem / secondelem;
    }
    else if (sign == '/' && secondelem == 0)
    {
        std::cerr << "Error: Division by zero is not allowed !" << std::endl;
        return -1;
    }
    else
    {
        std::cerr << "Error: Invalid operator !" << std::endl;
        return -1;
    }
}

void RPN::StartStack(std::string ecuasion)
{
    std::stringstream strstr;
    int firstelem = 0;
    int secondelem = 0;
    int val = 0;
    for (size_t i = 0; i < ecuasion.length(); ++i)
    {
        if (isdigit(ecuasion[i]))
        {
            strstr.clear();
            strstr.str("");
            strstr << ecuasion[i];
            strstr >> val;
            if (val > 9)
            {
                std::cerr << "Error: only single digits allowed !" << std::endl;
                return;
            }
            _stck.push(val);
        }
        else if (ecuasion[i] == '-' || ecuasion[i] == '+' || ecuasion[i] == '/' || ecuasion[i] == '*')
        {
            if (_stck.size() < 2)
            {
                std::cerr << "Error: Invalid number of elements in the stack !" << std::endl;
                return;
            }
            secondelem = _stck.top();
            _stck.pop();
            firstelem = _stck.top();
            _stck.pop();
            int rez = doRPN(firstelem, secondelem, ecuasion[i]);
            _stck.push(rez);
        }
        else if (ecuasion[i] == ' ')
        {
            continue;
        }
        else
        {
            std::cerr << "Error: Invalid character !" << std::endl;
            return;
        }
    }
    if (_stck.size() != 1)
    {
        std::cerr << "Error: Invalid RPN !" << std::endl;
        return;
    }
    std::cout << _stck.top() << std::endl;
    return;
}

RPN::~RPN() {}
