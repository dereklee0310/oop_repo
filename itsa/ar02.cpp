/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-14 23:33:24
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-14 23:33:41
 * @FilePath: \itsa\ar02.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    string buf, token;
    vector<string> tmp;

    getline(cin, buf);

    stringstream buf_stream(buf);
    while(getline(buf_stream, token, ' ')) {
        tmp.push_back(token);
    }
    

    cout << tmp.at(tmp.size() - 1);
    for(int i = tmp.size() - 2; i >= 0; i--)
        cout << " " << tmp.at(i);
    cout << endl;

    return 0;
}