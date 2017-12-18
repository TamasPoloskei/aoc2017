#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

unsigned input = 343;
//unsigned input = 3;

int main() {
    unsigned long pos = 0;
    unsigned long atPos0, atPos1;
    atPos0 = atPos1 = 0;
    for (unsigned long iii = 1; iii <= 50000000; ++iii) {
        if(0 == iii%100000)
            cout << ".";
        if(0 == iii%10000000)
            cout << endl;
        pos += input;
        pos %= iii;
        pos++;
        if(pos == 1)
            atPos1 = iii;
        else if(pos == 0){
            atPos1 = atPos0;
            atPos0 = iii;
        } else
            ;
    }
    cout << endl << atPos0 << " " << atPos1 << endl;

    return 0;
}