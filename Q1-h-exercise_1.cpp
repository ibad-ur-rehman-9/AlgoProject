#include <bits/stdc++.h>
using namespace std;

double findMedian(vector<int>& a, vector<int>& b) {
    int n = a.size();
    if (n == 0) return -1;
    if (a[0] > b[0]) swap(a, b);

    int low = 0, high = n;
    while (low <= high) {
        int cutA = (low + high) / 2;
        int cutB = n - cutA;

        int leftA = (cutA == 0) ? INT_MIN : a[cutA - 1];
        int leftB = (cutB == 0) ? INT_MIN : b[cutB - 1];
        int rightA = (cutA == n) ? INT_MAX : a[cutA];
        int rightB = (cutB == n) ? INT_MAX : b[cutB];

        if (leftA <= rightB && leftB <= rightA)
            return max(leftA, leftB);
        else if (leftA > rightB)
            high = cutA - 1;
        else
            low = cutA + 1;
    }
    return -1;
}

int main() {
    vector<int> dbA = {1, 5, 8, 10, 13, 17, 21, 25, 29, 33};
    vector<int> dbB = {2, 4, 6, 12, 15, 18, 22, 26, 30, 34};
    cout << findMedian(dbA, dbB);
}
