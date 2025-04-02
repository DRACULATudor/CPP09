#pragma once
#include <cstdlib>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream>
#include <sstream>


class RPN
{
private:
    std::stack<int> _stck;
public:
    RPN();
    RPN(const RPN &copy);
    RPN &operator=(const RPN &assign);
    void addToStck(std::string val);
    void StartStack(std::string ecuasion);
    ~RPN();
};

//"8 9 * 9 - 9 - 9 - 4 - 1 +"