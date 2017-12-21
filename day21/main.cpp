#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class pattern{
public:
    vector<vector<vector<char>>> from;
    vector<vector<char>> to;
};

void procFile(ifstream &inFile, vector<pattern> &patt2, vector<pattern> &patt3);

int main() {
    ifstream inFile("input.txt");
    vector<pattern> patt3;
    vector<pattern> patt2;
    procFile(inFile, patt2, patt3);
    vector<vector<char>> input = {
            {'.','#','.'},
            {'.','.','#'},
            {'#','#','#'}};
    inFile.close();
    return 0;
}

void procFile(ifstream &inFile, vector<pattern> &patt2, vector<pattern> &patt3){
    string from, to;
    unsigned long ind, num, patt2len, patt3len;
    istringstream iss;
    patt2len = patt3len = 0;
    while(getline(inFile, from)){
        iss = istringstream(from);
        iss >> from >> to;
        num = 0;
        if(from.size()%2 == 0){
            patt2.push_back({});
            vector<vector<char>>patt;
            for (int iii = 0; iii < 2; ++iii) {
                patt.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 2; ++jjj)
                    patt[iii].push_back(from[2*iii+jjj]);
            }
            patt2[patt2len].from.push_back(patt);
            for (int iii = 0; iii < 3; ++iii) {
                patt.clear();
                for (int jjj = 0; jjj < 2; ++jjj) {
                    patt.emplace_back(vector<char>());
                    for (int kkk = 0; kkk < 2; ++kkk) {
                        patt[iii].push_back(patt2[patt2len].from[iii][1-kkk][jjj]);
                    }
                }
            }
            patt2len++;
        }
        else if(from.size()%3 == 0){
            patt3.push_back({});
            vector<vector<char>>patt;
            for (int iii = 0; iii < 3; ++iii) {
                patt.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 3; ++jjj)
                    patt[iii].push_back(from[3*iii+jjj]);
            }
            patt2[patt2len].from.push_back(patt);
            for (int iii = 0; iii < 3; ++iii) {
                patt.clear();
                for (int jjj = 0; jjj < 3; ++jjj) {
                    patt.emplace_back(vector<char>());
                    for (int kkk = 0; kkk < 3; ++kkk) {
                        patt[iii].push_back(patt3[patt3len].from[iii][2-kkk][jjj]);
                    }
                }
            }
            patt3len++;
        }
        else{
            cout << "ERROR" << endl;
            exit(1);
        }
    }
}