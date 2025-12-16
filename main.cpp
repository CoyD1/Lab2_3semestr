#include "functions.h"
#include <iostream>

int main()
{
    auto ip_pool = parse(IP_FILTER_PATH);

    mainSort(ip_pool);
    printAllIPs(ip_pool);
    printIPsStartingWith1(ip_pool);
    printIPsStartingWith46_70(ip_pool);
    printIPsContaining46(ip_pool);

    return 0;
}