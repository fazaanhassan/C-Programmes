/**
* This is the main Blank Simple C++ Project program file.
*/

#include <stdio.h>            // Recommended over iostream for saving space
#include <propeller.h>        // Propeller-specific functions
#include <simpletools.h>
#include <abdrive.h>


int main(){
  
  drive_goto(102, -102); // Turn 360 degrees on the spot.
  return 0;
}
