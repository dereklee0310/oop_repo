/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-14 23:35:30
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-14 23:37:45
 * @FilePath: \itsa\ar03.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AEream
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int total;
    int tmp;

    while(cin >> tmp) {
        total += tmp * tmp * tmp;
    }
    cout << total << endl;
}