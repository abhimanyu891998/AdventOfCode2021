#include <iostream>

using namespace std;

void firstWayToSteer(const string &instruction, int &val, int &x, int &y) {
    
    if(instruction == "forward")
        x+= val;
        
    else if(instruction == "down")
        y+=val;
        
    else if(instruction == "up")
        y-=val;
        
    return;
}

void secondWayToSteer(const string &instruction, int &val, int &x, int &y, int &aim) {
    
    if(instruction == "forward") {
        x+= val;
        y+= aim*val;
    }

    else if(instruction == "down")
        aim+=val;
        
    else if(instruction == "up")
        aim-=val;
    
    return;
}

int main()
{
    int firstx = 0;
    int firsty = 0;
    int aim = 0;
    int secondX = 0;
    int secondY = 0;
    string instruction;
    int val;
    
    while(cin>>instruction>>val) {
       firstWayToSteer(instruction, val, firstx, firsty); 
       secondWayToSteer(instruction, val, secondX, secondY, aim);
    }
    
    cout<<firsty*firstx<<endl;
    cout<<secondY*secondX<<endl;

    return 0;
}
