
#include <stdio.h>            
#include <propeller.h>        
#include <simpletools.h>
#include <abdrive.h>


int main(){
  drive_goto(50, 50); // Travel a distance of 50 ticks and then stop
  return 0;
}
