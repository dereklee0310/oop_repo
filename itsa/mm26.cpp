/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 23:52:55
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
    int total;
    
    cin >> num;

    for(int i = 1; i <= num; i++) {
        cout << i << '*' << i << '=' << i * i << endl;
    }

    return 0;
}