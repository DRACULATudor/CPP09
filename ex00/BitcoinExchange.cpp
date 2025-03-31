#include "BitcoinExchange.hpp"
#include <string>

BitcoinExchange::BitcoinExchange() {};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
    this->_file = copy._file;
    this->_map = copy._map;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &assign)
{
    if (this != &assign)
    {
        this->_file = assign._file;
        this->_map = assign._map;
    }
    return *this;
}

bool isgoodDate(int year, int month, int day)
{
    if (day < 1 || day > 31)
        return false;
    if (month < 1 || month > 12)
        return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2)
    {
        bool leap_year = false;
        if (year % 400 == 0)
            leap_year = true;
        else if (year % 4 == 0 && year % 100 != 0)
            leap_year = true;
        if (leap_year && day > 29)
            return false;
        else if (!leap_year && day > 28)
            return false;
    }
    return true;
}

std::string SpaceRemover(std::string to_parse)
{
    std::string copy;
    for (size_t i = 0; i < to_parse.length(); i++)
    {
        if (!isspace(to_parse[i]))
            copy += to_parse[i];
    }
    return copy;
}

std::string DateParser(std::string &date_to_parse)
{
    date_to_parse = SpaceRemover(date_to_parse);
    if (date_to_parse.length() != 10)
    {
        std::cout << "Error: invalid date length" << std::endl;
        date_to_parse = "";
    }
    if (date_to_parse[4] != '-' || date_to_parse[7] != '-')
    {
        std::cout << "Error: Invalid date format !" << std::endl;
        date_to_parse = "";
    }
    for (size_t i = 0; i < date_to_parse.length(); i++)
    {
        if (i != 4 && i != 7 && !isdigit(date_to_parse[i]))
        {
            std::cout << "Error: Invalid characters in the date!" << std::endl;
            std::cout << "Expected format: YYYY-MM-DD" << std::endl;
            date_to_parse = "";
        }
    }
    return date_to_parse;
}

std::string process_date(std::string &to_parse)
{
    int year = 0;
    int month = 0;
    int day = 0;
    std::string parsed;

    parsed = DateParser(to_parse);
    if (parsed.length() == 0)
    {
        return parsed;
    }
    year = atoi(to_parse.substr(0, 4).c_str());
    month = atoi(to_parse.substr(5, 2).c_str());
    day = atoi(to_parse.substr(8, 2).c_str());
    if (!isgoodDate(year, month, day))
        std::cout << "Invalid year/month/date !" << std::endl;
    return parsed;
}

bool validate_value(double val)
{
    if (val < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return false;
    }
    if (val > 1000)
    {
        std::cout << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

std::multimap<std::string, double> BitcoinExchange::prepare_exchange(const std::string &file)
{
    std::string line;
    std::string date;
    std::string val;
    std::stringstream doubl;
    int line_num = 0;
    std::multimap<std::string, double> map;
    double value = 0;
    _file = file;
    std::ifstream fil(_file.c_str());
    getline(fil, line);
    while (getline(fil, line))
    {
        line_num++;
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(3) << line_num << "_";
        std::string line_prefix = oss.str();
        std::stringstream strstr(line);
        if (line[0] == ' ')
        {
            size_t i = 0;
            while (i < line.size() && isspace(line[i]))
            {
                i++;
            }
            line = line.substr(i);
            strstr.str(line);
            strstr.clear();
        }
        if (line.find(',') != std::string::npos)
        {
            getline(strstr, date, ',');
            date = process_date(date);
            if (date.empty())
            {
                map.insert(std::make_pair(line_prefix + line, -999));
            }
            else
            {
                getline(strstr, val);
                val = SpaceRemover(val);
                doubl.clear();
                doubl.str("");
                doubl << val;
                doubl >> value;
                if (doubl.fail())
                {
                    std::cout << "Error: Invalid value" << std::endl;
                    continue;
                }
                map.insert(std::make_pair(date, value));
            }
            
        }
        else if (line.find('|') != std::string::npos)
        {
            getline(strstr, date, '|');
            date = process_date(date);
            if (date.empty())
            {
                map.insert(std::make_pair(line_prefix + line, -999));
            }
            else
            {
                getline(strstr, val);
                val = SpaceRemover(val);
                doubl.clear();
                doubl.str("");
                doubl << val;
                doubl >> value;
                if (doubl.fail())
                {
                    std::cout << "Error: Invalid value" << std::endl;
                    continue;
                }
                map.insert(std::make_pair(date, value));
            }
        }
        else if (line.find(' ') != std::string::npos)
        {
            getline(strstr, date, ' ');
            date = process_date(date);
            if (date.empty())
                return std::multimap<std::string, double>();
            getline(strstr, val);
            val = SpaceRemover(val);
            doubl.clear();
            doubl.str("");
            doubl << val;
            doubl >> value;
            if (doubl.fail())
            {
                std::cout << "Error: Invalid value" << std::endl;
                continue;
            }
            map.insert(std::make_pair(date, value));
        }
        else
        {
            map.insert(std::make_pair(line_prefix + line, -999));
            continue;
        }
    }
    return map;
}

void BitcoinExchange::setFileName(const std::string &file)
{
    std::multimap<std::string, double> map;
    std::multimap<std::string, double>::iterator it_for_smap;

    map = prepare_exchange(file);
    for (it_for_smap = map.begin(); it_for_smap != map.end(); ++it_for_smap)
    {
        std::string full_key = it_for_smap->first;
        size_t pos = full_key.find('_');
        std::string key;
        if (pos != std::string::npos)
        {
            key = full_key.substr(pos + 1);
        }
        else
        {
            key = full_key;
        }
        double val = it_for_smap->second;
        std::multimap<std::string, double>::iterator it = _map.lower_bound(key);
        if (val == -999)
        {
            std::cout << "Error: bad input => " << key << std::endl;
            continue;
        }
        if (it != _map.end() && it->first == key)
        {
            double exchange_rate_result = val * it->second;
            if (validate_value(val))
            {
                if (val == static_cast<int>(val))
                {
                    std::cout << key << " => " << static_cast<int>(val) << " = " << exchange_rate_result << std::endl;
                }
                else
                {
                    std::cout << key << " => " << val << " = " << exchange_rate_result << std::endl;
                }
            }
        }
        else if (it != _map.begin())
        {
            --it;
            double exchange_rate_result = val * it->second;

            if (validate_value(val))
            {
                if (val == static_cast<int>(val))
                {
                    std::cout << key << " => " << static_cast<int>(val) << " = " << exchange_rate_result << std::endl;
                }
                else
                {
                    std::cout << key << " => " << val << " = " << exchange_rate_result << std::endl;
                }
            }
        }
    }
}

void BitcoinExchange::Load_DB_for_BitcoinExchange()
{
    std::ifstream file("data.csv");
    std::stringstream doubl;
    std::string line;
    std::string date;
    std::string val;
    double value = 0;

    getline(file, line);
    while (getline(file, line))
    {
        std::stringstream strstr(line);
        getline(strstr, date, ',');
        getline(strstr, val);
        doubl.clear();
        doubl.str("");
        doubl << val;
        doubl >> value;
        _map.insert(std::make_pair(date, value));
    }
}

BitcoinExchange::~BitcoinExchange() {};