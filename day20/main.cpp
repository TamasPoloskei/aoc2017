#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

typedef struct particle{
    vector<long> pos;
    vector<long> vel;
    vector<long> acc;
    unsigned long dist;
} particle;

int main() {
    ifstream inFile("input.txt");
    string line;
    istringstream iss;
    vector<particle> parts;
    long posx, posy, posz, velx, vely, velz, accx, accy,accz;
    unsigned long ind = 0;
    while(getline(inFile,line)){
        iss = istringstream(line);
        iss >> posx >> posy >> posz >> velx >> vely >> velz >> accx >> accy >> accz;
        parts.emplace_back();
        parts[ind].pos = {posx,posy,posz};
        parts[ind].vel = {velx,vely,velz};
        parts[ind].acc = {accx,accy,accz};
        parts[ind].dist = abs(posx)+abs(posy)+abs(posz);
        ind++;
    }

    unsigned long closestDist = parts[0].dist;
    unsigned long smallestAcc = abs(parts[0].acc[0])+abs(parts[0].acc[1])+abs(parts[0].acc[2]);
    unsigned long closestId = 0;
    for(unsigned long iii = 1; iii < parts.size(); iii++){
        if(abs(parts[iii].acc[0])+abs(parts[iii].acc[1])+abs(parts[iii].acc[2]) <= smallestAcc){
            closestId = iii;
            smallestAcc = abs(parts[iii].acc[0])+abs(parts[iii].acc[1])+abs(parts[iii].acc[2]);
            cout << closestId << " " << smallestAcc << endl;
        }
    }
    cout << closestId << " " << smallestAcc << endl;
//    bool gettingCloser = true;
//    for(ind = 0; ind < 100; ind++){
//        for (int iii = 0; iii < parts.size(); ++iii) {
//            for (int jjj = 0; jjj < 3; ++jjj) {
//                parts[iii].vel[jjj] += parts[iii].acc[jjj];
//                parts[iii].pos[jjj] += parts[iii].vel[jjj];
//            }
//            if(abs(parts[iii].pos[0])+abs(parts[iii].pos[1])+abs(parts[iii].pos[2]) < parts[iii].dist)
//                parts[iii].dist = abs(parts[iii].pos[0])+abs(parts[iii].pos[1])+abs(parts[iii].pos[2]);
////            else{
////                parts.erase(parts.begin()+iii);
////                iii--;
////            }
//        }
//        for(unsigned long iii = 0; iii < parts.size(); iii++){
//            if(parts[iii].dist < closestDist){
//                closestDist = parts[iii].dist;
//                closestId = iii;
//                cout << closestId << " " << closestDist << " " << ind << endl;
//            }
//        }
//    }
    inFile.close();
    return 0;
}

