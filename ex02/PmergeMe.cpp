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

void PmergeMe::loadVector(char **to_conv)
{
    if (to_conv[0] && !isdigit(to_conv[0][0]))
        to_conv++;
    for (size_t i = 0; to_conv[i]; i++)
    {
        _orig.push_back(atol(to_conv[i]));
    }
    startFordJhon();
}

void PmergeMe::startFordJhon()
{
    for (size_t i = 0; i < _orig.size(); i++)
    {
        std::cout << _orig[i] << " ";
    }
}

PmergeMe::~PmergeMe(){}
