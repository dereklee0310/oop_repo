/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 23:33:48
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
    // char num_arr[128];
    
    // while(cin >> num) {
    //     itoa(num, num_arr, 16);
    //     for(auto &i : num_arr)
    //         i = toupper(i);
    //     cout << num_arr << endl;
    // }

    while(cin >> num) {
        cout << hex << uppercase << num << endl;
    }

    return 0;
}