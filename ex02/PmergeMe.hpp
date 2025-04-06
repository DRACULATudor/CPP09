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
    std::vector<unsigned int, unsigned int> _vec;
public:

    PmergeMe();
    PmergeMe(const PmergeMe &copy);
    PmergeMe &operator=(const PmergeMe &assign);
    void loadVector(char **to_conv);
    ~PmergeMe();
};

