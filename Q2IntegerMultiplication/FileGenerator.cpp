#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());

    // Different distributions/types for 10 files
    vector<pair<int, int>> ranges = {
        {1, 9},       // Small 1-digit numbers
        {10, 99},     // 2-digit numbers
        {100, 999},   // 3-digit numbers
        {1000, 9999}, // 4-digit numbers
        {1, 9999},    // Mixed small & large within 4 digits
        {5000, 9999}, // Medium-range numbers limited to 4 digits
        {1234, 6789}, // Custom range within 4 digits
        {0, 9999}     // Large numbers capped at 4 digits
    };

    for (int fileIdx = 0; fileIdx < 10; ++fileIdx) {
        ofstream out("input_" + to_string(fileIdx+1) + ".json");
        if (!out) {
            cerr << "Error opening file\n";
            return 1;
        }

        uniform_int_distribution<> dist(ranges[fileIdx].first, ranges[fileIdx].second);

        out << "[\n";
        for (int i = 0; i < 100; ++i) {
            int a = dist(gen);
            int b = dist(gen);
            out << "  {\"a\": " << a << ", \"b\": " << b << "}";
            if (i != 99) out << ",";
            out << "\n";
        }
        out << "]";
        out.close();
    }

    cout << "10 JSON files generated successfully.\n";
    return 0;
}
