#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
    _vec = copy._vec;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &assign)
{
    if (this != &assign)
        _vec = assign._vec;
    return *this;
}

void loadVector(char **to_conv)
{
    for (size_t i = 0; i < ; i++)
    {
    }    
}

PmergeMe::~PmergeMe(){}
