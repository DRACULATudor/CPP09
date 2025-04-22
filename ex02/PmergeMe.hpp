#pragma once
#include <cstdlib>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>
#include <ctime>

class PmergeMe
{
private:
    std::vector<std::pair<unsigned int, unsigned int> > _vec;
    std::deque<std::pair<unsigned int, unsigned int> > _pair_deque;
    std::vector<long long> _orig;
    std::vector<long long> _deq;
    bool _has_odd;
    unsigned int _the_od_elem;
    unsigned int _the_od_elem_for_deck;
public:
    PmergeMe();
    PmergeMe(const PmergeMe &copy);
    PmergeMe &operator=(const PmergeMe &assign);
    void loadVectorDeque(char **to_conv);
    void StartVector();
    void StartDeque();
    void print_before();
    bool fillVecAndDeq(char **to_conv);
    std::vector<std::pair<unsigned int, unsigned int> > startRecMerging(std::vector<std::pair<unsigned int, unsigned int> > vec);
    std::deque<std::pair<unsigned int, unsigned int> > startRecMergingForDeque(std::deque<std::pair<unsigned int, unsigned int> > deque);
    std::vector<std::pair<unsigned int, unsigned int> > MergeCompPairs(std::vector<std::pair<unsigned int, unsigned int> > left, std::vector<std::pair<unsigned int, unsigned int> > right);
    std::deque<std::pair<unsigned int, unsigned int> > MergeCompPairsForDeque(std::deque<std::pair<unsigned int, unsigned int> > left, std::deque<std::pair<unsigned int, unsigned int> > right);
    void startFordJhon();
    ~PmergeMe();
};
