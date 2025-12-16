#pragma once

#include <string>
#include <vector>
#include <tuple>

std::vector<std::string> split(const std::string &str, char d);
std::vector<std::tuple<int, int, int, int>> parse(const std::string &file_name);
void mainSort(std::vector<std::tuple<int, int, int, int>> &start_vector);

void printAllIPs(const std::vector<std::tuple<int, int, int, int>> &ipList);
void printIPsStartingWith1(const std::vector<std::tuple<int, int, int, int>> &ipList);
void printIPsStartingWith46_70(const std::vector<std::tuple<int, int, int, int>> &ipList);
void printIPsContaining46(const std::vector<std::tuple<int, int, int, int>> &ipList);