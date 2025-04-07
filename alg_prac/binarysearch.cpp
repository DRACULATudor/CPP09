#include <cstdlib>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>


void binarySearch(std::vector<int> vector, int target)
{
    int left = 0;
    int right = vector.size() - 1;
    while (left <= right)
    {
        int mid = (left + right)/2;
        if (vector[mid] == target)
        {
            std::cout << vector[mid] << "\n";
            break;
        }
        else if (target > vector[mid])
            left = mid + 1;
        else
            right = mid - 1;
    }
}

int main(void)
{
    std::vector<int> _vec = {1, 2, 3, 4, 5, 6};
    int target = 4;
    binarySearch(_vec, target);
    return 0;
}
