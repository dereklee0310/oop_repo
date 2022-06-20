/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-21 00:08:34
 * @FilePath: \itsa\ar04.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://githuy.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <bitset>

bool is_prime(int num);

using namespace std;

int main() {
    int num;
    bool is_first;

    while(cin >> num) {
        if(is_prime(num))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}

bool is_prime(int num)
{   
    for(int i = 2; i < sqrt(num); i++) {
        if(num % i == 0)
            return false;
    }
    return true;
}