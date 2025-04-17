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
        std::cout << left <<  "\n"<< right / 2 << ":\n";
        if (vector[mid] == target)
        {
            return mid;
        }
        else if (target > vector[mid])
            left = mid + 1;
        else
        {
            if (right == 0)
            {
                break;
            }
            
            right = mid - 1;
        }
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
        j_scnd = j_fst;
        j_fst = j_next;
        if (j_next < size)
        {
            result.push_back(j_next);
        }
    }
    return result;
}

std::vector<unsigned int> startJhonInsert(std::vector<unsigned int> MainChain, std::vector<unsigned int> &Pend, std::vector<unsigned int> &JachobtalNUmbs)
{
    unsigned int pos = 0;
    unsigned int j = 0;

    if (MainChain.empty())
        return MainChain;
    if (Pend.empty())
        return MainChain;
    for (unsigned int i = 0; i < Pend.size(); i++)
    {
        if (Pend[i])
        {
            std::cout << "Pend elems are: " << Pend[i] << "\n";
        }
    }
    std::cout << std::endl;
    for (unsigned int i = 0; i < MainChain.size(); i++)
    {
        if (MainChain[i])
        {
            std::cout << "Main elems are: " << MainChain[i] << "\n";
        }
    }
    std::cout << std::endl;
    std::cout << "Below is code output\n";
    
    
    for (unsigned int i = 0; i < JachobtalNUmbs.size(); i++)
    {
        j = JachobtalNUmbs[i];
        if (j < Pend.size())
        {
            pos = binarySearch(MainChain, Pend[j]);
            if (pos <= MainChain.size())
            {
                MainChain.insert(MainChain.begin() + pos, Pend[j]);
            }
        }
    }
    
    return MainChain;
}

void PmergeMe::startFordJhon(std::vector<unsigned int> orig)
{
    (void)orig;
    std::vector<unsigned int> mainChain;
    std::vector<unsigned int> sorte;
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
    mainChain = startJhonInsert(mainChain, Pend, JachobtalNUmbs);
    if (_has_odd)
    {
        unsigned int pos = binarySearch(mainChain, _the_od_elem);
        mainChain.insert(mainChain.begin() + pos, _the_od_elem);
    }
    for (unsigned int i = 0; i < mainChain.size(); i++)
    {
        std::cout << mainChain[i] << std::endl;
    }
}

PmergeMe::~PmergeMe() {}
