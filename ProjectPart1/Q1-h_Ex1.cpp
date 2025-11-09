#include <iostream>
#include <vector>
#include <climits>

using namespace std;

double findMedian(vector<int> &a, vector<int> &b)
{
    int n = a.size();
    if (n == 0)
        return -1;
    if (a[0] > b[0])
    {
        vector<int> temp = a;
        a = b;
        b = temp;
    }
    int low = 0, high = n;
    while (low <= high)
    {
        int cutA = (low + high) / 2;
        int cutB = n - cutA;
        int leftA = (cutA == 0) ? INT_MIN : a[cutA - 1];
        int leftB = (cutB == 0) ? INT_MIN : b[cutB - 1];
        int rightA = (cutA == n) ? INT_MAX : a[cutA];
        int rightB = (cutB == n) ? INT_MAX : b[cutB];
        if (leftA <= rightB && leftB <= rightA)
        {
            int maxLeft = (leftA > leftB) ? leftA : leftB;
            return maxLeft;
        }
        else if (leftA > rightB)
            high = cutA - 1;
        else
            low = cutA + 1;
    }
    return -1;
}

int main()
{
    cout << endl
         << " __  __         __   __    ___  ||   __  __         __  ___ ___ __   ||   __  __         __   __   __    " << endl
         << "  _)  _)|  __  /  \\ |_  /|   /  ||    _)  _)|  __  /  \\   /   /  _)  ||    _)  _)|  __  /  \\ /__  (__) /|" << endl
         << " /__ __)|(     \\__/ __) _|_ /   ||   /__ __)|(     \\__/  /   /  /__  ||   /__ __)|(     \\__/ \\__) (__) _|_" << endl
         << endl;

    vector<int> dbA;
    cout << " Enter atleast 10 elements for Database A, press '-1' for end of array: " << endl;
    for (int i = 0;; i++)
    {
        int input;
        cin >> input;
        if (i > 9 && input == -1)
        {
            break;
        }
        else if (input == -1)
        {
            continue;
        }
        dbA.push_back(input);
    }

    vector<int> dbB;
    cout << " Enter atleast 10 elements for Database B, press '-1' for end of array: " << endl;
    for (int i = 0;; i++)
    {
        int input;
        cin >> input;
        if (i > 9 && input == -1)
        {
            break;
        }
        else if (input == -1)
        {
            continue;
        }
        dbB.push_back(input);
    }

    cout << "Database A: " << endl;
    for (auto i : dbA)
    {
        cout << i << "  ";
    }
    cout << endl;

    cout << "Database B: " << endl;
    for (auto i : dbB)
    {
        cout << i << "  ";
    }
    cout << endl;

    double median = findMedian(dbA, dbB);
    if (median != -1)
    {
        cout << "Median of combined databases: " << median << endl;
    }
    else
    {
        cout << "Error: Could not find median." << endl;
    }
}
