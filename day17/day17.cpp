#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll solvePart2(const int &x1, const int &x2, const int &y1, const int &y2)
{
    ll total = 0;
    for (int i = 0; i <= x2; i++)
    {

        for (int j = y1; j < 0; j++)
        {
            int vx = i;
            int vy = j;
            int initVx = vx;
            int initVy = vy;
            int x = 0;
            int y = 0;
            bool flagI = true;
            while (flagI)
            {
                x += vx;
                y += vy;
                if (vx > 0)
                {
                    vx -= 1;
                }
                vy -= 1;
                if ((x1 <= x && x <= x2) && (y1 <= y && y <= y2))
                {
                    total++;
                    flagI = false;
                }
                else if (y < y1 || x > x2)
                {
                    flagI = false;
                }
            }
        }

        for (int j = -y1; j >= 0; j--)
        {
            int vx = i;
            int vy = j;
            int initVx = vx;
            int initVy = vy;
            int x = 0;
            int y = 0;
            bool flagI = true;
            while (flagI)
            {
                x += vx;
                y += vy;
                if (vx > 0)
                {
                    vx -= 1;
                }
                vy -= 1;
                if ((x1 <= x && x <= x2) && (y1 <= y && y <= y2))
                {
                    total++;
                    flagI = false;
                }
                else if (y < y1 || x > x2)
                {
                    flagI = false;
                }
            }
        }
    }

    return total;
}

int main()
{

    fstream f("./input.txt");
    string s;
    getline(f, s);
    stringstream ss(s);
    int x1, x2, y1, y2;

    ss >> x1;
    ss >> x2;
    ss >> y1;
    ss >> y2;

    if (y1 < 0)
    {
        cout << "PART 1: " << ((y1) * (y1 + 1)) / 2;
    }
    else
    {
        cout << "PART 1: " << ((y1) * (y1 - 1)) / 2;
    }

    ll result = solvePart2(x1, x2, y1, y2);

    cout << "PART 2: " << result << endl;
}