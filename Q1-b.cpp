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

*/

int main()
{
    cout << findExponent(2, 8);
}