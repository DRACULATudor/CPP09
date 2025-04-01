#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: wrong number of arguments !" << std::endl;
        return -1;
    }
    else
    {
        RPN start;
        start.StartStack(argv[1]);
    }
}