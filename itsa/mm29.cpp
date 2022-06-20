/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-21 00:07:30
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
        for(int i = num - 1; i >= 2; i--) {
            if(is_prime(i)) {
                cout << i << endl;
                break;
            }
        }
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