#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

typedef enum dir{
    EAST, NORTH, WEST, SOUTH
} dir;

int main() {
    vector<string> map;
    ifstream inFile("input.txt");
    istringstream iss;
    string line;
    dir direction;
    map.push_back(string(500,' '));
    while(getline(inFile, line))
        map.push_back(" "+line+string(500,' '));
    map.push_back(string(500,' '));

    unsigned row, col;
    row = 1;
    string letters;
    for (col = 0; map[row][col] != '|'; ++col)
        ;
    direction = SOUTH;

    unsigned steps = 0;
    while(map[row][col] != ' '){
        if(isalpha(map[row][col]))
            letters += map[row][col];
        if(map[row][col] == '+'){
            if(map[row][col+1] != ' ' && direction != dir::WEST)
                direction = dir::EAST;
            else if(map[row-1][col] != ' ' && direction != dir::SOUTH)
                direction = dir::NORTH;
            else if(map[row][col-1] != ' ' && direction != dir::EAST)
                direction = dir::WEST;
            else if(map[row+1][col] != ' ' && direction != dir:: NORTH)
                direction = dir::SOUTH;
            else
                cout << "ERROR" << endl;
        }
        if(direction == dir::EAST)
            col++;
        else if(direction == dir::NORTH)
            row--;
        else if(direction == dir::WEST)
            col--;
        else if(direction == dir::SOUTH)
            row++;
        else
            cout << "ERROR" << endl;
        steps++;
    }
    cout << letters << endl;
    cout << steps << endl;
    return 0;
}