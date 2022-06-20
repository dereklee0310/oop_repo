/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 23:18:46
 * @FilePath: \itsa\ar04.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://githuy.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <bitset>

using namespace std;

int main() {
    int minute;
    double cost;

    cout << setprecision(1);
    cout << fixed;
    
    while(cin >> minute) {
        if(minute <= 800) {
            cost = 0.9 * minute;
        } else if(minute > 800 && minute < 1500) {
            cost = 0.9 * minute * 0.9;
        } else {
            cost = 0.9 * minute * 0.79;
        }
        cout << round(cost * 10) / 10 << endl;
    }

    return 0;
}