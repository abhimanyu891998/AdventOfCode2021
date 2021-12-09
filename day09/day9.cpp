#include <bits/stdc++.h>

using namespace std;


vector<vector<int>> getNeighbours(int i, int j, vector<vector<int>> &input, const int &rows, const int &cols) {
        vector<vector<int>> neighbors; 
        
		if(i>0) {
			neighbors.push_back({i-1, j});
		}
	
		if(i<rows-1) {
			neighbors.push_back({i+1, j});
		}
	
		if(j>0) {
			neighbors.push_back({i, j-1});
		}
	
		if(j<cols-1) {
			neighbors.push_back({i, j+1});
		}
		
		return neighbors;
}

int dfs( vector<int> start, vector<vector<int>> &input, const int &rows, const int &cols) {
    int count = 0;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    stack<vector<int>> dfsStack;
    dfsStack.push(start);
    while(!dfsStack.empty()) {
        vector<int> top = dfsStack.top();
        dfsStack.pop();
        if(!visited[top[0]][top[1]]) {
            visited[top[0]][top[1]] = true;
            count++;
        }
        vector<vector<int>> neighbors = getNeighbours(top[0], top[1], input, rows, cols);
        for(auto &neighbor: neighbors) {
            if(input[neighbor[0]][neighbor[1]] > input[top[0]][top[1]] && input[neighbor[0]][neighbor[1]]!=9 && visited[neighbor[0]][neighbor[1]]==false) {
                dfsStack.push(neighbor);
            }
        }
    }
    
    return count;
}



int main()
{
    vector<vector<int>> input;
    string s;
    fstream f("./input.txt");
    while(getline(f,s)) {
        stringstream ss(s);
        vector<int> temp;
        char n;
        while(ss>>n) {
            temp.push_back(n-'0');
        }
        input.push_back(temp);
    }
    
    int rows = input.size();
    int cols = input[0].size();
    int sum =0;
    vector<vector<int>> lowPoints;
    for(int i=0 ; i<rows ; i++) {
        for(int j=0; j<cols ; j++) {
            vector<vector<int>> neighbors = getNeighbours(i,j,input, rows, cols);
            int curr = input[i][j];
            bool isALowPoint = true;
            for(auto &neighbor : neighbors) {
                if(curr>=input[neighbor[0]][neighbor[1]]) {
                    isALowPoint = false;
                    break;
                }
            }
            
            if(isALowPoint) {
                lowPoints.push_back({i,j});
                sum = sum + curr + 1;
            }
        }
    }
    
    priority_queue<int,vector<int>> maxHeap;
    
    for(auto &lowPoint : lowPoints) {
        int count = dfs(lowPoint, input, rows, cols);
        maxHeap.push(count);
    }
    
    int first = maxHeap.top();
    maxHeap.pop();
    int second = maxHeap.top();
    maxHeap.pop();
    int third = maxHeap.top();
    maxHeap.pop();
    
    cout<<"PART 1: "<<sum<<endl;
    cout<<"PART 2: "<<first*second*third<<endl;
    
    return 0;
}
