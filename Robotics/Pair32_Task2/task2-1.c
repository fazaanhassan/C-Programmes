#include "simpletools.h"
#include "propeller.h"
#include "abdrive.h"
#include <stdio.h>                     

int array[100];

int main()
{
  int n, c, d, swap;
 
  printf("Enter number of elements\n");
  scanf("%d", &n);             // Stores the total number of elements needing sorting.

  printf("Enter %d integers\n", n);
 
  for (c = 0; c < n; c++) { // User enters in integers one by one
    scanf("%d", &array[c]);
  }

        
  for (c = 0 ; c < ( n - 1 ); c++)     // Iterates through the array of selected numbers
  {
    
    for (d = 0 ; d < n - c - 1; d++) // Goes through unsorted array of numbers
    {
      if (array[d] > array[d+1]) /* For decreasing order use < */
      {
        // Swaps the first two numbers if one is smaller then the other.
        // The swap is a temporary variable which allows this to happen.
        swap       = array[d];
        array[d]   = array[d+1];
        array[d+1] = swap;
      }
    }
    
  }

 
  printf("Sorted list in ascending order:\n");
   // Prints out numbers in ascending order

  for ( c = 0 ; c < n ; c++ )
     printf("%d\n", array[c]);
 
  return 0;
}