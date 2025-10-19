#include <iostream>
#include <vector>

using namespace std;

struct holdMinMax
{
    int min;
    int max;
};

/* QUESTION 1 -> part a(1) */

holdMinMax findMinMax(vector<int> &arr, int left, int right)
{
    holdMinMax result;

    // Base Case 1 : Only one element
    if (left == right)
    {
        result.min = arr[left];
        result.max = arr[right];
        return result;
    }

    // Base Case 2: Two elements
    if (right - left == 1)
    {
        if (arr[left] <= arr[right])
        {
            result.min = arr[left];
            result.max = arr[right];
            return result;
        }
        else
        {
            result.min = arr[right];
            result.max = arr[left];
            return result;
        }
    }

    int mid = left + (right - left) / 2;

    // Divide: Find min and max of left and right halves. Similar to what we do in merge sort.
    holdMinMax leftResult = findMinMax(arr, left, mid);
    holdMinMax rightResult = findMinMax(arr, mid + 1, right);

    // Conquer: i.e combine results and compare. But because there are only 2 comparisions i.e for min and mix, so unlike merge sort , that takes   O(n) time  for combining, this will take constant i.e O(1) time.

    result.min = leftResult.min < rightResult.min ? leftResult.min : rightResult.min;
    result.max = leftResult.max > rightResult.max ? leftResult.max : rightResult.max;

    return result;
}

/* QUESTION 1 -> part a(2)

C(n) = 2C(n/2) + 2 => 2 comparisions in each stage, each of size of n/2 + additional 2 comparisions for min and max at the end.

For an array of size n = 2^k, the recurrence relation for comparisons is:
C(n) = 2C(n/2) + 2 for n > 2, with C(2) = 1, C(1) = 0
Solving by backward substitution:
Starting with C(2^k):

= 2C(2^(k-1)) + 2
= 2[2C(2^(k-2)) + 2] + 2 = 2²C(2^(k-2)) + 2² + 2
= 2³[2C(2^(k-3)) + 2] + 2² + 2 = 2³C(2^(k-3)) + 2³ + 2² + 2

Continuing this pattern:

= 2^k C(2⁰) + 2^(k-1) + ... + 2² + 2
= 2^(k-1)·C(2) + (2^k - 2 - 2^1)
= 2^(k-1)·1 + 2^k - 2 - 2
= 2^k - 2 + 2^(k-1) - 2 = (3/2)·2^k - 2 = (3n/2) - 2


For n = 8:
```
                 Level 0: [8 elements]
                          ↓ 2 comparisons
                 /                    \
      Level 1: [4 elem]              [4 elem]
                ↓ 2 comp              ↓ 2 comp
              /        \            /        \
   Level 2: [2]       [2]        [2]       [2]
            ↓1 comp   ↓1 comp    ↓1 comp   ↓1 comp

Total comparisons:
- Level 2: 4 comparisons (base cases)
- Level 1: 4 comparisons (combining)
- Level 0: 2 comparisons (final combine)
Total: 10 comparisons

Using formula: (3×8/2) - 2 = 12 - 2 = 10 ✓
Writing code below for counting the number of comparisions...
*/

int comparisions;
void initializeNumberOfComparions()
{
    comparisions = 0;
}
int findNumberOfComparisionsDAC(vector<int> &arr, int left, int right) // DAC = Divide and Conquer
{
    holdMinMax result;

    // Base Case 1 : Only one element
    if (left == right)
    {
        result.min = arr[left];
        result.max = arr[right];
        return comparisions;
    }

    // Base Case 2: Two elements
    if (right - left == 1)
    {
        if (arr[left] <= arr[right])
        {
            result.min = arr[left];
            result.max = arr[right];
            return ++comparisions;
        }
        else
        {
            result.min = arr[right];
            result.max = arr[left];
            return ++comparisions;
        }
    }

    int mid = left + (right - left) / 2;

    holdMinMax leftResult = findMinMax(arr, left, mid);
    holdMinMax rightResult = findMinMax(arr, mid + 1, right);

    ++comparisions;
    result.min = leftResult.min < rightResult.min ? leftResult.min : rightResult.min;
    ++comparisions;
    result.max = leftResult.max > rightResult.max ? leftResult.max : rightResult.max;

    return comparisions;
}

/* QUESTION 1 -> part a(3)

The brute force approach makes approximately 2n comparisions. However, divide and conquer approach takes approx (3n/2 i.e 1.5n) comparisons. So we get 25% less comparisions using the divide and conquer approach.

Below is the code for counting the number of comparisions using Brute Force Approach as well.

*/

int findNumberOfComparisionsBFA(vector<int> &arr)
{
    int min = arr[0], max = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] < min)
            min = arr[i];
        ++comparisions;
        if (arr[i] > max)
            max = arr[i];
        ++comparisions;
    }
    return comparisions;
    // Total = 2(n-1) = 2n-2 comparisions.
}

int main()
{

    cout << endl
         << "                  __                                                                                      " << endl
         << "|\\/|. _ |\\/| _   |_. _  _| _ _                                                                           " << endl
         << "|  ||| )|  |(_|)(| || )(_|(-|                                                                            " << endl
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
    while (true)
    {
        cout << "1. Find Min and Max in Array" << endl
             << "2. Count Number of Comparisions using Divide and Conquer" << endl
             << "3. Count Number of Comparions using Brute Force" << endl
             << "4.Exit" << endl;
        int opt;
        cout << "Enter the correct Option Number: ";
        cin >> opt;
        switch (opt)
        {
        case 1:
        {
            holdMinMax res = findMinMax(inputArr, 0, inputArr.size() - 1);
            cout << "Minimum: " << res.min << endl;
            cout << "Maximum: " << res.max << endl;
            cout << endl;
            break;
        }
        case 2:
        {
            initializeNumberOfComparions();
            int numberOfComparisionsDAC = findNumberOfComparisionsDAC(inputArr, 0, inputArr.size() - 1);
            cout << "Number of Comparisions: " << numberOfComparisionsDAC << endl;
            break;
        }
        case 3:
        {
            initializeNumberOfComparions();
            int numberOfComparisionsBFA = findNumberOfComparisionsBFA(inputArr);
            cout << "Number of Comparisions: " << numberOfComparisionsBFA << endl;
            break;
        }
        case 4:
        {
            return 0;
        }
        }
    }
}
