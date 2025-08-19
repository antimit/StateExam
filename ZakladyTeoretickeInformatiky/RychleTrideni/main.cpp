#include <iostream>
#include <vector>
using namespace std;



/* 
5. Rychlé třídění (QuickSort)

a) Popis algoritmu:
   - Choose a pivot element (here: the last element of the subarray).
   - Partition the subarray:
       all values < pivot go to the left,
       all values ≥ pivot go to the right,
       pivot is placed between them (in its final position).
   - Recursively sort the left and right parts.
   - Stop when a subarray has 0 or 1 element (already sorted).

   ASCII sketch:
   [ smaller ... | pivot | greater ... ]

b) Složitost (worst-case complexity):
   - Partition itself is O(n).
   - If pivot is always the smallest or largest element,
     splits are 0:(n-1), 0:(n-2), … → recursion depth = n.
   - Work: n + (n-1) + (n-2) + ... + 1 = O(n^2).
   - Space: O(n) in this degenerate case (recursion stack).

c) Průměrná složitost (average complexity, no derivation):
   - On average, pivot splits the array into ~halves.
   - Each level of recursion costs O(n).
   - Depth ≈ log n.
   - Total work = O(n log n).
   - Space = O(log n) average (recursion stack).
*/


int partiton(vector <int> &a, int low, int high)
{
    int pivot = high;

    int i = low -1;


    for(int j = low; j <= high -1; j++)
    {
        if(a[pivot] > a[j])
        {
            i++;
            swap(a[i],a[j]);
        }
    }

    swap(a[i+1],a[high]);

    return (i+1);
}


void QuickSort(vector<int> &a, int low, int high)
{
    if(low < high)
    {
        int pi = partiton(a,low,high);

        QuickSort(a,low,pi -1);

        QuickSort(a, pi+1,high);
    }
}


void print_array(vector<int> & a)
{
    int size = a.size();

    for(int i = 0; i < size; i++)
    {
        cout << a[i] << " ";
    }
    cout <<endl;
}

int main()
{
    vector<int>a = {8,4,2,9};

    cout << "Before sorting"<<std::endl;
    print_array(a);
    QuickSort(a,0,a.size()-1);
    cout << "After sorting"<<std::endl;
    print_array(a);
    return 0;
}


/* 
5. Rychlé třídění (QuickSort)

a) Popis algoritmu:
   - Vybereme pivot (v našem případě poslední prvek).
   - Provedeme partition: 
       všechny prvky < pivot → vlevo,
       všechny prvky ≥ pivot → vpravo,
       pivot se přesune na své finální místo.
   - Rekurzivně seřadíme levou i pravou část pole.
   - Rekurze končí, když má podpole 0 nebo 1 prvek.

   ASCII schéma (partition):
   [ ... < pivot ... | ... ≥ pivot ... | pivot ]
                         ↓ swap
   [ ... < pivot ... | pivot | ... ≥ pivot ... ]

b) Složitost:
   - Nejhorší případ: O(n²)
       (např. pokud pivot je vždy minimum nebo maximum).
   - Paměťová složitost: O(log n) průměrně (rekurzivní zásobník),
     až O(n) v nejhorším případě.

c) Průměrná složitost:
   - O(n log n)
   - Protože pivot většinou dělí pole přibližně na dvě poloviny
     a partition je O(n).
*/


/* 
Complexity of QuickSort

Worst case (O(n^2)):
- Each partition scans the whole subarray → O(m) for size m.
- If pivot is always the smallest/largest, the split is 0:(n-1).
- Recurrence: T(n) = T(n-1) + O(n).
- Expanding: T(n) = n + (n-1) + (n-2) + ... + 1
            = n(n+1)/2
            = O(n^2).

Average case (O(n log n)):
- Pivot usually splits array into ~halves.
- Each level of recursion costs O(n) total.
- Depth of recursion ≈ log n.
- Total = O(n) * O(log n) = O(n log n).

Space complexity:
- In-place swaps, so no extra array needed.
- Only recursion stack:
   * O(log n) on average (balanced splits).
   * O(n) in worst case (completely unbalanced).
*/



/* 
Space complexity of QuickSort
-----------------------------

We pass the array by reference → no extra array memory.

BUT: each recursive call uses a stack frame
      (stores: return address, low, high, i, j, pivot) → O(1) per call.

Total extra space = recursion depth × O(1).

Case 1: Balanced splits (average) → depth ≈ log n
-------------------------------------------------
Example: n = 8

quickSort(0,7)
 ├── quickSort(0,3)
 │    └── quickSort(0,1)
 │         └── quickSort(0,0)   <- base case
 └── quickSort(4,7)
      └── quickSort(6,7)
           └── quickSort(7,7)   <- base case

Max depth ≈ log2(n) = 3.
=> Space = O(log n).


Case 2: Worst splits (pivot always min/max) → depth = n
-------------------------------------------------------
Example: n = 5, array already sorted, pivot = last element

quickSort(0,4)
 └── quickSort(0,3)
      └── quickSort(0,2)
           └── quickSort(0,1)
                └── quickSort(0,0)  <- base case

Depth = n = 5.
=> Space = O(n).


Summary:
--------
- Average (balanced):  O(log n)
- Worst (unbalanced): O(n)

Even though the array is the same (reference), 
the stack frames accumulate → that’s the extra space.
*/
