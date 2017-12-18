#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

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
    string line;
    char ch, ch1, ch2;
    unsigned pos1, pos2;
    istringstream iss;
    ofstream outFile("output.txt");
    for (int iii = 0; iii < 25; ++iii) {
        ifstream inFile("input.txt");

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
        for (int i = 0; i < letterNum; ++i) {
            outFile <<list[i];
            cout << list[i];
        }
        outFile << endl;
        cout << endl;
        vector<unsigned> change(letterNum);
        for (int i = 0; i < letterNum; ++i) {
            change[i] = distance(list.begin(), find(list.begin(), list.end(), 'a'+i));
        }
        cout << setw(3) << iii << " : ";
        for (unsigned chElem : change) {
            cout << setw(3) << chElem;
        }
        cout << endl;
        inFile.close();
    }
    outFile.close();
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