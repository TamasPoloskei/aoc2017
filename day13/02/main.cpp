#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    istringstream iss;
    ifstream inFile("input.txt");
    string line;
    vector<unsigned> depth;
    vector<unsigned> pos;
    unsigned num;
    while(getline(inFile, line)){
        iss = istringstream(line);
        iss >> num;
        pos.push_back(num);
        iss >> num;
        depth.push_back(num);
    }
    unsigned delay = 0;
    bool good = false;
    while(!good){
        good = true;
        for (int i = 0; i < depth.size() && good; ++i) {
            if(0 == (delay+pos[i])%((depth[i]-1)*2))
                good = false;
        }
        delay++;
    }
    cout << delay-1;
    return 0;
}