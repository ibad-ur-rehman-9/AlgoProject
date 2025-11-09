#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

struct Point
{
    double x, y;
};

int main()
{
    srand(time(0));
    int n = 100; // number of points
    std::vector<Point> points;

    for (int i = 0; i < n; i++)
    {
        double x = rand() % 1000 + (rand() % 1000) / 1000.0;
        double y = rand() % 1000 + (rand() % 1000) / 1000.0;
        points.push_back({x, y});
    }

    std::ofstream outFile("points.json");
    outFile << "{\n\"points\": [\n";
    for (int i = 0; i < n; i++)
    {
        outFile << "  {\"x\": " << points[i].x << ", \"y\": " << points[i].y << "}";
        if (i != n - 1)
            outFile << ",";
        outFile << "\n";
    }
    outFile << "]\n}";
    outFile.close();

    std::cout << "JSON file created!" << std::endl;
}
