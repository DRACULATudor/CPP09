#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

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
    bool has_odd_elem = false;

    if (to_conv[0] && !isdigit(to_conv[0][0]))
        to_conv++;
    for(size_t i = 0; to_conv[i]; i++)
        _orig.push_back(atol(to_conv[i]));
    if (_orig.size() % 2  != 0)
    {
        has_odd_elem = true;
    }
    for (size_t i = 0; i < _orig.size() - 1; i += 2)
    {
        if (has_odd_elem && i + 1 ==  _orig.size() - 1)
        {
            _vec.push_back(std::make_pair(_orig[i], -1));
        }
        else
        {
            _vec.push_back(std::make_pair(_orig[i], _orig[i + 1]));
        }
    }
    startFordJhon(_orig);
}

void PmergeMe::startFordJhon(std::vector<unsigned int> orig)
{
    (void)orig;

    std::vector<std::pair<unsigned int, unsigned int> >::iterator it;
    for (it = _vec.begin(); it != _vec.end(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
}

PmergeMe::~PmergeMe() {}
