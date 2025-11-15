#include <iostream>
#include <vector>

using namespace std;

/* QUESTION 1 -> part b(1)

If n is even: a^n = (a^(n/2))^2
If n is odd: a^n = a × (a^(n-1))^2 = a × (a^(n/2))^2

Example: 2^8

2^8 = (2^4)^2
2^4 = (2^2)^2
2^2 = (2^1)^2
2^1 = 2

*/

int findExponent(int number, int power)
{
    if (power == 0)
        return 1;

    if (power == 1)
        return number;

    int half = findExponent(number, power / 2); // Each call divides the power into 2.

    // If the power was even, e.g 8 , it will the 4, 2, 1 for the recursive calls. But if it was odd, such as 9 , then 9/2 = 4 not 4.5 so we have to multiply the number as well for the odd case.

    if (power % 2 == 0)
        return half * half;
    else
        return number * half * half;
}

/* QUESTION 1 -> part b(2)
T(n) = T(⌊n/2⌋) + 2 for odd n (one recursive call + 2 multiplications)
T(n) = T(⌊n/2⌋) + 1 for even n (one recursive call + 1 multiplication)

For simplicity, let's assume worst case where we always do 2 multiplications:
T(n) = T(⌊n/2⌋) + 2
Using the substitution method (assuming n = 2^k for simplicity):

T(n) = T(n/2) + 2
T(n/2) = T(n/4) + 2
T(n/4) = T(n/8) + 2
...

Expanding:

T(n) = T(n/2) + 2
T(n) = [T(n/4) + 2] + 2 = T(n/4) + 4
T(n) = [T(n/8) + 2] + 4 = T(n/8) + 6
T(n) = T(n/2^k) + 2k

When n/2^k = 1, we have k = log₂(n):

T(n) = T(1) + 2log₂(n)
T(n) = 0 + 2log₂(n)
T(n) = 2log₂(n)

Hence the number of multiplications made are 2log₂(n) and the time complexity is O(log₂n)

Question 1 part b(3)

Below is the code for finding the exponent of a number through brute force:
*/

int findExponentByBruteForce(int number, int power)
{
    if (number == 1) // 1 to any power is always 1 yayy!!
    {
        return number;
    }
    if (power == 1)
    {
        return number;
    }
    if (power == 0)
    {
        return 1;
    }
    int result = 1;
    while (power != 0)
    {
        result *= number;
        power--;
    }
    return result;
}

/* Divide and Conquer Vs Brute Force
The divide and Conquer approach takes O(logn) time while the brute force approach takes O(n) time. This make recursive approach better, but we will have to use long or long long it for larger numbers and powers. Also, recursive overhead will be much larger if exponent is huge.
*/
int main()
{
    cout << endl
         << " __  __         __   __    ___  ||   __  __         __  ___ ___ __   ||   __  __         __   __   __    " << endl
         << "  _)  _)|  __  /  \\ |_  /|   /  ||    _)  _)|  __  /  \\   /   /  _)  ||    _)  _)|  __  /  \\ /__  (__) /|" << endl
         << " /__ __)|(     \\__/ __) _|_ /   ||   /__ __)|(     \\__/  /   /  /__  ||   /__ __)|(     \\__/ \\__) (__) _|_" << endl
         << endl;

    int number, power;
    cout
        << "Enter number and power: ";
    cin >> number >> power;
    cout << "By Divide and Conquer: = " << findExponent(number, power) << endl;
    cout << "By Brute Force: = " << findExponentByBruteForce(number, power);
}
