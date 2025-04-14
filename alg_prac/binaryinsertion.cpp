#include <cstdlib>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>

size_t binarySearch(std::vector<int> vector, int target)
{
    int left = 0;
    int right = vector.size() - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (vector[mid] == target)
        {
            return mid;
        }
        else if (target > vector[mid])
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left;
}

std::vector<int> binayinsertion(std::vector<int> vector)
{
    size_t pos =0;
    std::vector<int> res;
    for (size_t i = 0; i != vector.size(); i++)
    {
        pos = binarySearch(res, vector[i]);
        res.insert(res.begin() + pos, vector[i]);
    }
    return res;
}

int main()
{
    std::vector<int> _vec = {6, 4, 15, 7, 2};
    std::vector<int> rez;
    rez = binayinsertion(_vec);
    for (size_t i = 0; i < rez.size(); i++)
        std::cout << rez[i] << std::endl;
    return 1;
}
