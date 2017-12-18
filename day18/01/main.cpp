#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

typedef enum instrType{
    SND, SET, ADD, MUL, MOD, RCV, JGZ
} instrType;

typedef enum argType{
    REG, NUM
} argType;
typedef struct instr{
    instrType ins;
    vector<argType> argTypes;
    vector<char> argChar;
    vector<long int> argNums;
} instr;

void procFile(ifstream &inFile, vector<instr> &instrs);
vector<long> readMemory(const instr &ins, const vector<long> & memory);
void runInstruction(vector<instr> &instrs,  vector<long> &memory, long &pos, long &lastSound);

int main() {
    ifstream inFile("input.txt");
    vector<instr> instrs;
    string line, word;
    istringstream iss;
    unsigned instrsSize = 0;
    procFile(inFile, instrs);
    vector<long> memory(26);
    long pos = 0;
    long lastSound;
    while(pos > -1 && pos < instrs.size()){
        runInstruction(instrs, memory, pos, lastSound);
    }

    inFile.close();
    return 0;
}

void procFile(ifstream &inFile, vector<instr> &instrs){
    string line, word;
    istringstream iss;
    unsigned instrsSize = 0;
    while(getline(inFile, line)){
        iss = istringstream(line);
        iss >> word;
        if(word == "snd")
            instrs.push_back({instrType::SND,{},{},{}});
        else if(word == "set")
            instrs.push_back({instrType::SET,{},{},{}});
        else if(word == "add")
            instrs.push_back({instrType::ADD,{},{},{}});
        else if(word == "mul")
            instrs.push_back({instrType::MUL,{},{},{}});
        else if(word == "mod")
            instrs.push_back({instrType::MOD,{},{},{}});
        else if(word == "rcv")
            instrs.push_back({instrType::RCV,{},{},{}});
        else if(word == "jgz")
            instrs.push_back({instrType::JGZ,{},{},{}});
        else{
            cout << word;
            exit(1);
        }
        while(iss >> word ) {
            if (isdigit(word[0]) || word[0] == '-') {
                instrs[instrsSize].argTypes.push_back(argType::NUM);
                instrs[instrsSize].argNums.push_back(stoi(word));
                instrs[instrsSize].argChar.push_back(0);
            }
            else{
                instrs[instrsSize].argTypes.push_back(argType::REG);
                instrs[instrsSize].argChar.push_back(word[0]);
                instrs[instrsSize].argNums.push_back(0);
            }
        }
        instrsSize++;
    }
}

vector<long> readMemory(const instr &ins, const vector<long> & memory){
    vector<long> memoryVal;
    for (int iii = 0; iii < ins.argTypes.size(); ++iii) {
        if(ins.argTypes[iii] == argType::REG)
            memoryVal.push_back(memory[ins.argChar[iii] - 'a']);
        else
            memoryVal.push_back(ins.argNums[iii]);
    }
    return memoryVal;
}

void runInstruction(vector<instr> &instrs,  vector<long> &memory, long &pos, long &lastSound){
    vector<long> regVal(readMemory(instrs[pos], memory));
    if(instrs[pos].ins == instrType::SND){
        cout << regVal[0] << endl;
        lastSound = regVal[0];
    }
    else if(instrs[pos].ins == instrType::SET)
        memory[instrs[pos].argChar[0]-'a'] = regVal[1];
    else if(instrs[pos].ins == instrType::ADD)
        memory[instrs[pos].argChar[0]-'a'] += regVal[1];
    else if(instrs[pos].ins == instrType::MUL)
        memory[instrs[pos].argChar[0]-'a'] *= regVal[1];
    else if(instrs[pos].ins == instrType::MOD)
        memory[instrs[pos].argChar[0]-'a'] %= regVal[1];
    else if(instrs[pos].ins == instrType::RCV)
        if(regVal[0] != 0){
            cout << "RCV: " << lastSound << endl;
            pos = instrs.size();
        } else
            ;
    else if(instrs[pos].ins == instrType::JGZ)
        if(regVal[0] > 0){
            pos += (regVal[1] - 1);
        } else
            ;
    else{
        cout << "ERROR " << pos << endl;
        exit(1);
    }
    pos++;
}