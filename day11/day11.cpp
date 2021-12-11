#include<bits/stdc++.h>

using namespace std;

#define PART 1 //Change this value according to the part you wanna solve


vector<pair<int,int>> getNeighbors(const int &i, const int &j, const int &r, const int &c) {
    vector<pair<int,int>> neighbors;

    if(i>0)
        neighbors.push_back({i-1, j});

    if(j>0)
        neighbors.push_back({i, j-1});

    if(i<r-1)
        neighbors.push_back({i+1, j});

    if(j<c-1)
        neighbors.push_back({i, j+1});

    if(i>0 && j>0)
        neighbors.push_back({i-1, j-1});

    if(i<r-1 && j<c-1)
        neighbors.push_back({i+1, j+1});

    if(i>0 && j<c-1)
        neighbors.push_back({i-1, j+1});

    if(i<r-1 && j>0)
        neighbors.push_back({i+1, j-1});

    return neighbors;
}

int bfs(vector<vector<int>> &input, const int &r, const int &c) {
    int count = 0;
    queue<pair<int,int>> q;
    vector<vector<bool>> visited(input.size(), vector<bool>(input[0].size(), false));
    for(int i= 0 ; i<r ; i++) {
        for(int j=0; j<c; j++) {
            input[i][j]+=1;
            if(input[i][j]>9) {
                q.push(make_pair(i,j));
                visited[i][j] = true;
                input[i][j] = 0;
                count++;
            }
        }
    }

    while(!q.empty()) {
        pair<int,int> top = q.front();
        q.pop();
        auto [i,j] = top;
        visited[i][j] = true;
        vector<pair<int,int>> neighbors = getNeighbors(i, j, r, c);
        for(auto &[in,jn] : neighbors) {
            if(!visited[in][jn]) {
                input[in][jn]+=1;
                if(input[in][jn] > 9) {
                    input[in][jn] = 0;
                    visited[in][jn] = true;
                    count++;
                    q.push({in,jn});
                }
            }
        }
    }

    #if PART==2
    bool allLit = true;
    for(int i=0 ; i<visited.size() ; i++) {
        for(int j=0; j<visited[0].size() ; j++) {
            if(visited[i][j] == false) {
                allLit = false;
                break;
            }
        }
    }
    if(allLit) {
        return 1;
    }
    else {
        return 0;
    }
    #endif

    return count;

}


int main() {

    fstream f("./input.txt");
    string s;
    vector<vector<int>> input;
    while(getline(f,s)) {
        stringstream ss(s);
        char c;
        vector<int> temp;
        while(ss>>c) {
            int n = c-'0';
            temp.push_back(n);
        }
        input.push_back(temp);
    }

    int sum=0;

    int r = input.size();
    int c = input[0].size();

    int limit;

    #if PART==1
    limit = 100;
    
    #elif PART==2
    limit = 100000;
    #endif

    int part2 = 0;

    for(int i=0 ; i<limit; i++) {
        int count = bfs(input, r,c);
        if(limit == 100000) {
            if(count == 1) {
                part2 = i;
                break;
            }
        } else {
            sum+=count;
        }
        
    }

    #if PART==1
    cout<<"PART 1 "<<sum<<endl;
    #elif PART==2
    cout<<"PART 2 "<<part2+1<<endl;
    #endif

    return 0;
}