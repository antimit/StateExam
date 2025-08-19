#include <iostream>
#include <vector>

using namespace std;

void heapify(vector<int> &arr,int size, int i )
{
    int largest = i;

    int l = 2*i + 1;

    int r = 2*i + 2;


    if(l < size && arr[l] > arr[largest])
    {
        largest = l;
    }

    if(r < size && arr[r] > arr[largest])
    {
        largest = r;
    }
    
    if(largest != i)
    {
        swap(arr[largest], arr[i]);

        heapify(arr,size,largest);
    }
}


void heapSort(vector<int> & arr)
{
    int size = arr.size();

    //making max heap
    for(int i = size /2 -1; i >= 0; i--)
    {
        heapify(arr, size,i);
    }   

    for(int i = size - 1; i>0; i--)
    {

        swap(arr[0],arr[i]);

        heapify(arr,i,0);
    }

}


void print_array(vector<int> arr)
{
    for(int i = 0; i <arr.size();i++ )
    {
        cout << arr[i]<< " ";
    }
}

int main()
{
    vector<int> arr = { 9, 4, 3, 8, 10, 2, 5 };

    cout <<"Unsorted array"<<std::endl;
    print_array(arr);
    heapSort(arr);
    cout <<"Sorted array"<<std::endl;
    print_array(arr);
}


/*
a) Heap storage in array:
   - A heap is stored in a simple array.
   - For a node at index i:
       left child  = 2*i + 1
       right child = 2*i + 2
       parent      = (i-1)/2
   - Because the heap is a complete binary tree, this mapping works without gaps.

   Example (max-heap stored in array):
       Index:  0   1   2   3   4   5   6
       Value: 15  12   6  10   5   3   2
       Tree (conceptually):
                 15
               /    \
             12      6
            / \    / \
          10   5  3   2
*/


/*
b) Algorithm description:
   1. Build a max-heap from the unsorted array (bottom-up heapify).
   2. Repeat until only one element remains:
      - Swap the root (maximum) with the last element.
      - Reduce heap size by 1 (exclude last element from heap).
      - Heapify the root to restore max-heap property.
   3. The array becomes sorted in ascending order.
*/



/*
Heapsort complexity (ASCII proofs)

------------------------------------------------------------
Build-heap (bottom-up) runs in O(n)
------------------------------------------------------------
Definitions:
- bottom-height h of a node = max number of edges from it down to a leaf.
- In a complete binary tree, the number of nodes with bottom-height h is
  at most n / 2^(h+1)  (about half the nodes are leaves (h=0), a quarter
  have h=1, an eighth have h=2, ...).

Cost per node at bottom-height h:
- Sift-down (heapify) can sink at most h levels.
- Each sink step is O(1), so cost per node is O(h).

Sum over all nodes:
  T_build(n) <= sum_{h=0..H} [ (#nodes at h) * O(h) ]
              <= sum_{h=0..H} [ (n / 2^(h+1)) * c*h ]    for some constant c
              =  (c*n) * sum_{h=0..H} [ h / 2^(h+1) ]
              =  (c*n/2) * sum_{h=0..H} [ h / 2^h ]

Series fact:
  S = sum_{h=0..infty} h / 2^h = 2.
  (Sketch: Let G(x)=sum_{h>=0} x^h = 1/(1-x). Differentiate:
           G'(x)=sum_{h>=1} h*x^{h-1} = 1/(1-x)^2.
           Multiply by x: sum_{h>=1} h*x^h = x/(1-x)^2.
           Plug x=1/2: S = (1/2) / (1/2)^2 = 2.)

Therefore:
  T_build(n) <= (c*n/2) * 2 = c*n = O(n).

------------------------------------------------------------
Extract-max loop (n-1 times) runs in O(n log n)
------------------------------------------------------------
Each iteration (while heap size m >= 2):
  1) swap A[0] with A[m-1]
  2) reduce heap size to m-1
  3) sift-down from root
Cost of one sift-down when heap has size m:
  Height is floor(log2 m) => cost O(log m).

Total over m = n, n-1, ..., 2:
  T_extract(n) = sum_{m=2..n} O(log m)
               = O( sum_{m=2..n} log m )
               = O( log( 2*3*...*n ) )
               = O( log(n!) )
Using Stirling: log(n!) = Theta(n log n), hence
  T_extract(n) = O(n log n).

(Quick bound: each log m <= log n, so sum <= (n-1)*log n = O(n log n).)

------------------------------------------------------------
Big picture (Heapsort total)
------------------------------------------------------------
Build-heap:  O(n)
Extract-max: O(n log n)
Total:       O(n) + O(n log n) = O(n log n)
*/
