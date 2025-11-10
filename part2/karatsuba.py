"""
Karatsuba Algorithm:

- Purpose: Efficient multiplication of very large numbers using divide-and-conquer.
- Classical multiplication takes O(n^2) time; Karatsuba reduces it to ~O(n^1.585).
- Idea: Split each number into two halves.

Steps:
1. Split numbers x and y:
    Example: x = 146123 can be split as
            x = a * 10^(n/2) + b = 146 * 1000 + 123
            Here, a = 146, b = 123, n = total digits of x.
    Similarly, y = c * 10^(n/2) + d
            Example: y = 789456 → c = 789, d = 456
    This helps reduce a large multiplication into smaller parts.

2. Compute three products recursively:
    We know that x * y = ac * 10^n + (ad+bc) * 10^(n/2) + bd;
    thus we compute:
    ac = a * c
    bd = b * d
    ad_plus_bc = (a + b) * (c + d) - ac - bd
        * why ad_plus_bc calculated and NOT calling recursivley on ad and bc separately?
        * Reason: Calculating (a+b)*(c+d) and subtracting ac and bd gives ad + bc, using only one extra multiplication instead of two,
        * saves computation time / extra recursive call

3. Combine results:
    x * y = ac * 10^n + (ad+bc) * 10^(n/2) + bd

4. Recursively apply the same steps if the halves are large.

- Advantages:
    * Fewer multiplications (3 instead of 4 per recursion)
    * Faster for very large numbers
- Base case: Use normal multiplication when numbers are small enough.
"""


def karatsuba(x, y):

    # stopping criteria -- just return the product when the broken down numbers become < 10
    if x < 10 and y < 10:
        return x*y
    
    # calculating n
    n = max(len(str(x)), len(str(y)))

    # getting a & b, (first & second half of first number x) and c & d (first & second half of second number y)
    m = n // 2
    a = x // 10**m
    b = x % 10**m
    c = y // 10**m
    d = y % 10**m

    # writing calling recursively on the halves:
    ac = karatsuba(a,c)
    bd = karatsuba(b, d)
    ad_plus_bc = karatsuba(a+b, c+d) - ac - bd

    prod_xy =  ac * (10 ** (2*m)) + ad_plus_bc * 10 ** m + bd

    return prod_xy # will return the correct large product

if __name__ == "__main__":
    with open("karatsubaSampleInput.txt", "r") as file:
        lines = file.readlines()
        x = int(lines[0].strip())
        y = int(lines[1].strip())

    print("Product:", karatsuba(x, y))


















