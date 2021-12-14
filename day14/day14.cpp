#include<bits/stdc++.h>

using namespace std;

vector<string> split(string s, string delim) {
    vector<string> elems;
    while(s.find(delim)!=string::npos) {
        elems.emplace_back(s.substr(0, s.find(delim)));
        s = s.substr(s.find(delim) + delim.size());
    }

    elems.emplace_back(s);

    return elems;
}



int main() {

    fstream f("./input.txt");
    string s;
    string polymer;
    getline(f,polymer);
    getline(f,s);

    unordered_map<string, char> rules;

    while(getline(f,s)) {
        vector<string> elems = split(s, " ->");
        rules[elems[0]] = elems[1][1];   
    }

    unordered_map<string,  long long> pairFreqs;
    unordered_map<char,  long long> charFreq;

    for( long long i=0; i<polymer.size()-1 ; i++) {
        string pair;
        pair.push_back(polymer[i]);
        pair.push_back(polymer[i+1]);
        charFreq[polymer[i]]++;
        pairFreqs[pair]++;
    }
    charFreq[polymer[polymer.size()-1]]++;

    long long n = 40; // Change according to part 1 or part 2 

    while(n--) {
        unordered_map<string,  long long> newMap;
        cout<<n<<" "<<pairFreqs.size()<<endl;
        for(auto &[pair, freq]: pairFreqs) {
                char insert = rules[pair];
                long long f = freq;
                char a = pair[0];
                char b = pair[1];
                string pair1;
                string pair2;
                pair1.push_back(a);
                pair1.push_back(insert);
                pair2.push_back(insert);
                pair2.push_back(b);
                newMap[pair1]+=freq;
                newMap[pair2]+=freq;
                charFreq[insert]+=freq;
          
        }
        swap(newMap, pairFreqs);
    }

    for(auto &[pair, freq]: pairFreqs) {
        cout<<pair<<" "<<freq<<endl;
    }

    long long maxi =  0;
    long long mini =  LLONG_MAX;

    for(auto &[c,freq]: charFreq) {
        maxi = max(maxi, freq);
        mini = min(mini, freq);
    }

    cout<<maxi-mini<<endl;

    return 0;
}