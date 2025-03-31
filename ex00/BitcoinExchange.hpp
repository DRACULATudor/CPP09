#pragma once
#include <cstdlib>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>

class BitcoinExchange
{
private:
    std::string _file;
    std::multimap<std::string, double> _map;
    BitcoinExchange(const BitcoinExchange &copy);
    BitcoinExchange &operator=(const BitcoinExchange &assign);
public:
    BitcoinExchange();
    ~BitcoinExchange();
    void setFileName(const std::string &file);
    void Load_DB_for_BitcoinExchange();
    std::multimap<std::string, double>prepare_exchange(const std::string &file);
};
