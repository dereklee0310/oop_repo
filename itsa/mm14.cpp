/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 22:46:35
 * @FilePath: \itsa\ar04.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int second;

    cin >> second;

    if(second / 86400 != 0) {
        cout << second / 86400 << " days" << endl;
        second = second % 86400;
    }
    if(second / 3600 != 0) {
        cout << second / 3600 << " hours" << endl;
        second = second % 3600;
    }
    if(second / 60 != 0) {
        cout << second / 60 << " minutes" << endl;
        second = second % 60;
    }
    cout << second << " seconds" << endl;
    

    return 0;
}