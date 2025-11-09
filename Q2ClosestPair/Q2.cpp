#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

struct Point
{
    double x, y;
};
double distance(Point a, Point b)
{
    double firstPart = (b.x - a.x)*(b.x - a.x);
    double secondPart = (b.y - a.y) * (b.y - a.y);
    double answer = sqrt(firstPart + secondPart);
    return answer;
}
double DC(vector<Point> &points)
{
    // base case
    if (points.size() <= 3)
    {
        double minDist = 1e9;
        for (int i = 0; i < points.size(); i++)
            for (int j = i + 1; j < points.size(); j++)
                minDist = min(minDist, distance(points[i], points[j]));
        return minDist;
    }

    // sort by x
    

    // find mid, left array and right array
    int mid = points.size() / 2;
    Point midPoint = points[mid];

    vector<Point> left(points.begin(), points.begin() + mid);
    vector<Point> right(points.begin() + mid, points.end());

    // recursively smallest point
    double dl = DC(left);
    double dr = DC(right);
    double d = min(dl, dr);

    // build strip, fabs = floating absolute
    vector<Point> strip;
    for (auto &p : points)
        if (fabs(p.x - midPoint.x) < d)
            strip.push_back(p);

    // sort strip by y, because x is already constrained, like all points already smaller than d(min yet) in terms of x
    sort(strip.begin(), strip.end(), [](const Point &a, const Point &b)
         { return a.y < b.y; });

    // check limited neighbors in strip, check as long y within the strip aswell
    for (int i = 0; i < strip.size(); i++)
    {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; j++)
        {
            d = min(d, distance(strip[i], strip[j]));
        }
    }

    return d;
}

int main()
{
    ifstream inFile("closest1.txt"); 
    if (!inFile)
    { // check if file opened successfully
        cerr << "Error opening file!" << endl;
        return 1;
    }
    vector<Point> points;
    double x, y;

    while (inFile >> x >> y)
    { 
        points.push_back({x, y});
    }

    inFile.close(); // always close the file when done

    for (auto &p : points)
    {
        cout << p.x << " " << p.y << "\n";
    }
    sort(points.begin(), points.end(), [](const Point &a, const Point &b)
         { return a.x < b.x; });
    double closest = DC(points);

    cout << "closest: " << closest << endl;


}
