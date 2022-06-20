/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 13:27:47
 * @FilePath: \itsa\ar04.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    int num1, num2;
    while(cin >> num1 >> num2) {
        cout << num1 << "+" << num2 << "=" << num1 + num2 << endl;
        cout << num1 << "*" << num2 << "=" << num1 * num2 << endl;
        cout << num1 << "-" << num2 << "=" << num1 - num2 << endl;
        int tmp = num1 % num2;
        if(num1 % num2 >= 0) {
            cout << num1 << "/" << num2 << "=" << num1 / num2 << "..." << tmp << endl;
            continue;
        } else {
            if(num1 / num2 >= 0)
                cout << num1 << "/" << num2 << "=" << (num1 / num2) + 1 << "..." << tmp + abs(num2) << endl;
            else
                cout << num1 << "/" << num2 << "=" << (num1 / num2) - 1 << "..." << tmp + abs(num2) << endl;
        }
    }
    return 0;
}