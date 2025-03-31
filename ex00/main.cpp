#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::perror("Error: could not open file");
        return (1);
    }
    else
    {
        (void)argv;
        BitcoinExchange btc;
        btc.Load_DB_for_BitcoinExchange();
        btc.setFileName(argv[1]);
    }
    return (0);
}