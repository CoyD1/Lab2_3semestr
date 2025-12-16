#include "functions.h"
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <algorithm>

// Разделяет строку по заданному разделителю и возвращает вектор подстрок.
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(str.substr(start));
    return r;
}

// Читает файл по указанному пути, парсит строки в формате "IP<tab>...",
// извлекает IPv4-адреса и возвращает вектор кортежей (a, b, c, d).
std::vector<std::tuple<int, int, int, int>> parse(const std::string &file_name)
{
    std::ifstream file(file_name);
    std::vector<std::tuple<int, int, int, int>> ip_pool;
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> v = split(line, '\t');
        std::vector<std::string> ip_parts = split(v[0], '.');
        int a = std::stoi(ip_parts[0]);
        int b = std::stoi(ip_parts[1]);
        int c = std::stoi(ip_parts[2]);
        int d = std::stoi(ip_parts[3]);
        ip_pool.emplace_back(a, b, c, d);
    }
    file.close();
    return ip_pool;
}

// Сортирует вектор IP-адресов в порядке убывания (лексикографически по кортежу).
void mainSort(std::vector<std::tuple<int, int, int, int>> &start_vector)
{
    std::sort(start_vector.begin(), start_vector.end(), [](const auto &a, const auto &b)
              { return a > b; });
}

// Выводит все IP-адреса из переданного вектора в формате "a.b.c.d", каждый с новой строки.
void printAllIPs(const std::vector<std::tuple<int, int, int, int>> &ipList)
{
    for (const auto &ip : ipList)
        std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "."
                  << std::get<2>(ip) << "." << std::get<3>(ip) << '\n';
    std::cout << '\n';
}

// Выводит только те IP-адреса, у которых первый октет равен 1.
void printIPsStartingWith1(const std::vector<std::tuple<int, int, int, int>> &ipList)
{
    for (const auto &ip : ipList)
        if (std::get<0>(ip) == 1)
            std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "."
                      << std::get<2>(ip) << "." << std::get<3>(ip) << '\n';
    std::cout << '\n';
}

// Выводит только те IP-адреса, у которых первый октет равен 46, а второй — 70.
void printIPsStartingWith46_70(const std::vector<std::tuple<int, int, int, int>> &ipList)
{
    for (const auto &ip : ipList)
        if (std::get<0>(ip) == 46 && std::get<1>(ip) == 70)
            std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "."
                      << std::get<2>(ip) << "." << std::get<3>(ip) << '\n';
    std::cout << '\n';
}

// Выводит IP-адреса, в которых хотя бы один из четырёх октетов равен 46.
void printIPsContaining46(const std::vector<std::tuple<int, int, int, int>> &ipList)
{
    for (const auto &ip : ipList)
        if (std::get<0>(ip) == 46 || std::get<1>(ip) == 46 ||
            std::get<2>(ip) == 46 || std::get<3>(ip) == 46)
            std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "."
                      << std::get<2>(ip) << "." << std::get<3>(ip) << '\n';
    std::cout << '\n';
}