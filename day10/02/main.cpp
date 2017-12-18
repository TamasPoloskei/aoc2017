#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

const unsigned long listLen = 256;
int main() {
    std::vector<unsigned> list(listLen);
    for (unsigned i = 0; i < listLen; ++i) {
        list[i] = i;
    }
    std::string lengths("227,169,3,166,246,201,0,47,1,255,2,254,96,3,97,144");
//    std::string lengths = "";
    lengths.push_back(17);
    lengths.push_back(31);
    lengths.push_back(73);
    lengths.push_back(47);
    lengths.push_back(23);
    unsigned position = 0;
    unsigned skip = 0;

    for (unsigned round = 0; round < 64; ++round){
        for (char length: lengths) {
            if (length <= listLen) {
                std::vector<unsigned> twisted;
                for (unsigned i = 0; i < length; ++i) {
                    twisted.push_back(list[(position + i) % listLen]);
                }
                std::reverse(twisted.begin(), twisted.end());
                for (int i = 0; i < length; ++i) {
                    list[(position + i) % listLen] = twisted[i];
                }
                position += length + skip;
                position %= listLen;
                skip++;
            }
        }
    }
    // posproc
    std::vector<unsigned> densehash(16);
    for (int j = 0; j < 16; ++j) {
        densehash[j] = list[16*j];
        for (int i = 1; i < 16; ++i) {
            densehash[j] ^= list[16*j+i];
        }
    }
    for (unsigned listElem : densehash) {
        std::cout << std::setfill('0') << std::setw(2) <<std::hex << listElem;
    }
    std::cout << std::endl;
    return 0;
}