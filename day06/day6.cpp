#include <iostream>
#include<bits/stdc++.h>

using namespace std;

vector<size_t> readInput() {
    string filePath = "./input.txt";
    fstream fileContent(filePath);
    vector<size_t> inputsVec= {};
    stringstream ss;
    string inputLine;
    getline(fileContent, inputLine);
    cout<<inputLine<<endl;
    ss<<inputLine;
    size_t n;
    char c; //For the comma

    while(ss>>n>>c) {
        inputsVec.push_back(n);
    }

    ss>>n;
    inputsVec.push_back(n);
    
    return inputsVec;
}

size_t totalFishes(const int &days, const vector<size_t> &input) {

    map<size_t,size_t> dayCount;
    
    for(int i=0 ; i<=8 ; i++) {
        dayCount[i] = 0;
    }
    
    for(auto &i: input) {
        dayCount[i]++;
    }
    
    
    for(int i=1; i<=days ; i++) {
        size_t d0Count = dayCount[0];
        for(int j=0 ; j<=8 ; j++) {
            if(j==6) {
                dayCount[6] = dayCount[7] + d0Count;
            }
            
            else if(j==8) {
                dayCount[8] = d0Count;
            }
            
            else {
                dayCount[j] = dayCount[j+1];
            }
        }
    }
    
    size_t sum = 0;
    
    for(auto &[k,v] : dayCount) {
        sum+=v;
    }

    return sum;
}

int main()
{
    vector<size_t> input = readInput();

    cout<<"PART 1 "<<totalFishes(80, input)<<endl;
    cout<<"PART 2 "<<totalFishes(256, input)<<endl;

    return 0;
}
