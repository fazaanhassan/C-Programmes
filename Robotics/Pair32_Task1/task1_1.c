/**
* This is the main Blank Simple C++ Project program file.
*/

#include <stdio.h>            // Recommended over iostream for saving space
#include <propeller.h>        // Propeller-specific functions
#include <simpletools.h>
#include <abdrive.h>


int main(){

// The 308 ticks represent 1m. 
// Change to 100 if on the stimulator as 308 is too big to represent.
int h = 100; 

for(int i = 1; i<=4; ++i) {

drive_goto(h,h);    
drive_goto(26,-25); // Rotate 90 degrees clockwise.

}
  return 0;
}
