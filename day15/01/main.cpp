#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
int main() {
    unsigned long genA = 634;
    unsigned long genB = 301;
    unsigned long mask = 65535;
    unsigned long factA = 16807;
    unsigned long factB = 48271;
    unsigned long rem = 2147483647;
    unsigned pairs = 0;
    for (int i = 0; i < 40000000; ++i) {
        genA *= factA;
        genB *= factB;
        genA %= rem;
        genB %= rem;
        if((genA&mask) == (genB&mask))
            pairs++;
    }
    cout << endl << pairs << endl;

    return 0;
}