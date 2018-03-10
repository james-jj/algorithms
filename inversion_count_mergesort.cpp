#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

struct tuples {
    ll value;
    ll element;
};

/*
 http://www.spoj.com/problems/INVCNT/
INVCNT - Inversion Count
#graph-theory #number-theory #shortest-path #sorting #bitmasks
Let A[0...n - 1] be an array of n distinct positive llegers. If i < j and A[i] > A[j] then the pair (i, j) is called an inversion of A. Given n and an array A your task is to find the number of inversions of A.

Input
 i= 0  1   2  3 4   5   6   7   8  9
    3  7   6  1 9   8  23  10  99 57

 merge:
    0 1 2 3 4 5  6  7  8  9
    3 7 6 1 9 8 23 10 99 57
 mergesort:
 1   [3,7,6,1,9] [8, 23, 10, 99, 57]
 2   [3,7,6] [1,9] [8,23,10] [99,57]
 3   [3,7][6] [1,9] [8,23][10] [99,57]
 
 merge:
 3. helper = [3,7] arr = [3,7]
    helper = [6] arr = [6] 
    helper = [1,9] arr = [1,9]
    helper = [8,23] arr = [8,23] 
    helper = [10]   arr = [10]
    helper = [99,57] arr = [57,99] nInversions++
 
 2
 
 
 
 
 
The first line contains t, the number of testcases fointowed by a blank space. Each of the t tests start with a number n (n <= 200000). Then n + 1 lines fointow. In the ith line a number A[i - 1] is given (A[i - 1] <= 10^7). The (n + 1)th line is a blank space.

Output

For every test output one line giving the number of inversions of A.

Example

Input:
2

3
3
1
2

5
2
3
8
6
1


Output:
2
5
 */
//merge
ll merge(vector<ll> &A, ll start, ll mid, ll end)
{
    vector<ll> helper(end-start+1);
    ll helperLeft = start;
    ll helperRight = mid+1;
    ll nInversions = 0;
    bool swapped = false;
    int count = 0;
    int counter = 0;

    ll n = 0;    
    for(ll i = start; i <= end; i++)
    {
        if(helperLeft > mid)
        {
            helper[count] = A[helperRight];
            helperRight++;
            count++;
        }
        else if(helperRight > end)
        {
            helper[count] = A[helperLeft];
            helperLeft++;
            count++;
        }
        else if(A[helperLeft] > A[helperRight])  //left side is greater than right side, need to swap
        {
            //this is an inversion
            helper[count] = A[helperRight];
            nInversions += mid+1 - helperLeft;
            count++;
            helperRight++;
            swapped = true;
        }
        else    //right side is greater than left side, order is correct so dont do anything
        {
            helper[count] = A[helperLeft];
            helperLeft++;
            count++;
        }
    }
    //copy sorted elements into the array in the new order, only need to do this if any swaps occured
    if(swapped)
    {
        count = 0;
        for(ll i = start; i <= end; i++)
        {
            //merge first half of array
            A[i] = helper[count];
            count++;
        }
    }
    return nInversions;
}

//merge sort recursive
ll mergeSort(vector<ll> &A, ll start, ll end)
{
    ll rc, lc, mc;
    rc = lc = mc = 0;
    if(start < end)
    {
        ll mid = (start + end) / 2;
        lc = mergeSort(A, start, mid);
        rc = mergeSort(A, mid+1, end);
        mc = merge(A, start, mid, end);
        return lc + rc + mc;
    }
    else
    {
        return 0;
    }
}

ll mergeSort(vector<ll> &A)
{
    ll start = 0;
    ll end = A.size()-1;
    ll nInversions = 0;
    nInversions = mergeSort(A, start, end);
    return nInversions;
}

int main(int argc, const char * argv[]) {
    std::ios::sync_with_stdio(false);
    
    ll t, n, valueIn;
    cin >> t;   //number of testcases
    string blank;
    getline(cin, blank);    //consume white space after cin
    getline(cin, blank);    //consume blank line

    for(ll i = 0; i < t; i++)  //loop over test cases
    {
        cin >> n; //number of lines in array
        vector<ll> arrIn(n);
        for(ll j = 0; j < n; j++)
        {
            cin >> valueIn;
            arrIn[j] = valueIn;
        }
        //perform mergesort to get the n inversions
        cout << mergeSort(arrIn) << endl;
    }
    return 0;
}
