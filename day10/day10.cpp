#include<bits/stdc++.h>

using namespace std;

unordered_map<char,int> scoreTable = {
    {')' , 3},
    {']', 57},
    {'}', 1197},
    {'>', 25137}
};

unordered_map<char,int> scoreTablePart2 = {
    {'(' , 1},
    {'[', 2},
    {'{', 3},
    {'<', 4}
};



vector<char> open = {'{', '(', '[', '<'};
vector<char> close = {'}', ')', ']', '>'};

size_t part2(string s){
    stack<char> checker;
    for(auto &c: s) {
    auto it = find(close.begin(), close.end(), c);

    if(it!= close.end()) {
        int index = it - close.begin();
        char top = checker.top();
        if(top!=open[index]) {
            checker = {};
            break;
        }
        checker.pop();
    }

    else {
        checker.push(c);
    }
    }

    size_t score =0;

    while(!checker.empty()) {

        char top = checker.top();
        score = 5*score + scoreTablePart2[top];
        checker.pop();
    } 

    return score;
    
}


int part1(string s) {
    stack<char> checker;
    for(auto &c: s) {
        auto it = find(close.begin(), close.end(), c);

        if(it!= close.end()) {
            int index = it - close.begin();
            char openChar = open[index];

            if(checker.empty()) {
                return scoreTable[c];
            }

            char top = checker.top();
            checker.pop();
            if(top!=openChar) {
                return scoreTable[c];
            }
        }

        else {
            checker.push(c);
        }
    }

    return 0;
}




int main() {
    fstream f("./input.txt");
    string s;
    int sum =0;
    vector<size_t> part2Vec;
    while(getline(f,s)) {
        int result = part1(s);
        sum += result;
        if(result == 0) {
            size_t score = part2(s);
            part2Vec.push_back(score);
        }
    }

    sort(part2Vec.begin(), part2Vec.end());

    cout<<"PART 1: "<<sum<<endl;
    cout<<"PART 2: "<<part2Vec[part2Vec.size()/2]<<endl;
}