#include <iostream>
#include<vector>
#include<sstream>

using namespace std;

pair<char,char> getMostLeast(vector<string> &matrix, int j) {
    int zcount = 0;
    int ocount = 0;
    for(int i= 0 ; i<matrix.size() ; i++) {
        if(matrix[i][j] == '0')
            zcount++;
        else
            ocount++;
    }
    
    if(zcount>ocount)
        return make_pair('0', '1');
        
    else
        return make_pair('1', '0');
}

int main()
{
    vector<string> binaryMatrix;
    string binary;
    string mostSig;
    string leastSig;

    while(cin>>binary){
        binaryMatrix.push_back(binary);
    }
    
    vector<string> mMatrix = binaryMatrix;
    vector<string> lMatrix = binaryMatrix;
    bool mGot = false;
    bool lGot = false;
    
    for(int i=0 ; i<binaryMatrix[0].length(); i++) {
        int zcount = 0;
        int ocount = 0;
        for(int j=0; j<binaryMatrix.size(); j++) {
            if(binaryMatrix[j][i] == '0')
                zcount++;
            else
                ocount++;
        }
        if(zcount>ocount) {
            mostSig.push_back('0');
            leastSig.push_back('1');
        } else {
            mostSig.push_back('1');
            leastSig.push_back('0');           
        }
        
        if(!mGot) {
            vector<string> tempMMatrix = {};
            pair<char,char> mval = getMostLeast(mMatrix, i);
            for(int k=0; k<mMatrix.size(); k++) {
                if(mMatrix[k][i]==mval.first) {
                    tempMMatrix.push_back(mMatrix[k]);
                }
            }
            mMatrix = tempMMatrix;
            if(mMatrix.size()==1)
                mGot = true;
        }
        
        if(!lGot) {
            vector<string> tempLMatrix = {};
            pair<char,char> lval = getMostLeast(lMatrix, i);
            for(int k=0; k<lMatrix.size(); k++) {
                if(lMatrix[k][i]==lval.second) {
                    tempLMatrix.push_back(lMatrix[k]);
                }
            }
            lMatrix = tempLMatrix;
            if(lMatrix.size()==1)
                lGot = true;
        }
    }
    
    
    int mostSigInBinary = stoi(mostSig, 0, 2);
    int leastSigInBinary = stoi(leastSig, 0, 2);
    
    int co2Rating = stoi(lMatrix[0], 0, 2);
    int o2Rating = stoi(mMatrix[0], 0 ,2);
    
    cout<<co2Rating*o2Rating<<endl;
    
    //cout<<mostSigInBinary*leastSigInBinary<<endl;
    return 0;
}
