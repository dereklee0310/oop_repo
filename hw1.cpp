#include <iostream>

void getData();

class node {
    public:
        
};

using namespace std;
int main() {
    int nodeNum, dstNum, linkNum;
    int *dstList;


    cin >> nodeNum >> dstNum >> linkNum;

    dstList = new int(dstNum);
    for(int i = 0; i < dstNum; i++)
        cin >> dstList[i];

    cout << "Hello, world!" << endl;
    cout << nodeNum << endl;
    cout << dstNum << endl;
    cout << linkNum << endl;

    for(int i = 0; i < dstNum; i++)
        cout << dstList[i];

    delete dstList;

    return 0;
}

void getData()
{

}