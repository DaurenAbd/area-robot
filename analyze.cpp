# include <iostream>
# include <cstdlib>
# include <cstdio>
# include <vector>

using namespace std;

struct point
{
    int x, y;
};

int square (int x)
{
    return x * x;
}

int pseudoScalarProduct (point a, point b, point c)
{
	return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

int squareDistance (point a, point b)
{
    return square (a.x - b.x) + square (a.y - b.y);
}

point make_point (int x, int y)
{
    point temp;
    temp.x = x;
    temp.y = y;
    return temp;
}

const char input[] = "input.txt";
const int INF = 2147483647;
vector < point > a;
vector < int > convexHull;
vector < bool > used;
int x, y, minY = INF, minX = INF, minI, n, previousPoint, currentPoint, psp, k;

int main ()
{
    freopen (input, "r", stdin);

    while (cin >> x >> y)
    {
        a.push_back (make_point (x, y));
        if (y < minY)
        {
            minY = y;
            minI = n;
        }
        if (y == minY && x < minX)
        {
            minX = x;
            minI = n;
        }
        ++n;
    }

    previousPoint = minI;
    used.resize (n);

    do
    {
        currentPoint = minI;
        for (int i = 0; i < n; ++i)
            if (!used[i])
            {
                psp = pseudoScalarProduct (a[previousPoint], a[currentPoint], a[i]);
                if ((psp < 0) || (psp == 0 && squareDistance (a[previousPoint], a[currentPoint]) < squareDistance (a[previousPoint], a[i])))
                    currentPoint = i;
            }
        used[currentPoint] = true;
        convexHull.push_back (currentPoint);
        ++k;
    }
    while (currentPoint != minI);
}
