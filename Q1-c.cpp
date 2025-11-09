#include <iostream>
#include <vector>

using namespace std;

/*
Inversions??
->Those elements in an array where arr[i] > arr[j] but j > i.
->Basically this is showing how much an array is sorted.

How to count inversions??
->During each merging step of the merge sort algorithm, we count cross inversions by comparing elements from the left half of the array with those from the right half. If we find an element arr[i] in the left half that is greater than an element arr[j] in the right half, we can conclude that all elements after i in the left half will also be greater than arr[j]. This allows us to count multiple inversions at once. Let's suppose if there are k elements remaining in the left half after i, then there are k cross inversions for that particular arr[j]. The rest of the merging process continues as usual, where we combine the two halves into a sorted array.

*/

/*remember this function only counts the cross inversions i.e inversions when an element of left sub array is bigger than the right sub array. It does not count the inner inversions of both sub arrays.For e.g Consider the array {4, 3, 2, 1}: **Inversions:**
In left `{4, 3}`: (4,3) → **1 inversion**
In right `{2, 1}`: (2,1) → **1 inversion**
Across both: (4,2), (4,1), (3,2), (3,1) → **4 inversions** THIS CROSS INVERSION IS COUNTED BY THIS FUNCTION, NOT THE ABOVE 2.
*/

int mergeAndCountSplitInversions(vector<int> &arr, int left, int middle, int right)
{

    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    vector<int> leftSubarray(leftSize);
    vector<int> rightSubarray(rightSize);

    for (int i = 0; i < leftSize; i++)
        leftSubarray[i] = arr[left + i];
    for (int j = 0; j < rightSize; j++)
        rightSubarray[j] = arr[middle + 1 + j];

    int leftIndex = 0;
    int rightIndex = 0;
    int mergedIndex = left;
    int inversionCount = 0;

    while (leftIndex < leftSize && rightIndex < rightSize)
    {

        // no inversion if arr[i] < arr[j]
        if (leftSubarray[leftIndex] <= rightSubarray[rightIndex])
        {
            arr[mergedIndex++] = leftSubarray[leftIndex++];
        }
        // If right element is smaller, it forms inversions with all remaining elements in the left subarray
        else
        {
            arr[mergedIndex++] = rightSubarray[rightIndex++];
            inversionCount += (leftSize - leftIndex);
        }
    }

    while (leftIndex < leftSize)
        arr[mergedIndex++] = leftSubarray[leftIndex++];

    while (rightIndex < rightSize)
        arr[mergedIndex++] = rightSubarray[rightIndex++];

    return inversionCount;
}

int countInversionsInRange(vector<int> &arr, int left, int right)
{
    int inversionCount = 0;

    if (left < right)
    {
        int middle = left + (right - left) / 2;

        inversionCount += countInversionsInRange(arr, left, middle);

        inversionCount += countInversionsInRange(arr, middle + 1, right);

        inversionCount += mergeAndCountSplitInversions(arr, left, middle, right);
    }

    return inversionCount;
}
int inversionCount(vector<int> &arr)
{
    return countInversionsInRange(arr, 0, arr.size() - 1);
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
    cout << endl
         << "Inversion Count: " << inversionCount(inputArr);
}