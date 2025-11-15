#include <iostream>
#include <vector>
using namespace std;

struct Result
{
    int buyDay;
    int sellDay;
    int profit;
};

Result maxProfitSplit(vector<int> &prices, int left, int right)
{
    if (left >= right)
        return {left, right, 0};

    int mid = left + (right - left) / 2;

    Result leftBest = maxProfitSplit(prices, left, mid);
    Result rightBest = maxProfitSplit(prices, mid + 1, right);

    // Cross case: buy in left half, sell in right half
    int minLeft = left;
    for (int i = left; i <= mid; i++)
    {
        if (prices[i] < prices[minLeft])
            minLeft = i;
    }

    int maxRight = mid + 1;
    for (int i = mid + 1; i <= right; i++)
    {
        if (prices[i] > prices[maxRight])
            maxRight = i;
    }

    int crossProfit = prices[maxRight] - prices[minLeft];
    Result crossResult = {minLeft, maxRight, crossProfit};

    // Return the best among the three
    if (leftBest.profit >= rightBest.profit && leftBest.profit >= crossResult.profit)
        return leftBest;
    else if (rightBest.profit >= leftBest.profit && rightBest.profit >= crossResult.profit)
        return rightBest;
    else
        return crossResult;
}

int main()
{
    cout << endl
         << " __  __         __   __    ___  ||   __  __         __  ___ ___ __   ||   __  __         __   __   __    " << endl
         << "  _)  _)|  __  /  \\ |_  /|   /  ||    _)  _)|  __  /  \\   /   /  _)  ||    _)  _)|  __  /  \\ /__  (__) /|" << endl
         << " /__ __)|(     \\__/ __) _|_ /   ||   /__ __)|(     \\__/  /   /  /__  ||   /__ __)|(     \\__/ \\__) (__) _|_" << endl
         << endl;
    vector<int> inputArr;
    cout << " Enter atleast 10 price array,press '-1' for end of array: " << endl;
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
    cout << "Prices: " << endl;
    for (auto i : inputArr)
    {
        cout << i << "  ";
    }

    Result result = maxProfitSplit(inputArr, 0, inputArr.size() - 1);

    if (result.profit > 0)
    {
        cout << "Buy on day " << result.buyDay + 1 << ", sell on day " << result.sellDay + 1 << endl;
        cout << "Profit per share: Rs" << result.profit << endl;
    }
    else
    {
        cout << "No profit possible during this period." << endl;
    }
}
