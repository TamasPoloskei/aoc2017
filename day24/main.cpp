#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

class Component{
public:
    unsigned long m_ID = {0};
    vector<unsigned long> m_pins;
    explicit Component(unsigned long ID, vector<unsigned long> pins) : m_ID{ID}, m_pins{pins}
    {
    }
};

unsigned long bridgeStrength(vector<Component> &components, vector<unsigned long> &inBridge);
unsigned long findMaxStrengthBridge(vector<vector<unsigned long>> pinList, vector<Component> &components, vector<unsigned long> inBridge, unsigned long pinNum);
int main() {
    ifstream inFile("input.txt");
    vector<vector<unsigned long>> pinList;
    vector<Component> components;
    istringstream iss;
    string line;
    unsigned long ID = 0;
    unsigned long pin1, pin2;
    while(getline(inFile, line)){
        iss = istringstream(line);
        iss >> pin1 >> pin2;
        while(pinList.size() <= pin1 || pinList.size() <= pin2)
            pinList.emplace_back(vector<unsigned long>());
        pinList[pin1].push_back(ID);
        if(pin1 != pin2)
            pinList[pin2].push_back(ID);
        components.push_back(Component(ID, {pin1, pin2}));
        ID++;
    }
    inFile.close();
    ofstream outFile("output.txt");
    for(unsigned long iii = 0; iii < pinList.size(); iii++){
        outFile << setw(3) << iii << ": ";
        for (unsigned long jjj = 0; jjj < pinList[iii].size(); ++jjj) {
            outFile << setw(3) << pinList[iii][jjj] << " ";
        }
        outFile << endl;
    }
    outFile.close();

    for(unsigned long iii = 0; iii < pinList[0].size(); iii++){
        vector<vector<unsigned long>> pinListCpy = pinList;
        vector<unsigned long> inBridge = {pinListCpy[0][iii]};
        auto it = find(
                pinListCpy[components[inBridge[0]].m_pins[1]].begin(),
                pinListCpy[components[inBridge[0]].m_pins[1]].end(),
                inBridge[0]);
        pinListCpy[components[inBridge[0]].m_pins[1]].erase(it);
        pinListCpy[0].erase(pinListCpy[0].begin()+iii);
        cout << findMaxStrengthBridge(pinListCpy, components, inBridge, components[inBridge[0]].m_pins[1]) << endl;
    }
    return 0;
}

unsigned long findMaxStrengthBridge(vector<vector<unsigned long>> pinList, vector<Component> &components, vector<unsigned long> inBridge, unsigned long pinNum){
    if(pinList[pinNum].empty()){
//        cout << pinNum << " | " << bridgeStrength(components, inBridge) << endl;
//        return bridgeStrength(components, inBridge);
        return bridgeStrength(components, inBridge)+ 100000*inBridge.size();
    }
    unsigned long maxStrength = 0;
    unsigned long tempMaxStrength;
    unsigned long newPinNum;
    for(unsigned long iii = 0; iii < pinList[pinNum].size(); iii++){
        if(components[pinList[pinNum][iii]].m_pins[0] == pinNum)
            newPinNum = components[pinList[pinNum][iii]].m_pins[1];
        else
            newPinNum = components[pinList[pinNum][iii]].m_pins[0];
//        cout << pinNum << " " << newPinNum <<endl;
        vector<vector<unsigned long>> pinListCpy = pinList;
        vector<unsigned long> inBridgeCpy = inBridge;
        inBridgeCpy.push_back(pinListCpy[pinNum][iii]);
        if(newPinNum != pinNum){
            auto it = find(
                    pinListCpy[newPinNum].begin(),
                    pinListCpy[newPinNum].end(),
                    inBridgeCpy[inBridgeCpy.size()-1]);
            pinListCpy[newPinNum].erase(it);
        }
        pinListCpy[pinNum].erase(pinListCpy[pinNum].begin()+iii);
        tempMaxStrength = findMaxStrengthBridge(pinListCpy, components, inBridgeCpy, newPinNum);

        if(tempMaxStrength > maxStrength)
            maxStrength = tempMaxStrength;
    }
    return maxStrength;

}

unsigned long bridgeStrength(vector<Component> &components, vector<unsigned long> &inBridge){
    unsigned long strength = 0;
    for(unsigned long ID : inBridge)
        strength += (components[ID].m_pins[0] + components[ID].m_pins[1]);
    return strength;
}