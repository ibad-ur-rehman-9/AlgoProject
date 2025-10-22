/*
One dimensional???
-> This means we are working on a single number line , therefore we do not have points here in 2D space, in which we have x and y coordinates both.

*/

#include <iostream>
#include <vector>

using namespace std;

// Creating a class here as we have to return the cloesest distance + the pair of points. So we will return the whole object instead.
class closestPair
{
public:
    double number1;
    double number2;
    double distance;

    closestPair() {};
    closestPair(double n1, double n2, double d) : number1(n1), number2(n2), distance(d) {}
};

// This fnction makes every negative distance positive , as distance is always positive.
double findAbsoluteValue(double x)
{
    if (x < 0)
    {
        return -x; // E.g if x is -5, it does -(-5) so it becomes 5.
    }
    return x;
}

// Asal function ye hai

closestPair findClosestPair(vector<double> &numberList, int start, int end)
{
    int size = end - start;

    if (size <= 1)
    {
        return closestPair(0, 0, 1e308); // Base case 1
    }

    if (size == 2)
    {
        double dist = findAbsoluteValue(numberList[start + 1] - numberList[start]);
        return closestPair(numberList[start], numberList[start + 1], dist); // Base Case 2
    }

    int middle = start + (end - start) / 2;

    // Recursive Calls for left and right halves
    closestPair leftResult = findClosestPair(numberList, start, middle);
    closestPair rightResult = findClosestPair(numberList, middle, end);

    // Find now which half has the smaller distance.

    closestPair currentBest;
    if (leftResult.distance <= rightResult.distance)
    {
        currentBest = leftResult; // Yahan pr deep copy shallow copy wala chakkar nhi hosakta because we don't have any array or a pointer so that's why no need of a copy constructor.
    }
    else
    {
        currentBest = rightResult;
    }

    /*Now we have current best. But suppose this was the list {1,9,10,20}
    Left half: [1, 9] → closest pair is (1, 9) with distance = 8
    Right half: [10, 20] → closest pair is (10, 20) with distance = 10
    So current_best.distance = 8

    But wait! What about the pair (9, 10)?

    9 is in the left half
    10 is in the right half
    Distance = 1 ← This is actually the closest pair!

    => So now we have to find the cross-half closest pair possibilities.


    */
    for (int i = start; i < middle; i++)
    { // Every number in left half
        for (int j = middle; j < end; j++)
        { // Every number in right half
            double cross_boundary_distance = findAbsoluteValue(numberList[j] - numberList[i]);

            if (cross_boundary_distance < currentBest.distance)
            {
                // Found a better pair that crosses the boundary!
                currentBest.distance = cross_boundary_distance;
                currentBest.number1 = numberList[i];
                currentBest.number2 = numberList[j];
            }
        }
    }
    return currentBest;
}

/*
=>Efficiiency Class?
This creates a recursion tree with log n levels, and at each level we do O(n) work in the combine step, giving us O(n log n) total time.
=> IS IT A GOOD ALGORITHM FOR THIS PROBLEM????
No. Why??
  for (int i = start; i < middle; i++)
    { // Every number in left half
        for (int j = middle; j < end; j++)
        { // Every number in right half
            double cross_boundary_distance = findAbsoluteValue(numberList[j] - numberList[i]);

            if (cross_boundary_distance < currentBest.distance)
            {
                // Found a better pair that crosses the boundary!
                currentBest.distance = cross_boundary_distance;
                currentBest.number1 = numberList[i];
                currentBest.number2 = numberList[j];
            }
        }
    }

This nested loop checks every possible pair where:

One number comes from the left half
One number comes from the right half

If any of these cross-boundary pairs are closer than what we found before, we update our answer.
Why Is This O(n) Work?
In the worst case, if the left half has n/2 numbers and right half has n/2 numbers, we're doing (n/2) × (n/2) = O(n²) comparisons at each level! This is actually inefficient, which is why this approach isn't optimal for the 1D problem.

*/

int main()
{
    cout << endl
         << " __  __         __   __    ___  ||   __  __         __  ___ ___ __   ||   __  __         __   __   __    " << endl
         << "  _)  _)|  __  /  \\ |_  /|   /  ||    _)  _)|  __  /  \\   /   /  _)  ||    _)  _)|  __  /  \\ /__  (__) /|" << endl
         << " /__ __)|(     \\__/ __) _|_ /   ||   /__ __)|(     \\__/  /   /  /__  ||   /__ __)|(     \\__/ \\__) (__) _|_" << endl
         << endl;
    vector<double> list = {2.5, -3, 4, 10, 6};
    closestPair c = findClosestPair(list, 0, list.size() - 1);
    cout << "distance: " << c.distance << endl
         << "Pair: ( " << c.number1 << "," << c.number2 << " )" << endl;
}