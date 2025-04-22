#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
    }
    else
    {
        PmergeMe merge;
        merge.loadVectorDeque(argv);
    }
}