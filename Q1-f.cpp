#include <iostream>
#include <vector>
using namespace std;

int findPeakRecursive(vector<int>& arr, int l, int r) {
    int mid = l + (r - l) / 2;

    if (l == r)
        return l;

    if (arr[mid] > arr[mid + 1])
        return findPeakRecursive(arr, l, mid);
    else
        return findPeakRecursive(arr, mid + 1, r);
}

int main() {
    vector<int> arr = {2, 3, 4, 5, 6, 7, 6, 4, 3, 0};
    int n = arr.size();
    int p = findPeakRecursive(arr, 0, n - 1);
    cout << "peak element: " << arr[p] << endl;
}
