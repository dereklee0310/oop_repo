/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 22:13:08
 * @FilePath: \itsa\ar04.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int dif_pos;
    double my_speed = 1, his_speed = 30 * 2.54 / 100;
    double diff_speed;

    while(cin >> dif_pos) {
        diff_speed = my_speed - his_speed;
        cout << ceil(dif_pos / diff_speed) << endl; 
    }

    return 0;
}