/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 23:46:48
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
    double time, pay;

    cout << setprecision(1);
    cout << fixed;
    
    while(cin >> time >> pay) {
        if(time <= 60)
            cout << round(time * pay * 10) / 10 << endl;
        else if(time > 60 && time <= 120) {
            cout << round((60 * pay + (time - 60) * pay * 1.33) * 10) / 10 << endl;
        } else {
            cout << round((60 * pay + 60 * pay * 1.33 + (time - 120) * pay * 1.66) * 10) / 10 << endl;
        }
    }

    return 0;
}