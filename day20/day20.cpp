#include<bits/stdc++.h>
#include "../utils/utils.h"

using namespace std;

typedef int64_t ll;

template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct hasher
{
inline size_t operator()(const v2 & v) const
{
    size_t seed = 0;
    ::hash_combine(seed, v.x);
    ::hash_combine(seed, v.y);
    return seed;
}
};

ll solve(const vector<string> &input, const string &algo, const int &iterations) {

    unordered_map<v2, int8_t, hasher> imageMap;
    v2 pos(0,0);

    for(size_t i=0; i<input.size(); i++) {
        for(size_t j=0; j<input[0].length() ;  j++) {
            pos.x = j;
            pos.y = i;
            imageMap[pos] = input[i][j];
        }
    }



    vector<v2> neighbours; 

    neighbours.emplace_back(-1, -1);
    neighbours.emplace_back(0, -1);
    neighbours.emplace_back(1, -1);

    neighbours.emplace_back(-1, 0);
    neighbours.emplace_back(0, 0);
    neighbours.emplace_back(1, 0);

    neighbours.emplace_back(-1, 1);
    neighbours.emplace_back(0, 1);
    neighbours.emplace_back(1, 1);

    unordered_map<v2, int8_t, hasher> changedImageMap;

    for(int i=0 ; i<iterations; i++) {
        int leastX = 0;
        int maxX = 0;
        int leastY = 0;
        int maxY = 0;

        for(auto [pos, val]: imageMap) {
            maxX = max(maxX, pos.x);
            maxY = max(maxY, pos.y);

            leastX = min(leastX, pos.x);
            leastY = min(leastY, pos.y);
        }

        for(int y = leastY-2 ; y<=maxY+2 ; y++) {
            for(int x=leastX-2 ; x<=maxX+2; x++) {
                v2 pos(x,y);
                int16_t newVal = 0;
                
                for(auto n: neighbours) {
                    newVal*=2;
                    if(imageMap.find(pos+n) != imageMap.end()) {
                        newVal+= (imageMap[pos+n] == '#');
                    }
                    else {
                        newVal+= (i%2);
                    }
                }
                changedImageMap[pos] = algo[newVal];
            }
        }
        swap(changedImageMap, imageMap);
        changedImageMap.clear();
    }

    ll sum = 0;

    for(auto [pos, val]: imageMap) {
        if(val=='#')
            // cout<<pos.x<<" "<<pos.y<<endl;
            sum+=1;
    }


    return sum;

}

int main() {

    vector<string> input;

    fstream f("./input.txt");

    string algo;
    string temp;
    getline(f,algo);
    getline(f,temp);
    while(getline(f,temp)) {
        input.push_back(temp);
    }

    cout<<"PART 1: "<<solve(input, algo, 2)<<endl;
    cout<<"PART 2: "<<solve(input, algo, 50);

    
    
}
