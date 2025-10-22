#include<iostream>
#include <vector>
using namespace std;

struct Result
{
    int buyDay;
    int sellDay;
    int profit;
};
pair<int, int> maxProfitSplitHelper(vector<int> &prices, int left, int right){
    int minIndex = left;
    int maxIndex = left;
    for (int i = left; i <= right; i++)
    {
        if (prices[i] < prices[minIndex])
            minIndex = i;
        if (prices[i] > prices[maxIndex])
            maxIndex = i;
    }
    return {minIndex, maxIndex};
}

Result maxProfitSplit(vector<int> &prices, int left, int right)
{
    if (left >= right)
        // return {-1,-1,-1};
        // return ;
        return {left, right, 0};

    int mid = left + (right - left) / 2;
    Result leftBest = maxProfitSplit(prices, left, mid);
    Result rightBest = maxProfitSplit(prices, mid + 1, right);
    // maxProfitSplit(prices, left, mid);
    // maxProfitSplit(prices, mid + 1, right);

    // (buy in left, sell in right)
    auto [minLeft, maxLeft] = maxProfitSplitHelper(prices, left, mid);
    auto [minRight, maxRight] = maxProfitSplitHelper(prices, mid + 1, right);

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
int main(){
    vector<int> prices = {10,8,12,13,2,4,13,20};
    Result result = maxProfitSplit(prices, 0, prices.size() - 1);
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