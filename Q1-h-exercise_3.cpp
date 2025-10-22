#include <bits/stdc++.h>
using namespace std;

bool equivalent(int a, int b) {
    return a == b;
}

int findMajority(vector<int>& cards) {
    if (cards.size() == 1) return cards[0];
    
    int mid = cards.size() / 2;
    vector<int> left(cards.begin(), cards.begin() + mid), right(cards.begin() + mid, cards.end());
    int leftMajor = findMajority(left), rightMajor = findMajority(right);
    
    if (leftMajor == -1 && rightMajor == -1) return -1;
    if (leftMajor == -1) return rightMajor;
    if (rightMajor == -1) return leftMajor;
    if (equivalent(leftMajor, rightMajor)) return leftMajor;
    
    int countLeft = 0, countRight = 0;
	for (int c : cards) {
    	if (equivalent(c, leftMajor)) countLeft++;
    	if (equivalent(c, rightMajor)) countRight++;
	}
	
    int n = cards.size();
    if (countLeft > n / 2) return leftMajor;
    if (countRight > n / 2) return rightMajor;
    
    return -1;
}

int main() {
    vector<int> cards = {2, 2, 2, 3, 2, 5, 2, 2, 1, 2};
    int result = findMajority(cards);
    if (result != -1) cout << "yes, card " << result << " appears > n/2 times";
    else cout << "no such card";
}
