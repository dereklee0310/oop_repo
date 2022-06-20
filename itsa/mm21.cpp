/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 23:39:28
 * @FilePath: \itsa\ar04.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://githuy.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <bitset>

using namespace std;

unsigned long long  fib(unsigned long long max);

int main() {
    int num;
    
    while(cin >> num)
        cout << fib(num) << endl;

    return 0;
}

unsigned long long fib(unsigned long long max)
{
    if(max == 0 || max == 1)
        return max;
    else
        return max * fib(max - 1);
}