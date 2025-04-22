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

void PmergeMe::print_before()
{
    for(unsigned int i = 0; i < _orig.size(); i++)
    {
        std::cout << _orig[i] << " ";
    }
    std::cout << std::endl;
}

bool PmergeMe::fillVecAndDeq(char **to_conv)
{
    if (to_conv[0] && !isdigit(to_conv[0][0]))
        to_conv++;
    for (unsigned int i = 0; to_conv[i]; i++)
    {
        for (unsigned int j = 0; to_conv[i][j]; j++)
        {
            if(to_conv[i][j] == '"' || to_conv[i][j] == '\'')
            {
                std::cerr << "Error: Invalid input, it only can be digits !" << std::endl;
                return false;
            }
            else if(atoll(to_conv[i]) < 0)
            {
                std::cerr << "Error: Invalid input, it only can be positive integers !" << std::endl;
                return false;
            }
            else if(!isdigit(to_conv[i][j]))
            {
                std::cerr << "Error: Invalid input, it only can be digits or numbers !" << std::endl;
                return false;
            }
        }
        if (atoll(to_conv[i]) > 2147483647)
        {
            std::cerr << "Error: Input too big !" <<  std::endl;
            return false;
        }
        _orig.push_back(atoll(to_conv[i]));
        _deq.push_back(atoll(to_conv[i]));        
    }
    if (_orig.size() % 2 != 0)
        _has_odd = true;
    return true;
}

void PmergeMe::loadVectorDeque(char **to_conv)
{
    _has_odd = false;

    if(!fillVecAndDeq(to_conv))
        return;
    std::cout << "Before: ";
    print_before();
    for (unsigned int i = 0; i < _orig.size() - 1; i += 2)
        _vec.push_back(std::make_pair(_orig[i], _orig[i + 1]));
    for (unsigned int i = 0; i < _deq.size() - 1; i += 2)
        _pair_deque.push_back(std::make_pair(_deq[i], _deq[i + 1]));
    if (_has_odd)
    {
        _the_od_elem = _orig[_orig.size() - 1];
        _the_od_elem_for_deck = _deq[_deq.size() - 1];
        _orig.pop_back();
        _deq.pop_back();
    }
    startFordJhon();
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


std::deque<std::pair<unsigned int, unsigned int> > PmergeMe::MergeCompPairsForDeque(std::deque<std::pair<unsigned int, unsigned int> > left, std::deque<std::pair<unsigned int, unsigned int> > right)
{

    std::deque<std::pair<unsigned int, unsigned int> >::iterator left_it = left.begin();
    std::deque<std::pair<unsigned int, unsigned int> >::iterator right_it = right.begin();
    std::deque<std::pair<unsigned int, unsigned int> > merged;

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


std::deque<std::pair<unsigned int, unsigned int> >
PmergeMe::startRecMergingForDeque(std::deque<std::pair<unsigned int, unsigned int> > deque)
{

    if (deque.size() <= 1)
    {
        return (deque);
    }
    size_t mid = deque.size() / 2;
    std::deque<std::pair<unsigned int, unsigned int> > left(deque.begin(), deque.begin() + mid);
    std::deque<std::pair<unsigned int, unsigned int> > right(deque.begin() + mid, deque.end());

    left = startRecMergingForDeque(left);
    right = startRecMergingForDeque(right);
    return MergeCompPairsForDeque(left, right);
}

unsigned int binarySearch(std::vector<unsigned int> &vector, unsigned int target)
{
    if (vector.empty())
        return (0);
    int left = 0;
    int right = vector.size() - 1;
    while (left <= right)
    {
        unsigned int mid = (left + right) / 2;
        if (vector[mid] == target)
            return mid;
        else if (target > vector[mid])
            left = mid + 1;
        else
        {
            if (right == 0)
                break;
            right = mid - 1;
        }
    }
    return left;
}

unsigned int binarySearchForDeque(std::deque<unsigned int> &vector, unsigned int target)
{
    if (vector.empty())
        return (0);
    int left = 0;
    int right = vector.size() - 1;
    while (left <= right)
    {
        unsigned int mid = (left + right) / 2;
        if (vector[mid] == target)
            return mid;
        else if (target > vector[mid])
            left = mid + 1;
        else
        {
            if (right == 0)
                break;
            right = mid - 1;
        }
    }
    return left;
}


std::deque<unsigned int> generateJacobNumbersDeq(unsigned int size)
{
    std::deque<unsigned int> result;
    if (size <= 1)
    {
        return result;
    }
    result.push_back(1);
    unsigned int j_fst = 1;
    unsigned int j_scnd = 1;
    while (result.size() < size)
    {
        unsigned int j_next = j_fst + 2 * j_scnd;
        j_scnd = j_fst;
        j_fst = j_next;
        result.push_back(j_next);
        
    }
    while (!result.empty() && result.back() > size) //ensure not to exced pend size
        result.pop_back();
    return result;
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
    while (result.size() < size)
    {
        unsigned int j_next = j_fst + 2 * j_scnd;
        j_scnd = j_fst;
        j_fst = j_next;
        result.push_back(j_next);
        
    }
    while (!result.empty() && result.back() > size) //ensure not to exced pend size
        result.pop_back();
    return result;
}

std::deque<unsigned int> startJhonInsertDeq(std::deque<unsigned int> MainChain, std::deque<unsigned int> &Pend, std::deque<unsigned int> &JachobtalNUmbs)
{
    int pos = 0;
    int j = 0;
    std::deque<bool>used(Pend.size(), false);

    if (MainChain.empty())
        return MainChain;
    if (Pend.empty())
        return MainChain;
    for (unsigned int i = 0; i < JachobtalNUmbs.size(); i++)
    {
        j = JachobtalNUmbs[i] - 1;
        if (j < static_cast<int>(Pend.size()))
        {   
            pos = binarySearchForDeque(MainChain, Pend[j]);
            MainChain.insert(MainChain.begin() + pos, Pend[j]);
            used[j] = true;
        }
    }
    for (unsigned int i = 0; i < Pend.size(); i++)
    {
        if (!used[i])
        {
            pos = binarySearchForDeque(MainChain, Pend[i]);
            MainChain.insert(MainChain.begin() + pos, Pend[i]);
        }
    }
    return MainChain;
}



std::vector<unsigned int> startJhonInsert(std::vector<unsigned int> MainChain, std::vector<unsigned int> &Pend, std::vector<unsigned int> &JachobtalNUmbs)
{
    int pos = 0;
    int j = 0;
    std::vector<bool>used(Pend.size(), false);

    if (MainChain.empty())
        return MainChain;
    if (Pend.empty())
        return MainChain;
    for (unsigned int i = 0; i < JachobtalNUmbs.size(); i++)
    {
        j = JachobtalNUmbs[i] - 1;
        if (j < static_cast<int>(Pend.size()))
        {   
            pos = binarySearch(MainChain, Pend[j]);
            MainChain.insert(MainChain.begin() + pos, Pend[j]);
            used[j] = true;
        }
    }
    for (unsigned int i = 0; i < Pend.size(); i++)
    {
        if (!used[i])
        {
            pos = binarySearch(MainChain, Pend[i]);
            MainChain.insert(MainChain.begin() + pos, Pend[i]);
        }
    }
    return MainChain;
}

void PmergeMe::StartVector()
{
    std::vector<unsigned int> mainChain;
    std::vector<unsigned int> sorte;
    std::vector<unsigned int> Pend;

    std::vector<std::pair<unsigned int, unsigned int> >::iterator it;
    std::clock_t start = std::clock();

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
        if (mainChain.empty())
            mainChain.push_back(_the_od_elem);
        else
        {
            unsigned int pos = binarySearch(mainChain, _the_od_elem);
            if (pos <= mainChain.size())
                mainChain.insert(mainChain.begin() + pos, _the_od_elem);
        }
    }
    std::clock_t end = std::clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    
    // std::cout << "Vector is: ";
    std::cout << "After: ";
    for (unsigned int i = 0; i < mainChain.size(); i++)
    {
        std::cout << mainChain[i]  << " ";
    }
    std::cout << std::endl;
    std::cout << "Time to process a range of " << mainChain.size() << " elements with std::vector : " << time * 10 << " us" << std::endl; 
}

void PmergeMe::StartDeque()
{
    std::deque<unsigned int> mainChain_deq;
    std::deque<unsigned int> sorte_deq;
    std::deque<unsigned int> Pend_deq;
    
    std::deque<std::pair<unsigned int, unsigned int> >::iterator it_deq;
    std::clock_t start = std::clock();
    
    for (it_deq = _pair_deque.begin(); it_deq != _pair_deque.end(); ++it_deq)
    {
        if (it_deq->first < it_deq->second)
        {
            std::swap(it_deq->first, it_deq->second);
        }
    }
    _pair_deque = startRecMergingForDeque(_pair_deque);
    for (it_deq = _pair_deque.begin(); it_deq != _pair_deque.end(); ++it_deq)
    {
        mainChain_deq.push_back(it_deq->first);
        Pend_deq.push_back(it_deq->second);
    }
    std::deque<unsigned int> JachobtalNUmbsDeq = generateJacobNumbersDeq(Pend_deq.size());
    mainChain_deq = startJhonInsertDeq(mainChain_deq, Pend_deq, JachobtalNUmbsDeq);
    if (_has_odd)
    {
        if (mainChain_deq.empty())
            mainChain_deq.push_back(_the_od_elem_for_deck);
        else
        {
            unsigned int pos_deq = binarySearchForDeque(mainChain_deq, _the_od_elem_for_deck);
            if (pos_deq <= mainChain_deq.size())
                mainChain_deq.insert(mainChain_deq.begin() + pos_deq, _the_od_elem_for_deck);
        }
    }
    std::clock_t end = std::clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    // std::cout << "Deque is: ";
    // for (unsigned int i = 0; i < mainChain_deq.size(); i++)
    // {
    //     std::cout << mainChain_deq[i]  << " ";
    // }
    // std::cout << std::endl;
    std::cout << "Time to process a range of " << mainChain_deq.size() << " elements with std::deque : " << time * 10 << " us" << std::endl; 
}

void PmergeMe::startFordJhon()
{
    StartVector();
    StartDeque();
}

PmergeMe::~PmergeMe() {}