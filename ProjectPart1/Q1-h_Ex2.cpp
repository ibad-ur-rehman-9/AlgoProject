#include <iostream>
#include <vector>

using namespace std;

long long mergeCount(vector<int> &arr, int left, int mid, int right)
{
    long long count = 0;
    int j = mid + 1;
    for (int i = left; i <= mid; i++)
    {
        while (j <= right && (long long)arr[i] > 2LL * arr[j])
            j++;
        count += j - (mid + 1);
    }

    vector<int> temp;
    int i = left;
    j = mid + 1;
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= mid)
        temp.push_back(arr[i++]);
    while (j <= right)
        temp.push_back(arr[j++]);
    for (int k = left; k <= right; k++)
        arr[k] = temp[k - left];
    return count;
}

long long countSignificantInversions(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return 0;
    int mid = left + (right - left) / 2;
    long long count = countSignificantInversions(arr, left, mid);
    count += countSignificantInversions(arr, mid + 1, right);
    count += mergeCount(arr, left, mid, right);
    return count;
}

int main()
{
    cout << endl
         << " __  __         __   __    ___  ||   __  __         __  ___ ___ __   ||   __  __         __   __   __    " << endl
         << "  _)  _)|  __  /  \\ |_  /|   /  ||    _)  _)|  __  /  \\   /   /  _)  ||    _)  _)|  __  /  \\ /__  (__) /|" << endl
         << " /__ __)|(     \\__/ __) _|_ /   ||   /__ __)|(     \\__/  /   /  /__  ||   /__ __)|(     \\__/ \\__) (__) _|_" << endl
         << endl;

    vector<int> inputArr;
    cout << " Enter atleast 10 array elements, press '-1' for end of array: " << endl;
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
        inputArr.push_back(input);
    }

    cout << "Array: " << endl;
    for (auto i : inputArr)
    {
        cout << i << "  ";
    }
    cout << endl;

    long long result = countSignificantInversions(inputArr, 0, inputArr.size() - 1);
    cout << "Significant inversions: " << result << endl;
}
