#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

typedef unsigned long long ull;

//mergesort
//divide array in half, sort each half then merge back together.
//each half has sorting algorithm applied (e.g. divide in half, sort then merge)
//until just comparing two single element arrays.
void merge(vector<int> &array, vector<int> &helper, int low, int middle, int high)
{
    //copy both halfs into helper array
    for(int i = low; i <= high; i++)
    {
        helper[i] = array[i];
    }
    
    int helperLeft = low;
    int helperRight = middle + 1;
    int current = low;
    
    //iterate through helper array, compare L and R half, copying back the smaller element from the two halves into the original array
    while(helperLeft <= middle && helperRight <= high)
    {
        if(helper[helperLeft] <= helper[helperRight])
        {
            array[current] = helper[helperLeft];
            helperLeft++;
        }
        else //if right element is smaller than left element
        {
            array[current] = helper[helperRight];
            helperRight++;
        }
        current++;
    }
    
    //copy rest of left side of the array into the target array
    int remaining = middle - helperLeft;
    for(int i = 0; i <= remaining; i++)
    {
        array[current+i] = helper[helperLeft + i];
    }
}

void mergesort(vector<int> &array, vector<int> &helper, int low, int high)
{
    if (low < high)
    {
        int middle = (low + high) / 2;
        mergesort(array, helper, low, middle);  //sort left half
        mergesort(array, helper, middle+1, high); //sort right half
        merge(array, helper, low, middle, high); //merge the halfs
    }
}

void mergesort(vector<int> &array)
{
    vector<int> helper(array.size());
    mergesort(array, helper, 0, (int)array.size()-1);
}
    
    
int main(int argc, const char * argv[])
{
    vector<ull> numbers;
    
    vector<int> array;
    array.push_back(6);
    array.push_back(5);
    array.push_back(3);
    array.push_back(1);
    array.push_back(8);
    array.push_back(7);
    array.push_back(2);
    array.push_back(4);
    
    for(int i = 0; i < array.size(); i++)
    {
        cout << array[i] << ", ";
    }
    cout << endl;
    
    mergesort(array);
    cout << "mergesorting" << endl;
    
    for(int i = 0; i < array.size(); i++)
    {
        cout << array[i] << ", ";
    }
    cout << endl;
    
    
    return 0;
}
