/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 22:59:11
 * @FilePath: \itsa\ar04.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int x, y;

    while(cin >> x >> y) {
        if(x * x + y * y <= 100 * 100)
            cout << "inside" << endl;
        else
            cout << "outside" << endl;
    }
    

    return 0;
}