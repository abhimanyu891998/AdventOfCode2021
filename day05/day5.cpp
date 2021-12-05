#include<iostream>
#include<fstream>
#include<bits/stdc++.h>

using namespace std;

//Choose between 1 or 2 to execute that part of the code
#define PART 2

struct Point{
    int x;
    int y;

    Point(const int x, const int y):x(x), y(y) {}

    bool operator == (const Point &p) const {
        return x==p.x && y==p.y;
    }

    bool operator != (const Point &p) const {
        return x!=p.x || y!=p.y;
    }

    Point operator + (const Point &p) const {
        return Point(x+p.x , y+p.y); 
    }

    friend ostream& operator <<(ostream &os , const Point &p);

};

ostream& operator <<(ostream &os, Point & p) {
    os<< "["<<p.x<<","<<p.y<<"]";
    return os;


}

struct PointHashFunction {
    size_t operator()(const Point &a) const {
        return a.x ^ a.y;
    }
};


pair<Point,Point> convertStringToPoint(string line){
    stringstream ss;

    ss<<line;
    int x1, y1;
    ss>>x1;
    ss>>y1;

    Point a(x1,y1);
    int x2,y2;
    ss>>x2;
    ss>>y2;
    Point b(x2,y2);

    return {a,b};
}


int main() {

    string inputFile = "./input.txt";
    fstream fileContent(inputFile);
    string line;
    int output = 0;

    unordered_map<Point, int, PointHashFunction> visitedFreq;

    while(getline(fileContent, line)) {
        auto [start, end] = convertStringToPoint(line);
        
        #if PART==1
        if(!((start.x == end.x) || (start.y == end.y)))
            continue;
        #endif

        auto delta = Point(0,0);

        if(start.x == end.x) {
            delta.y = abs(start.y - end.y) / (start.y-end.y);
        }
        else if(start.y == end.y){
            delta.x = abs(start.x - end.x) / (start.x - end.x);
        } 

        #if PART==2
        else {
            delta.x = abs(start.x - end.x) / (start.x - end.x);
            delta.y = abs(start.y - end.y) / (start.y-end.y);
        }
        #endif

        auto traverse = end;

        while(traverse != start) {
            if(visitedFreq.find(traverse) == visitedFreq.end())
                visitedFreq[traverse] = 0;
            visitedFreq[traverse]++;
            traverse = traverse + delta;
        }

        if(visitedFreq.find(traverse) == visitedFreq.end()) {
            visitedFreq[traverse] = 0;
        }
        visitedFreq[traverse]++;
    }

    for(const auto &[point, count] : visitedFreq) {
        if(count>1) {
            output++;
        }
    }

    cout<<"PART "<<PART<<" "<<output<<endl;

    return 0;

}
