#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

//quick sort
//pick a random element and partition the array so all numbers less than partition element
//come before all elements that are greater than it.
int partition(vector<int> &arr, int left, int right)
{
    int pivot = arr[(left+right)/2];
    while(left <= right)
    {
        //find element on left that should be on right
        while(arr[left] < pivot) left++;
        
        //find element on right that should be on left
        while(arr[right] > pivot) right--;
    
        //swap elements and move left and right indices
        if(left <= right)
        {
            swap(arr[left], arr[right]);
            left++;
            right--;
            
        }
    }
    return left;
}

void quickSort(vector<int> &arr, int left, int right)
{
    int index = partition(arr, left, right);
    if(left < index - 1)    //sort left half
    {
        quickSort(arr, left, index-1);
    }
    if(index < right)   //sort right half
    {
        quickSort(arr, index, right);
    }
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
    
    quickSort(array,0,array.size()-1);
    cout << "quicksorting" << endl;
    
    for(int i = 0; i < array.size(); i++)
    {
        cout << array[i] << ", ";
    }
    cout << endl;
    
    
    return 0;
}
