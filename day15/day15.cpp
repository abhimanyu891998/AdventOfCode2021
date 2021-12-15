#include<bits/stdc++.h>

using namespace std;


struct Node {
    long long i;
    long long j;
    Node(long long i, long long j):i(i),j(j){

    }
};

void parseInput(string& s, vector<vector<long long>> &input) {
    stringstream ss(s);
    char c;
    vector<long long> temp;
    while(ss>>c) {
        temp.push_back(c-'0');
    }

    input.push_back(temp);
}

//Generates neighbours based on ranges
vector<vector<long long>> getNeighbours(long long rows, long long cols, long long i, long long j) {
    vector<vector<long long>> elems;

    if(i>0) {
        elems.push_back({i-1, j});
    }

    if(j>0) {
        elems.push_back({i,j-1});
    }

    if(i<rows-1) {
        elems.push_back({i+1, j});
    }

    if(j<cols-1) {
        elems.push_back({i, j+1});
    }

    return elems;
}

struct comparator {
    bool operator()(pair<long long,Node> &a, pair<long long,Node> &b) {
        return a.first > b.first;
    }
};


//Basic djikstra
void djikstra(vector<vector<long long>> &graph, vector<vector<long long>> &nodeVals, const long long &r, const long long &c) {
    priority_queue<pair<long long,Node>, vector<pair<long long,Node>>, comparator> pq;
    pq.push(make_pair(0, Node(0,0)));
    while(!pq.empty()) {
        pair<long long,Node> nodeBeingVisited = pq.top();
        pq.pop();
        Node currentNode = nodeBeingVisited.second;
        long long currentNodeVal = nodeBeingVisited.first;
        vector<vector<long long>> neighbors = getNeighbours(r,c, currentNode.i, currentNode.j);
        for(auto &neighbor : neighbors) {
            long long i = neighbor[0];
            long long j = neighbor[1];
            if(((currentNodeVal + graph[i][j]) < nodeVals[i][j])) {
                nodeVals[i][j] = currentNodeVal + graph[i][j];
                pq.push({nodeVals[i][j], Node(i,j)});
            }
        }
    }
    return;
}

//To extrapolate the new graph for part 2
void generateNewGraph(vector<vector<long long>> &graph, vector<vector<long long>> &newGraph,const int &r,const int &c, const int &nr, const int &nc) {
    for(int i=0 ; i<r; i++) {
        for(int j=0; j<c; j++) {
            newGraph[i][j] = graph[i][j];
        }
    }

    for(int i=0 ; i<nr-r ; i++) {
        for(int j=0; j<nc-c; j++) {
            int newR = i+r;
            int newC = j+c;
            if(newGraph[i][j]+1 >= 10) {
                newGraph[i][newC] = 1;
                newGraph[newR][j] = 1;
            }
            else {
                newGraph[i][newC] = newGraph[i][j]+1;
                newGraph[newR][j] = newGraph[i][j]+1;
            }
        }
    }

    for(int i=nr-r; i<nr; i++) {
        for(int j=nc-(2*c); j<nc-c; j++) {
            int newC = j+c;
            if(newGraph[i][j]+1>9) {
                newGraph[i][newC] = 1;
            }
            else {
                newGraph[i][newC] = newGraph[i][j]+1;
            }
        }
    }

    return;
}


int main() {

    fstream f("./input.txt");
    string s;
    vector<vector<long long>> graph;
    
    while(getline(f,s)) {
        parseInput(s, graph);
    }

    long long rows = graph.size();
    long long cols = graph[0].size();

    vector<vector<long long>> nodeVals(rows, vector<long long>(cols, LLONG_MAX));

    nodeVals[0][0] = 0;

    djikstra(graph,nodeVals, rows, cols);
    
    cout<<"PART 1: "<<nodeVals[rows-1][cols-1]<<endl;

    long long nrows = rows*5;
    long long ncols = cols*5;

    vector<vector<long long>> newGraph(nrows, vector<long long>(ncols, 0));

    generateNewGraph(graph, newGraph, rows, cols, nrows, ncols);

    vector<vector<long long>> newNodeVals(nrows, vector<long long>(ncols, LLONG_MAX));

    djikstra(newGraph, newNodeVals, nrows, ncols);

    cout<<"PART 2: "<<newNodeVals[nrows-1][ncols-1]<<endl;

    return 0;

}