#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>


using namespace std;

#define INPUT_PATH "./input.txt"

vector<int> getInput(const string &input) {
   stringstream ss(input);
   vector<int> inputVec;
   while(ss) {
    char c;
    int num;
    ss>>num;
    ss>>c;
    inputVec.push_back(num);
   }

   return inputVec;
}

int partOne(const vector<int> &inputVec){
    vector<int> inputVecCopy = inputVec;
    sort(inputVecCopy.begin(), inputVecCopy.end());
    int median;
    if(inputVecCopy.size() % 2 == 0) {
        median = (inputVecCopy[inputVecCopy.size()/2] + inputVecCopy[inputVecCopy.size()/2 -1])/2;
    } else {
        median = inputVecCopy[inputVecCopy.size()/2];
    }
    int sum = 0;

    for(auto &i : inputVec) {
        sum+= abs(i-median);
    }

    return sum;
}


int partTwo(const vector<int> &arr) {
    size_t maxEle = *max_element(arr.begin(), arr.end());
    size_t bestCost = INT_MAX;
    for(int i=0 ; i<=maxEle; i++) {
        size_t cost = 0;
        for(auto &j: arr) {
            int n = abs(j-i);
            cost+= (n*(n+1))/2;
        }
        bestCost = min(cost, bestCost);
    }

    return bestCost;
}

 
int main() {

    fstream inputStream(INPUT_PATH);
    string input; 
    getline(inputStream, input);
    
    vector<int> inputVec = getInput(input);

    cout<<"PART 1: "<<partOne(inputVec)<<endl;
    cout<<"PART 2: "<<partTwo(inputVec)<<endl;
    

    return 0;
}