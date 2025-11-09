#include <iostream>
#include <vector>

using namespace std;

bool equivalent(int a, int b)
{
    return a == b;
}

int findMajority(vector<int> &cards)
{
    if (cards.size() == 1)
        return cards[0];

    int mid = cards.size() / 2;
    vector<int> left(cards.begin(), cards.begin() + mid), right(cards.begin() + mid, cards.end());
    int leftMajor = findMajority(left), rightMajor = findMajority(right);

    if (leftMajor == -1 && rightMajor == -1)
        return -1;
    if (leftMajor == -1)
        return rightMajor;
    if (rightMajor == -1)
        return leftMajor;
    if (equivalent(leftMajor, rightMajor))
        return leftMajor;

    int countLeft = 0, countRight = 0;
    for (int c : cards)
    {
        if (equivalent(c, leftMajor))
            countLeft++;
        if (equivalent(c, rightMajor))
            countRight++;
    }

    int n = cards.size();
    if (countLeft > n / 2)
        return leftMajor;
    if (countRight > n / 2)
        return rightMajor;

    return -1;
}

int main()
{
    cout << endl
         << " __  __         __   __    ___  ||   __  __         __  ___ ___ __   ||   __  __         __   __   __    " << endl
         << "  _)  _)|  __  /  \\ |_  /|   /  ||    _)  _)|  __  /  \\   /   /  _)  ||    _)  _)|  __  /  \\ /__  (__) /|" << endl
         << " /__ __)|(     \\__/ __) _|_ /   ||   /__ __)|(     \\__/  /   /  /__  ||   /__ __)|(     \\__/ \\__) (__) _|_" << endl
         << endl;

    vector<int> cards;
    cout << " Enter atleast 10 card values, press '-1' for end of input: " << endl;
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
        cards.push_back(input);
    }

    cout << "Cards: " << endl;
    for (auto i : cards)
    {
        cout << i << "  ";
    }
    cout << endl;

    int result = findMajority(cards);
    if (result != -1)
        cout << "Yes, card " << result << " appears > n/2 times" << endl;
    else
        cout << "No such card" << endl;
}