#include<bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    string filename = argv[1];
    filename = "./" + filename + ".txt";
    fstream f(filename);
    vector<string> grid;
    string s;

    while(getline(f,s)) {
        grid.push_back(s);
    }

    int r = int(grid.size());
    int c = int(grid[0].size());


    auto step = [&]() -> bool {
        
        vector<string> original = grid;
        vector<string> newGrid = grid;
        
        for(int i=0; i<r; i++) {
            for(int j=0 ; j<c ; j++) {
                if(grid[i][j] == '>') {
                    int nj = (j+1)%c;
                    if(grid[i][nj] == '.') {
                        newGrid[i][nj] = '>';
                        newGrid[i][j] = '.';
                    }
                }
            }    
        }

        grid = newGrid;
        newGrid = grid;

        for(int i=0 ; i<r ; i++) {
            for(int j=0 ; j<c; j++) {
                if(grid[i][j] == 'v') {
                    int nr = (i+1)%r;
                    if(grid[nr][j] == '.') {
                        newGrid[nr][j] = 'v';
                        newGrid[i][j] = '.';
                    }
                }
            }
        }

        grid = newGrid;

        return grid!=original;
        
    };


    int steps = 0;

    while(step()) {
        steps++;
    }

    cout<<steps+1<<endl;

    return 0;
}
