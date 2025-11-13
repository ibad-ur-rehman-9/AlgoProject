#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <cmath>

#define M_PI 3.14159265358979323846

struct Point
{
    double x, y;
};

void generateFile(std::string filename, int n, int pattern)
{
    std::vector<Point> points;

    switch (pattern)
    {
    case 1: // Random uniform distribution
        for (int i = 0; i < n; i++)
        {
            double x = rand() % 1000 + (rand() % 1000) / 1000.0;
            double y = rand() % 1000 + (rand() % 1000) / 1000.0;
            points.push_back({x, y});
        }
        break;

    case 2: // Clustered points (3-4 clusters)
        for (int i = 0; i < n; i++)
        {
            int cluster = rand() % 4;
            double centerX = (cluster % 2) * 500 + 250;
            double centerY = (cluster / 2) * 500 + 250;
            double x = centerX + (rand() % 200 - 100);
            double y = centerY + (rand() % 200 - 100);
            points.push_back({x, y});
        }
        break;

    case 3: // Points on a line (worst case for some algorithms)
        for (int i = 0; i < n; i++)
        {
            double x = i * (1000.0 / n);
            double y = x + (rand() % 50 - 25); // slight variation
            points.push_back({x, y});
        }
        break;

    case 4: // Circular distribution
        for (int i = 0; i < n; i++)
        {
            double angle = (i * 2 * M_PI) / n;
            double radius = 400 + (rand() % 100);
            double x = 500 + radius * cos(angle);
            double y = 500 + radius * sin(angle);
            points.push_back({x, y});
        }
        break;

    case 5: // Grid-like pattern
    {
        int gridSize = sqrt(n);
        for (int i = 0; i < n; i++)
        {
            double x = (i % gridSize) * (1000.0 / gridSize) + (rand() % 20);
            double y = (i / gridSize) * (1000.0 / gridSize) + (rand() % 20);
            points.push_back({x, y});
        }
    }
    break;

    case 6: // Dense center, sparse edges
        for (int i = 0; i < n; i++)
        {
            double r = pow(rand() / (double)RAND_MAX, 2) * 500;
            double angle = (rand() / (double)RAND_MAX) * 2 * M_PI;
            double x = 500 + r * cos(angle);
            double y = 500 + r * sin(angle);
            points.push_back({x, y});
        }
        break;

    case 7: // Two very close clusters (challenging)
        for (int i = 0; i < n; i++)
        {
            int cluster = i % 2;
            double centerX = 450 + cluster * 100;
            double centerY = 500;
            double x = centerX + (rand() % 80 - 40);
            double y = centerY + (rand() % 400 - 200);
            points.push_back({x, y});
        }
        break;

    case 8: // Diagonal stripe pattern
        for (int i = 0; i < n; i++)
        {
            double x = rand() % 1000;
            double y = x + (rand() % 100 - 50);
            if (y > 1000)
                y = 1000;
            if (y < 0)
                y = 0;
            points.push_back({x, y});
        }
        break;

    case 9: // Corners (points concentrated at corners)
        for (int i = 0; i < n; i++)
        {
            int corner = i % 4;
            double x = (corner % 2) * 900 + (rand() % 100);
            double y = (corner / 2) * 900 + (rand() % 100);
            points.push_back({x, y});
        }
        break;

    case 10: // Mixed: random with some very close pairs
        for (int i = 0; i < n; i++)
        {
            if (i % 10 == 0 && i > 0)
            {
                // Make this point very close to previous
                Point prev = points[points.size() - 1];
                double x = prev.x + (rand() % 5);
                double y = prev.y + (rand() % 5);
                points.push_back({x, y});
            }
            else
            {
                double x = rand() % 1000 + (rand() % 1000) / 1000.0;
                double y = rand() % 1000 + (rand() % 1000) / 1000.0;
                points.push_back({x, y});
            }
        }
        break;
    }

    std::ofstream outFile(filename);
    outFile << "{\n  \"points\": [\n";
    for (int i = 0; i < points.size(); i++)
    {
        outFile << "    {\"x\": " << points[i].x << ", \"y\": " << points[i].y << "}";
        if (i != points.size() - 1)
            outFile << ",";
        outFile << "\n";
    }
    outFile << "  ]\n}";
    outFile.close();
}

int main()
{
    srand(time(0));

    std::string descriptions[] = {
        "Random Uniform (100 points)",
        "Clustered (110 points)",
        "Linear Pattern (120 points)",
        "Circular (100 points)",
        "Grid Pattern (121 points)",
        "Dense Center (130 points)",
        "Two Close Clusters (140 points)",
        "Diagonal Stripe (150 points)",
        "Corner Clusters (100 points)",
        "Mixed with Close Pairs (160 points)"};

    int sizes[] = {100, 110, 120, 100, 121, 130, 140, 150, 100, 160};

    for (int i = 1; i <= 10; i++)
    {
        std::string filename = "points" + std::to_string(i) + ".json";
        generateFile(filename, sizes[i - 1], i);
        std::cout << "Generated " << filename << " - " << descriptions[i - 1] << std::endl;
    }

    std::cout << "\nAll 10 JSON files created successfully!" << std::endl;
    return 0;
}