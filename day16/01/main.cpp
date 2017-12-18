#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

unsigned const letterNum = 16;
void spin(vector<char> &list, unsigned num);
void exchange(vector<char> &list, unsigned pos1, unsigned pos2);
void partner(vector<char> &list, char ch1, char ch2);

int main() {
    vector<char> list;
    for (int i = 0; i < letterNum; ++i) {
        list.emplace_back('a'+i);
    }
    ifstream inFile("input.txt");
    string line;
    char ch, ch1, ch2;
    unsigned pos1, pos2;
    istringstream iss;
    while(getline(inFile,line)){
        iss = istringstream(line);
        iss >> ch;
        switch(ch){
            case 'x':
                iss >> pos1 >> pos2;
                exchange(list, pos1, pos2);
                break;
            case 'p':
                iss >> ch1 >> ch2;
                partner(list, ch1, ch2);
                break;
            case 's':
                iss >> pos1;
                spin(list,pos1);
                break;
            default:
            cout << "ERROR " << line << endl;
                break;
        }
    }
    inFile.close();
    for (int i = 0; i < letterNum; ++i) {
        cout << list[i];
    }
    return 0;
}

void spin(vector<char> &list, unsigned num){
    vector<char> temp;
    for (int i = 0; i < num; ++i) {
        temp.emplace_back(list[letterNum-num+i]);
    }
    for (int i = 0; i < letterNum-num; ++i) {
        list[letterNum-1-i] = list[letterNum-num-1-i];
    }
    for (int i = 0; i < num; ++i) {
        list[i] = temp[i];
    }
}

void exchange(vector<char> &list, unsigned pos1, unsigned pos2){
    char temp;
    temp = list[pos1]; list[pos1] = list[pos2]; list[pos2] = temp;
}

void partner(vector<char> &list, char ch1, char ch2){
    long pos1 = distance(list.begin(), find(list.begin(), list.end(), ch1));
    long pos2 = distance(list.begin(), find(list.begin(), list.end(), ch2));
    exchange(list, pos1, pos2);
}