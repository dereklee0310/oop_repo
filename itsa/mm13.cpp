/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 22:38:38
 * @FilePath: \itsa\ar04.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int h1, m1;
    int h2, m2;
    int t_dif;
    int cost;

    cin >> h1 >> m1 >> h2 >> m2;
    t_dif = (60 * (h2 - h1) + m2) - m1;
    if(t_dif <= 120) { // under two hours
        cost = 30 * (t_dif / 30);
    } else if(t_dif > 120 && t_dif <= 240) { // two to four hours
        cost = 30 * 4 + 40 * ((t_dif - 120) / 30);
    } else {
        cost = 30 * 4 + 40 * 4 + 60 * ((t_dif - 120 - 120) / 30);
    }
    cout << cost << endl;

    return 0;
}