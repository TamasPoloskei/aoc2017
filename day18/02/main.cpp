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
void runInstruction(vector<instr> &instrs,  vector<long> &memory, long &pos, vector<long> &rcv, vector<long> &snd,
                    unsigned &sent);

int main() {
    ifstream inFile("input.txt");
    vector<instr> instrs;
    procFile(inFile, instrs);
    vector<long> memory0(26);
    vector<long> rcv0;
    memory0['p'-'a']  = 0;
    vector<long> rcv1;
    vector<long> memory1(26);
    memory1['p'-'a']  = 1;
    long pos0 = 0;
    long pos1 = 0;
    unsigned sent0 = 0;
    unsigned sent1 = 0;
    while(pos0 > -1 && pos0 < instrs.size() && pos1 > -1 && pos1 < instrs.size() &&
            !(instrs[pos0].ins == instrType::RCV && rcv0.empty() &&
            instrs[pos1].ins == instrType::RCV && rcv1.empty())){
        do {
            runInstruction(instrs, memory0, pos0, rcv0, rcv1, sent0);
        } while(pos0 > -1 && pos0 < instrs.size() && !(instrs[pos0].ins == instrType::RCV && rcv0.empty()));
        do {
            runInstruction(instrs, memory1, pos1, rcv1, rcv0, sent1);
        } while(pos1 > -1 && pos1 < instrs.size() && !(instrs[pos1].ins == instrType::RCV && rcv1.empty()));
    }
    cout << sent0 << endl << sent1 << endl;
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

void runInstruction(vector<instr> &instrs,  vector<long> &memory, long &pos, vector<long> &rcv, vector<long> &snd,
                    unsigned &sent){
    vector<long> regVal(readMemory(instrs[pos], memory));
    if(instrs[pos].ins == instrType::SND){
        sent++;
        snd.push_back(regVal[0]);
    }
    else if(instrs[pos].ins == instrType::SET)
        memory[instrs[pos].argChar[0]-'a'] = regVal[1];
    else if(instrs[pos].ins == instrType::ADD)
        memory[instrs[pos].argChar[0]-'a'] += regVal[1];
    else if(instrs[pos].ins == instrType::MUL)
        memory[instrs[pos].argChar[0]-'a'] *= regVal[1];
    else if(instrs[pos].ins == instrType::MOD)
        memory[instrs[pos].argChar[0]-'a'] %= regVal[1];
    else if(instrs[pos].ins == instrType::RCV){
        if(rcv.empty())
            pos--;
        else{
            memory[instrs[pos].argChar[0] - 'a'] = rcv[0];
            rcv.erase(rcv.begin());
        }
    }
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