#include <iostream>
#include <deque>
#include <fstream>
#include <algorithm>

using namespace std;

class Point{
public:
    long int m_x;
    long int m_y;
    Point(){
        m_x = 0;  m_y = 0;
    }
    Point(long int x, long int y, long int state){
        m_x = x; m_y = y;
    }
};

// 0 - cleaned
// 1 - weakened
// 2 - infected
// 3 - flagged

int main() {
    long width = 25;
    long height = 25;
    deque<deque<int>> map(width,deque<int>(width));
    ifstream inFile("input.txt");
    Point virus(0,0,-1);
    Point dir(0,1,-1);
    string line;

    long int xmin = -width/2;
    long int xmax = width/2;
    long int ymin = -height/2;
    long int ymax = height/2;
    long int row, col;
    for (int iii = 0; iii < height; ++iii) {
        getline(inFile, line);
        for (int jjj = 0; jjj < width; ++jjj) {
            if(line[jjj] == '#')
                map[iii][jjj] = 2;
        }
    }

    unsigned long burstNum = 0;
    for (unsigned long iii = 0; iii < 10000000; ++iii) {
        row = -virus.m_y+ymax;
        col = virus.m_x-xmin;
        if(iii%100000 == 0)
            cout << iii << ": " << burstNum << ", " << width << " " << height << endl;
        if(map[row][col] == 0){// turns left if it is clean
            swap(dir.m_x,dir.m_y);
            dir.m_x *= -1;
        } else if(map[row][col] == 1){// weakened
            ;
        }
        else if(map[row][col] == 2){// turns right if it is infected
            swap(dir.m_x,dir.m_y);
            dir.m_y *= -1;
        }
        else if(map[row][col] == 3){//flagged turns direction
            dir.m_x *= -1;
            dir.m_y *= -1;
        } else{
            cout << "ERROR" << endl;
            exit(1);
        }
        map[row][col]++;
        if(map[row][col] == 2)
            burstNum++;

        map[row][col]%=4;

        virus.m_x += dir.m_x;
        virus.m_y += dir.m_y;
        if(virus.m_x < xmin){
            for(deque<int> &mapRow : map)
                mapRow.push_front(0);
            xmin--;
            width++;
        }
        else if(virus.m_x > xmax){
            for(deque<int> &mapRow : map)
                mapRow.push_back(0);
            xmax++;
            width++;
        }
        else if(virus.m_y > ymax){
            map.push_front(deque<int>(width));
            ymax++;
            height++;
        }
        else if(virus.m_y < ymin){
            map.push_back(deque<int>(width));
            ymin--;
            height++;
        }
    }

    inFile.close();
    cout << burstNum << endl;
    return 0;
}