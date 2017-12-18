#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

unsigned input = 343;
//unsigned input = 3;

int main() {
    vector<unsigned> spinLock({0});
    unsigned pos = 0;
    for (int iii = 1; iii <= 2017; ++iii) {
        pos += input;
        pos %= iii;
        spinLock.insert(spinLock.begin()+pos+1,iii);
        pos++;
    }
    long ind = (distance(spinLock.begin(),find(spinLock.begin(),spinLock.end(),2017))+1)%2018;

    cout << spinLock[ind] << endl;

    return 0;
}