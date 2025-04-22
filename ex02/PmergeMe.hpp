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

class PmergeMe
{
private:
    std::vector<std::pair<unsigned int, unsigned int> > _vec;
    std::deque<std::pair<unsigned int, unsigned int> > _deque;
    std::vector<long long> _orig;
    bool _has_odd;
    unsigned int _the_od_elem;
public:
    PmergeMe();
    PmergeMe(const PmergeMe &copy);
    PmergeMe &operator=(const PmergeMe &assign);
    void loadVector(char **to_conv);
    std::vector<std::pair<unsigned int, unsigned int> > startRecMerging(std::vector<std::pair<unsigned int, unsigned int> > vec);
    std::vector<std::pair<unsigned int, unsigned int> > MergeCompPairs(std::vector<std::pair<unsigned int, unsigned int> > left, std::vector<std::pair<unsigned int, unsigned int> > right);
    void startFordJhon();
    ~PmergeMe();
};
