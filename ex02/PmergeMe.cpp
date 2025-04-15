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
    for (size_t i = 0; to_conv[i]; i++)
        _orig.push_back(atol(to_conv[i]));
    if (_orig.size() % 2 != 0)
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
        _orig.pop_back();
    }

    startFordJhon(_orig);
}

std::vector<std::pair<unsigned int, unsigned int> > PmergeMe::MergeCompPairs(std::vector<std::pair<unsigned int, unsigned int> > left, std::vector<std::pair<unsigned int, unsigned int> > right)
{

    std::vector<std::pair<unsigned int, unsigned int> >::iterator left_it = left.begin();
    std::vector<std::pair<unsigned int, unsigned int> >::iterator right_it = right.begin();
    std::vector<std::pair<unsigned int, unsigned int> > merged;

    while (left_it != left.end() && right_it != right.end())
    {
        if (left_it->first <= right_it->first)
        {
            merged.push_back(*left_it);
            ++left_it;
        }
        else
        {
            merged.push_back(*right_it);
            ++right_it;
        }
    }
    while (left_it != left.end())
    {
        merged.push_back(*left_it);
        ++left_it;
    }
    while (right_it != right.end())
    {
        merged.push_back(*right_it);
        ++right_it;
    }
    return merged;
}

std::vector<std::pair<unsigned int, unsigned int> >
PmergeMe::startRecMerging(std::vector<std::pair<unsigned int, unsigned int> > vec)
{

    if (vec.size() <= 1)
    {
        return (vec);
    }
    size_t mid = vec.size() / 2;
    std::vector<std::pair<unsigned int, unsigned int> > left(vec.begin(), vec.begin() + mid);
    std::vector<std::pair<unsigned int, unsigned int> > right(vec.begin() + mid, vec.end());

    left = startRecMerging(left);
    right = startRecMerging(right);
    return MergeCompPairs(left, right);
}

unsigned int binarySearch(std::vector<unsigned int> &vector, unsigned int target)
{
    if (vector.empty())
        return (0);
    unsigned int left = 0;
    unsigned int right = vector.size() - 1;
    while (left <= right)
    {
        unsigned int mid = (left + right) / 2;
        if (vector[mid] == target)
            return mid;
        else if (target > vector[mid])
            left = mid + 1;
        else
            right = mid - 1;
    }

    return left;
}

std::vector<unsigned int> generateJacobNumbers(unsigned int size)
{
    std::vector<unsigned int> result;
    if (size <= 1)
    {
        return result;
    }
    result.push_back(1);
    unsigned int j_fst = 1;
    unsigned int j_scnd = 1;
    while (j_fst < size)
    {
        unsigned int j_next = j_fst + 2 * j_scnd;
        for (unsigned int i = j_fst + 2;i <= j_next  && i < size; i++)
        {
            result.push_back(i);
        }
        j_scnd = j_fst;
        j_fst = j_next;
    }
    return result;
}

std::vector<unsigned int> startJhonInsert(std::vector<unsigned int> &MainChain, std::vector<unsigned int> &Pend, std::vector<unsigned int> &JachobtalNUmbs)
{
    std::vector<unsigned int> sorted;
    std::vector<bool> has_missed(Pend.size(), false);
    unsigned int pos = 0;
    unsigned int idex = 0;

    if (MainChain.empty())
        return sorted;
    for (unsigned int i = 0; i < MainChain.size(); i++)
        sorted.push_back(MainChain[i]);
    if (Pend.empty())
        return sorted;
    sorted.insert(sorted.begin(),Pend[0]);
    has_missed[0] = true;

    for (unsigned int i = 0; i < JachobtalNUmbs.size() && i < Pend.size(); i++)
    {
        idex = JachobtalNUmbs[i];
        if (idex < Pend.size() && !has_missed[idex])
        {
            pos = binarySearch(sorted, Pend[idex]);
            sorted.insert(sorted.begin() + pos, Pend[idex]);
            has_missed[idex] = true;
        }
    }
    for (unsigned int i = 0; i <Pend.size(); i++)
    {
        if (!has_missed[i])
        {
            pos = binarySearch(sorted, Pend[i]);
            sorted.insert(sorted.begin() + pos, Pend[i]);
        }
    }
    
    return sorted;
}

void PmergeMe::startFordJhon(std::vector<unsigned int> orig)
{
    (void)orig;
    std::vector<unsigned int> mainChain;
    std::vector<unsigned int> sorted;
    std::vector<unsigned int> Pend;
    
    std::vector<std::pair<unsigned int, unsigned int> >::iterator it;
    for (it = _vec.begin(); it != _vec.end(); ++it)
    {
        if (it->first < it->second)
        {
            std::swap(it->first, it->second);
        }
    }
    _vec = startRecMerging(_vec);
    for (it = _vec.begin(); it != _vec.end(); ++it)
    {
        mainChain.push_back(it->first);
        Pend.push_back(it->second);
    }
    std::vector<unsigned int> JachobtalNUmbs = generateJacobNumbers(Pend.size());
    sorted = startJhonInsert(mainChain, Pend, JachobtalNUmbs);
    if (_has_odd)
    {
        unsigned int pos = binarySearch(sorted, _the_od_elem);
        sorted.insert(sorted.begin() + pos, _the_od_elem);
    }
    for (unsigned int i = 0; i < sorted.size(); i++)
    {
        std::cout << sorted[i] << std::endl;
    }
}

PmergeMe::~PmergeMe() {}
