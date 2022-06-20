/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 07:48:19
 * @FilePath: \itsa\ar04.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int order_num;
    int start, end;
    int cnt = 0;
    vector<pair<int, int> > order_arr;
    vector<bool> check_arr;

    cin >> order_num;
    check_arr.resize(order_num, false);

    for(int i = 0; i < order_num; i++) {
        cin >> start >> end;
        order_arr.push_back(make_pair(start, end));
    }
    for(int i = 0; i < order_num; i++) {
        int pre_idx = -1;
        for(int j = 0; j < order_num; j++) {
            if(check_arr.at(j))
                continue;
            
            if(pre_idx == -1) {
                cnt++;
                check_arr.at(j) = true;
                pre_idx = j;
            } else if(order_arr.at(j).first >= order_arr.at(pre_idx).second) {
                check_arr.at(j) = true;
                pre_idx = j;
            }
        }
    }

    cout << cnt << endl;



    return 0;
}