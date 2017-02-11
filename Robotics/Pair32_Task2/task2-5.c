#include "simpletools.h"                     
#include "propeller.h"
#include <stdio.h>
#include "abdrive.h"

char currentPos = 'A'; // Starting Position of Robot.

void driveNolight(char start, char end) {
  // Using character operations to move robot.
    drive_goto(80 * (end - start), 80 * (end - start));
    currentPos = end;
 return; 
}  

void drive(char start, char end) {
  if (currentPos != start) {
    driveNolight(currentPos, start); // Move robot to correct Position with no light.
    currentPos = start;   
  } 

  // Cylinder is being moved with light on.
  high(26);
  pause(500);
  drive_goto(80 * (end - start), 80 * (end - start));
  currentPos = end;
  low(26);
  return;
}  

void towers(int num, char frompeg, char topeg, char leftOverPeg)
{
    if (num == 1) // A base case when there is either 1 disk to move, or Largest disk is in place.
    {
        printf("\n Move disk 1 from peg %c to peg %c", frompeg, topeg);
        return;
    }
    towers(num - 1, frompeg, leftOverPeg, topeg); // Recursive Call to change position of pegs, so destination peg becomes the unsued one.
    printf("\n Move disk %d from peg %c to peg %c", num, frompeg, topeg);
    drive(frompeg, topeg); // A call to move the robot from cureent peg to destination peg
    towers(num - 1, leftOverPeg, topeg, frompeg); // Another Recursive Call to change position of pegs, so Starting peg becomes unused one.
}

int main()
{
    int num; 
    char start,end, sideman;
    
    // Stores the number of Disks.
    printf("Enter the number of disks: ");
    scanf("%d", &num);
    puts("\n");
    
    // Stores Starting Position of Tower.
    printf("Start tower: ");
    scanf(" %c", &start);
    puts("\n");
    
    // Starts Ending Position of Tower.
    printf("End tower: ");
    scanf(" %c", &end);
    puts("\n");
    
    // Stores the unused tower.
    printf("Not used tower: ");
    scanf(" %c", &sideman);
    puts("\n");
 
    
    printf("The sequence of moves involved in the Tower of Hanoi are :\n");
    // A call to start re-arranging.
    towers(num, start, end, sideman);
    drive_goto(-26,25); // Finishing Move of the robot which is spinning.
    return 0;
}
