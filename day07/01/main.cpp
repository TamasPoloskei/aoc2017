#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>

typedef struct program{
    std::string name;
    int weight;
    std::vector<std::string> children;
    std::vector<unsigned> childInd;
    std::vector<int> sumOnBranches;
    long parentInd;
} program;

int setSumOnBranch(std::vector<program> &programs, int ind);

int main() {
    std::fstream inFile;
    inFile.open("input.txt");
    std::string line, word;
    std::istringstream iss;
    std::vector<program> programs;
    int weight;
    // reading in the file
    while(getline(inFile,line))
    {
        iss = std::istringstream(line);
        iss >> word;
        iss >> weight;
        programs.push_back({word,weight, std::vector<std::string>()});
        while(iss >> word){
            programs[programs.size()-1].children.push_back(word);
        }
    }
    // sorting the list to get the root to the top
    for (int i = 0; i < programs.size(); ++i) {
        for (int j = i+1; j < programs.size(); ++j) {
            for (int k = 0; k < programs[j].children.size(); ++k) {
                if(programs[i].name == programs[j].children[k]){
                    std::swap(programs[i],programs[j]);
                    i--;
                    j = programs.size();
                }
            }
        }
    }
    std::vector<program> new_programs;
    new_programs.push_back(programs[0]);
    new_programs[0].parentInd = -1;
    programs.erase(programs.begin()+0);

    for (unsigned i = 0; i < new_programs.size(); ++i) {
        for (std::string child : new_programs[i].children) {
            for (unsigned j = 0; j < programs.size(); ++j) {
                if (child == programs[j].name) {
                    new_programs.push_back(programs[j]);
                    new_programs[i].childInd.push_back(new_programs.size() - 1);
                    new_programs[new_programs.size() - 1].parentInd = i;
                    programs.erase(programs.begin() + j);
                    j = programs.size();
                }
            }
        }
    }

    setSumOnBranch(new_programs, 0);
    for (int l = 107; l < 111; ++l) {
        std::cout << "\n" << new_programs[l].weight << '\n';
        for(int sum : new_programs[l].sumOnBranches)
            std::cout << "|" << sum;
        std::cout << '\n';
    }

    for(program p: new_programs)
    {
        std::sort(p.sumOnBranches.begin(),p.sumOnBranches.end());
        auto it = std::unique(p.sumOnBranches.begin(), p.sumOnBranches.end());
        p.sumOnBranches.resize(std::distance(p.sumOnBranches.begin(), it));
        if(p.sumOnBranches.size() == 2)
        {
            std::cout << p.name << " " << p.weight << " | ";
            for (int sum : p.sumOnBranches) {
                std::cout << sum << " - ";
            }
            for(unsigned ind : p.childInd)
                std::cout << ind << '|';
            std::cout << '|' <<p.parentInd << "| |";
        }
    }

    for (program p : new_programs) {
        std::cout << p.name << " " << p.weight;
//        for(std::string &child : p.children){
//            std::cout << '|' << child;
//        }
        std::cout << '|';
        for(unsigned ind : p.childInd)
            std::cout << ind << '|';
        std::cout << '|' <<p.parentInd << "| |";
        for(int sum : p.sumOnBranches)
            std::cout << sum << '|';
        std::cout << '\n';
    }
    return 0;
}

int setSumOnBranch(std::vector<program> &programs, int ind)
{
    if(programs[ind].children.empty()){
        programs[ind].sumOnBranches.push_back(programs[ind].weight);
        return programs[ind].weight;
    }
    int sumWeight = 0;
    int weight;
    for (int i = 0; i < programs[ind].childInd.size(); ++i) {
        programs[ind].sumOnBranches.push_back(setSumOnBranch(programs, programs[ind].childInd[i]));
    }
    return  std::accumulate(programs[ind].sumOnBranches.begin(),programs[ind].sumOnBranches.end(),0) + programs[ind].weight;
}