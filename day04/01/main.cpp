#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    ifstream inFile;
    inFile.open("input.txt");
    string line, word;
    unsigned password = 0;
    vector<vector<string>> file;
    unsigned file_length = 0;
    while(getline(inFile, line)){
        file.push_back(vector<string>());
        istringstream iss(line);
        while(iss >>word)
            file[file_length].push_back(word);
        file_length++;
    }
    int j;
    for (int i = 0; i < file_length; ++i) {
        sort(file[i].begin(), file[i].end());
        for (j = 0; j < file[i].size()-1; ++j) {
            if (file[i][j] == file[i][j + 1])
                break;
        }
        if(j == file[i].size()-1)
            password++;
    }
    cout << password;
    return 0;
}