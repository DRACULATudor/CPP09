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
    _has_odd = false;

    if (to_conv[0] && !isdigit(to_conv[0][0]))
        to_conv++;
    for(size_t i = 0; to_conv[i]; i++)
        _orig.push_back(atol(to_conv[i]));
    if (_orig.size() % 2  != 0)
    {

        _has_odd = true;
    }
    for (size_t i = 0; i < _orig.size() - 1; i += 2)
    {
        _vec.push_back(std::make_pair(_orig[i], _orig[i + 1]));
    }
    if (_has_odd)
    {
        _the_od_elem = _orig[_orig.size() - 1];
    }

    startFordJhon(_orig);
}

std::vector<std::pair<unsigned int, unsigned int> > PmergeMe::MergeCompPairs(std::vector<std::pair<unsigned int, unsigned int> > left, std::vector<std::pair<unsigned int, unsigned int> > right)
{

    std::vector<std::pair<unsigned int, unsigned int> >::iterator left_it = left.begin();
    std::vector<std::pair<unsigned int, unsigned int> >::iterator right_it = right.begin();
    std::vector<std::pair<unsigned int, unsigned int> > mainchain;

    std::cout << "here\n";
    while (left_it != left.end() && right_it != right.end())
    {
        if (left_it->first <= right_it->first)
        {
            mainchain.push_back(*left_it);
            ++left_it;
        }
        else
        {
            mainchain.push_back(*right_it);
            ++right_it;
        }
    }
    while (left_it != left.end())
    {
        mainchain.push_back(*left_it);
        ++left_it;
    }
    while (right_it != right.end())
    {
        mainchain.push_back(*right_it);
        ++right_it;
    }
    std::vector<std::pair<unsigned int, unsigned int> >::iterator it;
    for (it = mainchain.begin(); it != mainchain.end(); ++it)
    {
        std::cout << it->first << " " << it->second <<"   ";
    }

    return mainchain;
}


std::vector<std::pair<unsigned int, unsigned int> >
PmergeMe::startRecMerging(std::vector<std::pair<unsigned int, unsigned int> > vec)
{
    size_t mid = vec.size() / 2;
    std::vector<std::pair<unsigned int, unsigned int> > left(vec.begin(), vec.begin() + mid);
    std::vector<std::pair<unsigned int, unsigned int> > right(vec.begin() + mid, vec.end());
    left = startRecMerging(left);
    right = startRecMerging(right);

    return MergeCompPairs(left, right);
}

void PmergeMe::startFordJhon(std::vector<unsigned int> orig)
{
    (void)orig;
    
    
    std::vector<std::pair<unsigned int, unsigned int> >::iterator it;
    for (it = _vec.begin(); it != _vec.end(); ++it)
    {
        if (it->first < it->second)
        {
            std::swap(it->first, it->second);
        }
    }
    if (_has_odd)
    {
        std::cout << _the_od_elem << "\n";
    }
    startRecMerging(_vec);
}

PmergeMe::~PmergeMe() {}
