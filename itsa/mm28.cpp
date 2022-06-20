/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-21 00:02:27
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
    int num;
    bool is_first;

    while(cin >> num) {
        is_first = true;
        for(int i = 1; i <= num; i++) {
            if(i % 35 == 0) {
                if(is_first)
                    is_first = false;
                else
                    cout << ' ';
                cout << i;
            }
        }
        cout << endl;
    }

    return 0;
}