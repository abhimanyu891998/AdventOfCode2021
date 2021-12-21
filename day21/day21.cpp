#include<bits/stdc++.h>

using namespace std;

typedef long long ll;


unordered_map<int,int> sumToPermutations = {
    {3,1},
    {4,3},
    {5,6},
    {6,7},
    {7,6},
    {8,3},
    {9,1}    
};


void part2Util(int p1Pos, int p2Pos, ll &p1Wins, ll &p2Wins, bool p1Playing, ll totalPaths, int p1Score, int p2Score) {

    if(p1Playing) {
        for(int i=3 ; i<=9 ; i++) {
            auto newPos = p1Pos;
            newPos+=i;

            while(newPos>10)
                newPos-=10;

            
            auto newScore1 = p1Score + newPos;

            if(newScore1>=21) {
                p1Wins += totalPaths * sumToPermutations[i];
            }
            else {
                part2Util(newPos, p2Pos, p1Wins, p2Wins, false, totalPaths*sumToPermutations[i], newScore1, p2Score);
            }
        }
    }

    else {
        for(int i=3 ; i<=9 ; i++) {
            auto newPos = p2Pos;
            newPos+=i;
            
            while(newPos > 10)
                newPos -=10;

            auto newScore2 = p2Score+newPos;

            if(newScore2>=21) {

                p2Wins+= totalPaths * sumToPermutations[i];

            }
            else {
                part2Util(p1Pos, newPos, p1Wins, p2Wins, true, totalPaths*sumToPermutations[i], p1Score, newScore2);
            }
        }
    }

}

ll solvePart2(const int &p1, const int &p2) {
    ll p1Wins = 0;
    ll p2Wins = 0;

    int p1Pos = p1;
    int p2Pos = p2;

    part2Util(p1Pos, p2Pos, p1Wins, p2Wins, true, 1, 0, 0);

    return  max(p1Wins, p2Wins);

}

ll solvepart1(const ll &p1, const ll &p2) {
    ll p1Score = 0;
    ll p2Score = 0;
    ll p1Pos = p1;
    ll p2Pos = p2;
    ll prevSteps = 0;
    ll n=3;
    ll throws = 0;
    bool p1Playing = true;
    while(p1Score<1000 && p2Score<1000) {
        ll totalSteps = (n*(n+1))/2;
        ll currSteps = totalSteps - prevSteps;
        prevSteps = totalSteps;
        if(p1Playing) {

            p1Pos= (p1Pos+currSteps>10)?((p1Pos + currSteps)%10 !=0 ? (p1Pos + currSteps)%10  : 10): (p1Pos+currSteps);
            p1Score+= p1Pos;
        }
        else {
            p2Pos= (p2Pos+currSteps>10)?((p2Pos + currSteps)%10 !=0 ? (p2Pos + currSteps)%10  : 10): (p2Pos+currSteps);
            p2Score+= p2Pos;
        }

        n+=3;
        throws+=3;
        p1Playing = !p1Playing;
    }

    if(p1Score>=1000) {
        return p2Score * throws;
    }


    return p1Score * throws;
}

int main() {
    fstream f("./sample.txt");
    string s;
    vector<ll> playerPos;

    while(getline(f,s)) {
        stringstream ss(s);
        string temp;
        getline(ss,temp,':');
        ll i;
        ss>>i;
        playerPos.push_back(i);
    }

    ll p1= playerPos[0];
    ll p2 = playerPos[1];

    cout<<"Part 1: "<<solvepart1(p1, p2)<<endl;

    ll p2Sol = solvePart2(p1,p2);

    cout<<"Part 2: "<<p2Sol<<endl;

}