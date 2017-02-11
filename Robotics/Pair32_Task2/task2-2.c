#include "simpletools.h"
#include "propeller.h"
#include "abdrive.h"
#include <stdio.h>                     

int array[100];


// This function is used to print each iteration of the sorting algorithm.
void printArray(int n){
  for (int i=0; i<n; i++){
    printf("%d", array[i]);
    printf(", ");
  }
  printf("\n");
}
 

int main()
{
  int n, c, d, swap;
 
  printf("Enter number of elements\n");
  scanf("%d", &n); // Stores the total number of elements needing sorting.

  printf("Enter %d integers\n", n);
 
  for (c = 0; c < n; c++) { // User enters in integers one by one which are stored in an array
    scanf("%d", &array[c]);
  }
  // The current entered numbers are printed
  printArray(n);


  // Iterates through the array of stored numbers
  for (c = 0 ; c < ( n - 1 ); c++)
  {
    // Goes through the unordered list. Everytime it enteres this loop, it means last number is in place.
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (array[d] > array[d+1]) /* For decreasing order use < */
      {
        // Swaps the first two numbers if one is smaller then the other.
        // The swap is a temporary variable which allows this to happen.
        swap       = array[d];
        array[d]   = array[d+1];
        array[d+1] = swap;
	      printArray(n); // Calls the function to print each pass
      }
    }
    
  }
 

  printf("Sorted list in ascending order:\n");
  // Prints out numbers in ascending order
  for ( c = 0 ; c < n ; c++ )
     printf("%d\n", array[c]);
 
  return 0;
}