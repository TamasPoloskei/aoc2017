#include <iostream>
#include <vector>
#include <algorithm>

const unsigned long listLen = 256;
int main() {
    std::vector<long> list(listLen);
    for (int i = 0; i < listLen; ++i) {
        list[i] = i;
    }
    std::vector<unsigned long> lengths = {227,169,3,166,246,201,0,47,1,255,2,254,96,3,97,144};
//    std::vector<unsigned long> lengths = {3, 4, 1, 5};
    unsigned long position = 0;
    unsigned long skip = 0;

    for (unsigned long length: lengths) {
        if(length <= listLen){
            std::vector<long> twisted;
            for (int i = 0; i < length; ++i) {
                twisted.push_back(list[(position+i)%listLen]);
            }
            std::reverse(twisted.begin(), twisted.end());
            for (int i = 0; i < length; ++i) {
                list[(position+i)%listLen] = twisted[i];
            }
            position += length + skip;
            position %= listLen;
            skip++;
        }
    }
    for (long listElem : list) {
        std::cout << listElem << ' ';
    }
    std::cout << std::endl;
    return 0;
}