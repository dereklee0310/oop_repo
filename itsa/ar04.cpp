/*
 * @Author: dereklee0310 dereklee0310.gmail.com
 * @Date: 2022-06-20 06:26:09
 * @LastEditors: dereklee0310 dereklee0310.gmail.com
 * @LastEditTime: 2022-06-20 07:12:24
 * @FilePath: \itsa\ar04.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int case_num;
    int n, m;

    cin >> case_num;

    for(int i = 0; i < case_num; i++) {
        cin >> n >> m;
        vector< vector<int> > matrix;
        vector< vector<char> > output;
        matrix.resize(n);
        for(int it = 0; it < n; it++)
            matrix.at(it).resize(m);
        output.resize(n);
        for(int it = 0; it < n; it++)
            output.at(it).resize(m);

        for(int j = 0; j < n; j++) {
            for(int k = 0; k < m; k++) {
                cin >> matrix[j][k];
                if(matrix[j][k] == 0)
                    output[j][k] = '_';
                else 
                    output[j][k] = '0';
            }
        }

        for(int j = 0; j < n; j++) {
            for(int k = 0; k < m; k++) {
                if(j == 0 || j == n - 1 || k == 0 || k == m - 1) {
                    cout << output[j][k] << " ";
                    continue;
                }
                
                if((matrix[j][k] == 1) && (matrix[j - 1][k] & matrix[j + 1][k] & matrix[j][k - 1] & matrix[j][k + 1] == 1)) { // point that is not an edge
                    output[j][k] = '_';
                }
                cout << output[j][k] << " ";
            }
            cout << endl;
        }
        if(i != case_num - 1)
            cout << endl;
    }

    return 0;
}