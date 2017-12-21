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
void printPatterns(ofstream &outFile, vector<pattern> &patts);
vector<vector<char>> enhance(const vector<vector<char>> &input, const vector<pattern> &patts);
unsigned long findMatchingPattern(const vector<vector<char>> &inputPart, const vector<pattern> &patts);

int main() {
    ifstream inFile("input.txt");

    vector<pattern> patt3;
    vector<pattern> patt2;

    procFile(inFile, patt2, patt3);
    inFile.close();

    ofstream outFile("output2.txt");
    printPatterns(outFile, patt2);
    outFile.close();
    outFile.open("output3.txt");
    printPatterns(outFile, patt3);
    outFile.close();

    vector<vector<char>> input = {
            {'.','#','.'},
            {'.','.','#'},
            {'#','#','#'}};
    vector<vector<char>> output;
    for (int iii = 0; iii < 18; ++iii) {
        string fileName = "state_"+to_string(iii)+".txt";
        outFile.open(fileName);
        if(input[0].size()%2 == 0)
            output = enhance(input, patt2);
        else
            output = enhance(input, patt3);

        for(vector<char> line : output){
            for(char ch : line)
                outFile << ch;
            outFile << endl;
        }
        input = output;
        outFile.close();
    }
    unsigned long turnedOn = 0;
    for(vector<char> line : output)
        for(char ch : line)
            if(ch == '#')
                turnedOn++;
    cout << turnedOn << endl;
    return 0;
}

void procFile(ifstream &inFile, vector<pattern> &patt2, vector<pattern> &patt3){
    string from, to;
    unsigned long patt2len, patt3len;
    istringstream iss;
    patt2len = patt3len = 0;
    vector<vector<char>>patt;
    while(getline(inFile, from)){
        iss = istringstream(from);
        iss >> from >> to;
        if(from.size()%2 == 0){
            patt2.push_back({});
            patt.clear();
            for (int iii = 0; iii < 2; ++iii) {
                patt.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 2; ++jjj)
                    patt[iii].push_back(from[2*iii+jjj]);
            }
            patt2[patt2len].from.push_back(patt);
            for (int iii = 0; iii < 3; ++iii) { // rotate
                patt.clear();
                for (int jjj = 0; jjj < 2; ++jjj) {
                    patt.emplace_back(vector<char>());
                    for (int kkk = 0; kkk < 2; ++kkk) {
                        patt[jjj].push_back(patt2[patt2len].from[iii][1-kkk][jjj]);
                    }
                }
                patt2[patt2len].from.push_back(patt);
            }
            // flip 1 horizontal
            patt.clear();
            for (int iii = 0; iii < 2; ++iii) {
                patt.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 2; ++jjj)
                    patt[iii].push_back(patt2[patt2len].from[0][1-iii][jjj]);
            }
            patt2[patt2len].from.push_back(patt);
            // flip 2 vertical
            patt.clear();
            for (int iii = 0; iii < 2; ++iii) {
                patt.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 2; ++jjj)
                    patt[iii].push_back(patt2[patt2len].from[0][iii][1-jjj]);
            }
            patt2[patt2len].from.push_back(patt);
            // flip 3 horizontal
            patt.clear();
            for (int iii = 0; iii < 2; ++iii) {
                patt.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 2; ++jjj)
                    patt[iii].push_back(patt2[patt2len].from[1][1-iii][jjj]);
            }
            patt2[patt2len].from.push_back(patt);
            // flip 4 vertical
            patt.clear();
            for (int iii = 0; iii < 2; ++iii) {
                patt.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 2; ++jjj)
                    patt[iii].push_back(patt2[patt2len].from[1][iii][1-jjj]);
            }
            patt2[patt2len].from.push_back(patt);

            for (int iii = 0; iii < 3; ++iii) {
                patt2[patt2len].to.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 3; ++jjj)
                    patt2[patt2len].to[iii].push_back(to[3*iii+jjj]);
            }
            patt2len++;
        }
        else if(from.size()%3 == 0){
            patt3.push_back({});
            patt.clear();
            for (int iii = 0; iii < 3; ++iii) {
                patt.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 3; ++jjj)
                    patt[iii].push_back(from[3*iii+jjj]);
            }
            patt3[patt3len].from.push_back(patt);
            for (int iii = 0; iii < 3; ++iii) { //rotate
                patt.clear();
                for (int jjj = 0; jjj < 3; ++jjj) {
                    patt.emplace_back(vector<char>());
                    for (int kkk = 0; kkk < 3; ++kkk) {
                        patt[jjj].push_back(patt3[patt3len].from[iii][2-kkk][jjj]);
                    }
                }
                patt3[patt3len].from.push_back(patt);
            }
            // flip 1 horizontal
            patt.clear();
            for (int iii = 0; iii < 3; ++iii) {
                patt.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 3; ++jjj)
                    patt[iii].push_back(patt3[patt3len].from[0][2-iii][jjj]);
            }
            patt3[patt3len].from.push_back(patt);
            // flip 2 vertical
            patt.clear();
            for (int iii = 0; iii < 3; ++iii) {
                patt.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 3; ++jjj)
                    patt[iii].push_back(patt3[patt3len].from[0][iii][2-jjj]);
            }
            patt3[patt3len].from.push_back(patt);
            // flip 3 horizontal
            patt.clear();
            for (int iii = 0; iii < 3; ++iii) {
                patt.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 3; ++jjj)
                    patt[iii].push_back(patt3[patt3len].from[1][2-iii][jjj]);
            }
            patt3[patt3len].from.push_back(patt);
            // flip 4 vertical
            patt.clear();
            for (int iii = 0; iii < 3; ++iii) {
                patt.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 3; ++jjj)
                    patt[iii].push_back(patt3[patt3len].from[1][iii][2-jjj]);
            }
            patt3[patt3len].from.push_back(patt);

            for (int iii = 0; iii < 4; ++iii) {
                patt3[patt3len].to.emplace_back(vector<char>());
                for (int jjj = 0; jjj < 4; ++jjj)
                    patt3[patt3len].to[iii].push_back(to[4*iii+jjj]);
            }

            patt3len++;
        }
        else{
            cout << "ERROR" << endl;
            exit(1);
        }
    }
}

void printPatterns(ofstream &outFile, vector<pattern> &patts){
    unsigned long size = patts[0].from[0].size();
    for(const pattern &patt : patts){
        for (int iii = 0; iii < size; ++iii) {
            for (int jjj = 0; jjj < 8; ++jjj) {
                for (int kkk = 0; kkk < size; ++kkk) {
                    outFile << patt.from[jjj][iii][kkk];
                }
                outFile << '|';
            }
            outFile << endl;
        }
        outFile << string((size+1)*8,'-') << endl;
        for (int iii = 0; iii < size+1; ++iii) {
            for (int jjj = 0; jjj < size+1; ++jjj) {
                outFile << patt.to[iii][jjj];
            }
            outFile << endl;
        }
        outFile << (string(size+1,'=')) << endl;
    }
}

vector<vector<char>> enhance(const vector<vector<char>> &input, const vector<pattern> &patts){
    unsigned long inputSize = input[0].size();
    unsigned long pattSize = patts[0].from[0].size();
    unsigned long pixNum = inputSize/pattSize;
    unsigned long matchInd;
    vector<vector<char>> output(pixNum*(pattSize+1), vector<char>(pixNum*(pattSize+1)));
    vector<vector<char>> inputPart;
    for (int iii = 0; iii < pixNum; ++iii) {
        for (int jjj = 0; jjj < pixNum; ++jjj) {
            inputPart.clear();
            for (int kkk = 0; kkk < pattSize; ++kkk) {
                inputPart.emplace_back();
                for (int lll = 0; lll < pattSize; ++lll) {
                    inputPart[kkk].push_back(input[pattSize*iii+kkk][pattSize*jjj+lll]);
                }
            }
            matchInd = findMatchingPattern(inputPart, patts);
            if(matchInd != patts.size()){
                for (int kkk = 0; kkk < pattSize+1; ++kkk) {
                    inputPart.emplace_back();
                    for (int lll = 0; lll < pattSize+1; ++lll) {
                        output[(pattSize+1)*iii+kkk][(pattSize+1)*jjj+lll] = patts[matchInd].to[kkk][lll];
                    }
                }
            } else{
                cout << "ERROR";
                exit(1);
            }
        }
    }
    return output;
}

unsigned long findMatchingPattern(const vector<vector<char>> &inputPart, const vector<pattern> &patts){
    for (unsigned long iii = 0; iii < patts.size(); ++iii) {
        for (unsigned long jjj = 0; jjj < 8; ++jjj) {
            if(inputPart == patts[iii].from[jjj])
                return iii;
        }
    }
    return patts.size();
}