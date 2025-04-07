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
    std::vector<unsigned int> _orig;
public:
    PmergeMe();
    PmergeMe(const PmergeMe &copy);
    PmergeMe &operator=(const PmergeMe &assign);
    void loadVector(char **to_conv);
    void startFordJhon();
    ~PmergeMe();
};

