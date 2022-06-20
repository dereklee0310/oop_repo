/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 08:16:08
 * @FilePath: \itsa\ar04.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    int up, down, height;
    cout << fixed;
    cout << setprecision(1);
    while(cin >> up >> down >> height) {
        cout << "Trapezoid area:" << (float) (up + down) * height / 2 << endl;
    }
    return 0;
}