#include <iostream>
#include <deque>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Computer{
public:
    int m_state;
    deque<int> m_tape;
    long int m_pos;
    long int m_minpos, m_maxpos;

    Computer(): m_state{0}, m_tape{deque<int>(1)}, m_pos{0}, m_minpos{0}, m_maxpos{0}{}

    void step(int stepSize){
        if(m_pos+stepSize > m_maxpos){
            m_maxpos++;
            m_tape.push_back(0);
        }
        else if(m_pos+stepSize < m_minpos){
            m_minpos--;
            m_tape.push_front(0);
        }
        m_pos += stepSize;
    }

    int readTape(){
        return m_tape[m_pos - m_minpos];
    }

    void writeTape(int val){
        m_tape[m_pos - m_minpos] = val;
    }

    void setState(int newState){
        m_state = newState;
    }
    friend ostream& operator<< (ostream & out, Computer const & data){
        out  << setw(3)
             << "POS:" << data.m_pos
             << " STA:" << data.m_state
             << " MIN:" << data.m_minpos
             << " MAX:" << data.m_maxpos
             << " SIZ:" << data.m_tape.size()<< endl;
        return out;
    }
};

class State{
public:
    vector<int> m_write;
    vector<int> m_stepSize;
    vector<int> m_newState;
    State(): m_write{vector<int>(2)}, m_stepSize{vector<int>(2)}, m_newState{vector<int>(2)}{}
};
int main() {
    Computer turing;
    ifstream inFile("input.txt");
    vector<State> states;
    unsigned long maxSteps;
    inFile >> maxSteps;
    cout << maxSteps << endl;
    string str;
    while(inFile.get()!='\n')
        ;
    unsigned long stateNum = 0;
    while(getline(inFile, str)){
        cout << str << endl;
        states.emplace_back(State());
        for (int iii = 0; iii < 2; ++iii) {
            inFile >> states[stateNum].m_write[iii];
            while(inFile.get()!='\n')
                ;
            getline(inFile, str);
            if(str == "right")
                states[stateNum].m_stepSize[iii] = 1;
            else
                states[stateNum].m_stepSize[iii] = -1;
            getline(inFile, str);
            states[stateNum].m_newState[iii] = str[0]-'A';
        }
        getline(inFile, str);
        stateNum++;
    }
    int currVal;
    for (unsigned long iii = 0; iii < maxSteps; ++iii) {
//        cout << turing;
        currVal = turing.readTape();
        turing.writeTape(states[turing.m_state].m_write[currVal]);
        turing.step(states[turing.m_state].m_stepSize[currVal]);
        turing.setState(states[turing.m_state].m_newState[currVal]);
    }
    cout << turing;
    cout << accumulate(turing.m_tape.begin(), turing.m_tape.end(),0) << endl;
    return 0;
}