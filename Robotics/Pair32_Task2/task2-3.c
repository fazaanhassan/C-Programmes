#include "simpletools.h"
#include "propeller.h"
#include "abdrive.h"
#include <stdio.h>                     

void b(int x, int y);
void printArray(int n);

// Global Variables
int array[100];
int weelTicks = 50;

int main()
{
  int n, c, d, swap, gapsIdentified = 0, goBack = 0;
 
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

      gapsIdentified++; // Identifies the number of Gaps so the robot can travel to it.
      if (array[d] > array[d+1]) /* For decreasing order use < */
      {
        goBack = goBack + gapsIdentified ; // A counter to ensure robot can return back to the beginining. 
        b(gapsIdentified,gapsIdentified);
        // Swaps the first two numbers if one is smaller then the other.
        // The swap is a temporary variable which allows this to happen.
        swap       = array[d];
        array[d]   = array[d+1];
        array[d+1] = swap;
	      printArray(n); // Calls the function to print each pass
        gapsIdentified = 0;
      }
    }

    drive_goto(goBack * -weelTicks, goBack * -weelTicks);
    goBack = 0;
  }
 
  drive_goto((n/2) * weelTicks, (n/2) * weelTicks);
  drive_goto(-25,26);

  printf("Sorted list in ascending order:\n");
  // Prints out numbers in ascending order
  for ( c = 0 ; c < n ; c++ )
     printf("%d\n", array[c]);
 
  return 0;
}

void b(int x, int y) {

 drive_goto(x * weelTicks,y * weelTicks);
  high(26);                                   // Set P26 light on
  pause(300);                                // Wait 1/30 second
  low(26);                                  // Set P26 light off
  pause(300);                              // Wait another 1/30 second
}  

// This function is used to print each iteration of the sorting algorithm.
void printArray(int n) {
  for (int i=0; i<n; i++){
    printf("%d", array[i]);
    printf(", ");
  }
  printf("\n");
}