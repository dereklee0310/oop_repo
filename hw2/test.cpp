#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class t{
    int a;
    int b;
    int c;
    public:
        int geta() {return a;};
        int getb() {return b;};
        int getc() {return c;};
        void seta(int i) {a = i;};
        void setb(int i) {b = i;};
        void setc(int i) {c = i;};
        friend bool comp(t t1, t t2);
};

bool comp(t t1, t t2) {return t1.geta() > t2.getb();};

int main () {
    vector<t> test;
    test.resize(3);
    test.at(0).seta(5);
    test.at(1).seta(7);
    test.at(2).seta(8);

    sort(test.begin(), test.end(), comp);

    for(auto itr : test)
    cout << itr.geta() << endl;

    return 0;
}