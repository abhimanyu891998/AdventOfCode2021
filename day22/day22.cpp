#include<bits/stdc++.h>

using namespace std;

struct step {
    int x0;
    int x1;
    int y0;
    int y1;
    int z0;
    int z1;
    bool type;
};


int64_t solvePart2(vector<step> &steps){
    vector<int> X, Y,Z;
    for(auto &step : steps) {
        X.push_back(step.x0);
        step.x1++;
        X.push_back(step.x1);
        Y.push_back(step.y0);
        step.y1++;
        Y.push_back(step.y1);
        Z.push_back(step.z0);
        step.z1++;
        Z.push_back(step.z1);
    }

    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    sort(Z.begin(), Z.end());
    int gridSize = int(X.size());

    auto getIndex = [&](vector<int> &C, int c) -> int {
        return int(lower_bound(C.begin(), C.end(),c) - C.begin());
    };

    vector<vector<vector<bool>>> grid(gridSize, vector<vector<bool>>(gridSize, vector<bool>(gridSize, false)));

    for(auto &s: steps) {
        int x0 = getIndex(X, s.x0);
        int x1 = getIndex(X, s.x1);
        int y0 = getIndex(Y, s.y0);
        int y1 = getIndex(Y,s.y1);
        int z0 = getIndex(Z, s.z0);
        int z1 = getIndex(Z, s.z1);

        for(int i=x0; i<x1 ; i++) {
            for(int j=y0 ; j<y1 ; j++) {
                for(int k=z0 ; k<z1 ; k++) {
                    grid[i][j][k] = s.type;
                }
            }
        }
    }

    int64_t sum = 0;
    int N = gridSize;

    for(int i=0; i< N-1 ; i++) {
        for(int j=0 ; j<N-1; j++) {
            for(int k=0 ; k< N-1 ; k++) {
                sum+= int64_t(grid[i][j][k]) * (X[i+1] - X[i]) * (Y[j+1] - Y[j]) * (Z[k+1] - Z[k]);
            }
        }
    }

    return sum;

}

int main() {
    fstream f("./input.txt");
    string type;
    int N = 50;
    bool A[2*N+1][2*N+1][2*N+1];

    for(int i=0 ; i<=100; i++) {
        for(int j=0; j<=100; j++) {
            for(int k=0 ; k<=100 ; k++) {
                A[i][j][k] = 0;
            }
        }
    }  

    int64_t sum = 0;
    vector<step> steps;
    while(f>>type) {
        bool value = type=="on";
        int x0,x1,y0,y1,z0,z1; 
        f>>x0>>x1>>y0>>y1>>z0>>z1;
        steps.emplace_back();
        step &s = steps.back();
        s.x0 = x0;
        s.x1 = x1; 
        s.y0 = y0;
        s.y1 = y1; 
        s.z0 = z0;
        s.z1 = z1; 
        s.type = value;

        x0 = max(x0, -N);
        x1 = min(x1, N);
        y0 = max(y0, -N);
        y1 = min(y1, N);
        z0 = max(-N, z0);
        z1 = min(z1, N);

        for(int i=x0 ; i<=x1; i++) {
            for(int j=y0; j<=y1; j++) {
                for(int k=z0 ; k<=z1 ; k++) {
                    A[i+N][j+N][k+N] = value;
                }
            }
        }     
    }

    for(int i=0 ; i<=100; i++) {
    for(int j=0; j<=100; j++) {
        for(int k=0 ; k<=100 ; k++) {
            sum+=A[i][j][k];
        }
     }
    }  

    cout<<"PART 1 "<<sum<<endl;

    cout<<"PART 2 "<<solvePart2(steps)<<endl;


    return 0;
}