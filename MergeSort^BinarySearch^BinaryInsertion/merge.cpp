#include <cstdlib>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>


std::vector<int> mergeLefRght(std::vector<int> leftarr, std::vector<int> rightarr)
{
    std::vector<int> sorted;
    int left = 0;
    int right = 0;

    while (left < leftarr.size() && right < rightarr.size())
    {
        if (leftarr[left] <= rightarr[right])
        {
            sorted.push_back(leftarr[left]);
            left++;
        }
        else
        {
            sorted.push_back(rightarr[right]);
            right++;
        }
    }
    while(left < leftarr.size())
    {
        sorted.push_back(leftarr[left]);
        left++;
    }
    while (right < rightarr.size())
    {
        sorted.push_back(rightarr[right]);
        right++;
    }
    return sorted;
}

std::vector<int> merge_sort(std::vector<int>_vec)
{
    if (_vec.size() <= 1)
        return _vec;
    size_t middle = _vec.size() / 2;
    std::vector<int>left(_vec.begin(), _vec.begin() + middle);
    std::vector<int>right(_vec.begin() + middle, _vec.end());
    left = merge_sort(left);
    right = merge_sort(right);
    return mergeLefRght(left, right);
}

int main()
{
    std::vector<int> _vec = {6, 4, 15, 7, 2};
    std::vector<int> rez;
    rez = merge_sort(_vec);
    for (size_t i = 0; i < rez.size(); i++)
        std::cout << rez[i] << std::endl;
    return 0;
}
