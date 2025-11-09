#include <iostream>
#include <vector>
using namespace std;

int findPeakRecursive(vector<int> &arr, int l, int r)
{
    int mid = l + (r - l) / 2;

    if (l == r)
        return l;

    if (arr[mid] > arr[mid + 1])
        return findPeakRecursive(arr, l, mid);
    else
        return findPeakRecursive(arr, mid + 1, r);
}

int main()
{
    cout << endl
         << " __  __         __   __    ___  ||   __  __         __  ___ ___ __   ||   __  __         __   __   __    " << endl
         << "  _)  _)|  __  /  \\ |_  /|   /  ||    _)  _)|  __  /  \\   /   /  _)  ||    _)  _)|  __  /  \\ /__  (__) /|" << endl
         << " /__ __)|(     \\__/ __) _|_ /   ||   /__ __)|(     \\__/  /   /  /__  ||   /__ __)|(     \\__/ \\__) (__) _|_" << endl
         << endl;
    vector<int> inputArr;
    cout << " Enter atleast 10 array elements,press '-1' for end of array: " << endl;
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
    int n = inputArr.size();
    int p = findPeakRecursive(inputArr, 0, n - 1);
    cout << "peak element: " << inputArr[p] << endl;
}
