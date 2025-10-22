// We can have multiple approaches for finding the pivot element. I have used the approach in which the first element of the partition is the pivot element always.

#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &arr, int start, int end)
{
    int pivot = arr[start]; // Pivot is our first element of the array

    // First we count how many numbers are less than the pivot in the array
    int count = 0;
    for (int i = start; i <= end; i++)
    {
        if (arr[i] < pivot)
        {
            count++;
        }
    }

    int pivotIndex = start + count;

    swap(arr[start], arr[pivotIndex]);
    int i = start;
    int j = end;
    while (i < pivotIndex && j > pivotIndex)
    {
        while (arr[i] < pivot) // No need to swap case1
        {
            i++;
        }

        while (arr[j] > pivot) // No need to swap case2
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            swap(arr[i], arr[j]);
        }
    }

    return pivotIndex;
}

void quickSort(vector<int> &arr, int start, int end)
{
    // Base Case
    if (start >= end)
    {
        return;
    }

    // Making a partition
    int p = partition(arr, start, end);

    // Recursive calls for sorting the left and right partitions
    quickSort(arr, start, p - 1);
    quickSort(arr, p + 1, end);

    return;
}

/*
Best Case and Worst case complexity of Quick sort??
=> Best Case O(nlogn)
When the first element happens to be close to the median value. So the array gets divided into roughly equal halves
Example: [5, 2, 8, 1, 9, 3, 7] - first element 5 is near the middle value
[5, 2, 8, 1, 9, 3, 7]  pivot = 5
→ [2, 1, 3] | 5 | [8, 9, 7]  ← Balanced!

The recursion tree has log n levels (because we're dividing by 2 each time)
At each level, we do O(n) work (partitioning all elements)
Total: log n levels × O(n) work per level = O(n log n)


=> Worst Case O(n^2)
When the pivot is the smallest or the largest element. i.e the array is sorted or reverse sorted, or when all the elements of the array are identical.

[1, 2, 3, 4, 5]  pivot = 1 (smallest!)
→ [] | 1 | [2, 3, 4, 5]  ← Extremely unbalanced!

Then: [2, 3, 4, 5]  pivot = 2
→ [] | 2 | [3, 4, 5]  ← Still unbalanced!

Then: [3, 4, 5]  pivot = 3
→ [] | 3 | [4, 5]

Then: [4, 5]  pivot = 4
→ [] | 4 | [5]

5 levels for 5 elements = O(n²)
*/
int main()
{
    cout << endl
         << " __  __         __   __    ___  ||   __  __         __  ___ ___ __   ||   __  __         __   __   __    " << endl
         << "  _)  _)|  __  /  \\ |_  /|   /  ||    _)  _)|  __  /  \\   /   /  _)  ||    _)  _)|  __  /  \\ /__  (__) /|" << endl
         << " /__ __)|(     \\__/ __) _|_ /   ||   /__ __)|(     \\__/  /   /  /__  ||   /__ __)|(     \\__/ \\__) (__) _|_" << endl
         << endl;
    vector<int> arr1 = {5, 2, 8, 1, 9, 3, 7};
    vector<int> arr2 = {1, 2, 3, 4, 5};

    for (auto i : arr1)
    {
        cout << i << "  ";
    }
    cout << endl
         << "(Best Case) -> Sorting this array in which median value i.e 5 becomes the pivot" << endl;

    quickSort(arr1, 0, arr1.size() - 1);
    for (auto i : arr1)
    {
        cout << i << "  ";
    }
    cout << endl
         << endl;

    for (auto i : arr2)
    {
        cout << i << "  ";
    }
    cout << endl
         << "(Worst Case) -> Sorting this array which is already sorted." << endl;

    quickSort(arr1, 0, arr2.size() - 1);
    for (auto i : arr2)
    {
        cout << i << "  ";
    }
    cout << endl
         << endl;
}
