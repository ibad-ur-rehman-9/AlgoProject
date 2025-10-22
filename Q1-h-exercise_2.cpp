#include <bits/stdc++.h>
using namespace std;

long long mergeCount(vector<int>& arr, int left, int mid, int right) {
    long long count = 0;
    int j = mid + 1;
    for (int i = left; i <= mid; i++) {
        while (j <= right && (long long)arr[i] > 2LL * arr[j]) j++;
        count += j - (mid + 1);
    }
    
    vector<int> temp;
    int i = left;
    j = mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);
    for (int k = left; k <= right; k++) arr[k] = temp[k - left];
    return count;
}

long long countSignificantInversions(vector<int>& arr, int left, int right) {
    if (left >= right) return 0;
    int mid = (left + right) / 2;
    long long count = countSignificantInversions(arr, left, mid);
    count += countSignificantInversions(arr, mid + 1, right);
    count += mergeCount(arr, left, mid, right);
    return count;
}

int main() {
    vector<int> arr = {10, 3, 7, 2, 9, 5, 11, 4, 1, 6};
    cout << "significant inversions: " << countSignificantInversions(arr, 0, arr.size() - 1);
}
