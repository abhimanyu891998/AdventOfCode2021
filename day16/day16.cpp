#include <bits/stdc++.h>

using namespace std;

typedef int64_t ll;

unordered_map<char, string> hexToBin = {
    {'0', "0000"},
    {'1', "0001"},
    {'2', "0010"},
    {'3', "0011"},
    {'4', "0100"},
    {'5', "0101"},
    {'6', "0110"},
    {'7', "0111"},
    {'8', "1000"},
    {'9', "1001"},
    {'A', "1010"},
    {'B', "1011"},
    {'C', "1100"},
    {'D', "1101"},
    {'E', "1110"},
    {'F', "1111"}};

pair<ll, ll> processLiteral(const string s, ll &v);

pair<ll, vector<ll>> processOperator(const string s, ll &v, vector<ll> &values);

string converToBinary(const string &hexInput)
{
    stringstream ss(hexInput);
    char c;
    string binary;
    while (ss >> c)
    {
        binary += hexToBin[c];
    }

    return binary;
}

//Starting point
pair<ll, ll> processHeader(const string binary, ll &versionCount)
{

    if (binary.size() < 6)
    {
        return make_pair(0, 0);
    }

    string version = binary.substr(0, 3);
    versionCount += stoi(version, nullptr, 2);
    string sTypeID = binary.substr(3, 3);
    int type = stoi(sTypeID, nullptr, 2);
    pair<ll, ll> res;
    if (type == 4)
    {
        res = processLiteral(binary, versionCount);
    }
    else
    {
        vector<ll> values;
        pair<ll, vector<ll>> operatorResult;
        operatorResult = processOperator(binary, versionCount, values);
        ll value = 0;
        if (type == 0)
        {
            value = accumulate(values.begin(), values.end(), value);
        }
        else if (type == 1)
        {
            value = 1;
            for (auto val : values)
                value *= val;
        }
        else if (type == 2)
        {
            value = std::numeric_limits<ll>::max();
            for (auto val : values)
                value = std::min(val, value);
        }
        else if (type == 3)
        {
            value = std::numeric_limits<ll>::min();
            for (auto val : values)
                value = std::max(val, value);
        }

        else if (type == 5)
            value = (values[0] > values[1]);

        else if (type == 6)
            value = (values[0] < values[1]);

        else if (type == 7)
            value = (values[0] == values[1]);

        res = make_pair(operatorResult.first, value);
    }

    return res;
}

//Processes operator
pair<ll, vector<ll>> processOperator(const string binary, ll &versionCount, vector<ll> &values)
{
    string lengthTypeID = binary.substr(6, 1);
    if (lengthTypeID == "0")
    {
        string sTotalBitsLen = binary.substr(7, 15);
        ll totalBitsLen = stoi(sTotalBitsLen, nullptr, 2);
        ll lengthUsed = 0;
        while (lengthUsed < totalBitsLen)
        {
            auto res = processHeader(binary.substr(22 + lengthUsed, totalBitsLen - lengthUsed), versionCount);
            lengthUsed += res.first;
            values.push_back(res.second);
        }
        totalBitsLen += 22;
        return make_pair(totalBitsLen, values);
    }

    else if (lengthTypeID == "1")
    {
        string sNumPackets = binary.substr(7, 11);
        ll numPackets = stoi(sNumPackets, nullptr, 2);
        ll lengthUsed = 0;
        for (ll packet = 0; packet < numPackets; packet++)
        {
            string temp = binary.substr(18 + lengthUsed);
            auto res = processHeader(binary.substr(18 + lengthUsed), versionCount);
            lengthUsed += res.first;
            values.push_back(res.second);
        }
        lengthUsed += 18;
        return make_pair(lengthUsed, values);
    }
}

//Processes literals with a final value
pair<ll, ll> processLiteral(const string binary, ll &versionCount)
{

    ll finalVal = 0;
    ll ctr = 0;
    auto group = binary.substr(6, 5);
    auto value = binary.substr(7, 4);

    while (group[0] != '0')
    {
        ctr++;
        value += binary.substr(7 + ctr * 5, 4);
        group = binary.substr(6 + ctr * 5, 5);
    }
    ll literalVal = stoll(value, nullptr, 2);
    return make_pair(11 + ctr * 5, literalVal);
}

int main()
{

    string hexInput;
    fstream f("./input.txt");
    getline(f, hexInput);

    string binary = converToBinary(hexInput);

    ll versionCount = 0;

    auto res = processHeader(binary, versionCount);

    cout << "PART 1: " << versionCount << endl;
    cout << "PART 2: " << res.second << endl;

    return 0;
}
