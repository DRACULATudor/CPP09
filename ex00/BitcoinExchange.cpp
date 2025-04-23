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

//Leap year = year divisible by 4 and not 100 or divisibale by 400

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
        return parsed;
    year = atoi(to_parse.substr(0, 4).c_str());
    month = atoi(to_parse.substr(5, 2).c_str());
    day = atoi(to_parse.substr(8, 2).c_str());
    if (!isgoodDate(year, month, day))
        parsed = "";
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

bool isallNum(std::string val)
{
    int dot_count = 0;
    for (size_t i = 0; i < val.length(); ++i)
    {
        if (val[i] == '.')
        {
            dot_count++;
            if (i + 1 >= val.length())
                return false;
        }
        else if (!isdigit(val[i]) && val[i] != '-')
            return false;
    }
    if (dot_count > 1)
        return false;
    
    return true;
}


std::string SkipWspaces(std::string line)
{
    std::stringstream strstr(line);
    size_t i = 0;
    while (i < line.size() && isspace(line[i]))
        i++;
    line = line.substr(i);
    strstr.str(line);
    strstr.clear();
    return line;
}

void add_values_to_map(std::multimap<std::string, double> &map, std::string val, std::string date, std::string line, bool elsFlg)
{
    static int line_num = 0;
    std::stringstream doubl;
    std::ostringstream oss; //allows to format and builad a string in memory;
    oss << std::setfill('0') << std::setw(3) << line_num << "_";
    std::string line_prefix = oss.str();
    std::stringstream strstr(line);
    double value = 0;

    line_num++;
    date = process_date(date);
    if (date.empty())
    {
        map.insert(std::make_pair(line_prefix + line, -999));
    }
    else if(!elsFlg)
    {
        val = SpaceRemover(val);
        doubl.clear();
        doubl.str("");
        doubl << val;
        doubl >> value;
        if (doubl.fail())
        {
            if (value == 0)
            {
                map.insert(std::make_pair(line_prefix + line, -999));
            }
            else
            {

                map.insert(std::make_pair(line_prefix + val, -999));
            }
        }
        else
        {
            if (!isallNum(val))
            {
                map.insert(std::make_pair(line_prefix + val, -999));
            }
            else
                map.insert(std::make_pair(line_prefix + date, value));
        }
    }
    else
    {
        std::cout << date << "\n\n\n\n";
        map.insert(std::make_pair(line_prefix + date, -999));
    }
}

std::multimap<std::string, double> BitcoinExchange::prepare_exchange(const std::string &file)
{
    std::string line;
    std::string date;
    std::string val;
    std::multimap<std::string, double> map;
    bool elsFlg = false;
    _file = file;
    std::ifstream fil(_file.c_str());
    getline(fil, line);
    while (getline(fil, line))
    {
        std::stringstream strstr(line);
        if (line[0] == ' ')
            line = SkipWspaces(line);
        if (line.find(',') != std::string::npos)
        {
            getline(strstr, date, ',');
            getline(strstr, val);
            add_values_to_map(map,  val, date, line, elsFlg);
        }
        else if (line.find('|') != std::string::npos)
        {
            getline(strstr, date, '|');
            getline(strstr, val);
            add_values_to_map(map,  val, date, line, elsFlg);
        }
        else if (line.find(' ') != std::string::npos)
        {
            getline(strstr, date, ' ');
            getline(strstr, val);
            add_values_to_map(map,  val, date, line, elsFlg);
        }
        else
        {
            elsFlg = true;
            add_values_to_map(map,  val, date, line, elsFlg);
            elsFlg = false;
        }
    }
    return map;
}

void ExchangeOutput(double val, std::string key, double exchange_rate_result)
{
    if (validate_value(val))
    {
        // std::cout << std::fixed << std::setprecision(2); 
        if (val == static_cast<int>(val))
            std::cout << key << " => " << static_cast<int>(val) << " = " << exchange_rate_result << std::endl;
        else
            std::cout << key << " => " << val << " = " << exchange_rate_result << std::endl;
    }
}

void BitcoinExchange::setFileName(const std::string &file)
{
    double val = 0;
    double exchange_rate_result = 0;
    std::string full_key;
    std::string key;
    std::multimap<std::string, double> map;
    std::multimap<std::string, double>::iterator it_for_smap;
    std::multimap<std::string, double>::iterator it;

    map = prepare_exchange(file);
    for (it_for_smap = map.begin(); it_for_smap != map.end(); ++it_for_smap)
    {
        full_key = it_for_smap->first;
        size_t pos = full_key.find('_');
        if (pos != std::string::npos)
            key = full_key.substr(pos + 1);
        else
            key = full_key;
        val = it_for_smap->second;
        it = _map.lower_bound(key);
        if (val == -999)
        {
            std::cout << "Error: bad input => " << key << std::endl;
            continue;
        }
        if (it != _map.end() && it->first == key)
        {
            exchange_rate_result = val * it->second;
            ExchangeOutput(val,key,exchange_rate_result);
        }
        else if (it != _map.begin())
        {
            --it;
            exchange_rate_result = val * it->second;
            ExchangeOutput(val,key,exchange_rate_result);
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