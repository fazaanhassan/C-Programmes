#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"
#include <stdio.h>
#include <stdlib.h>

// Main Functions that will be called
void infaRed();
void deadEnd();
void checkBearing();
void deadEnd();
void goCorner(int x, int y);
void runCorner();
void priority();

// This rotates the the robot. c - ClockWise, ac - AntiClockWise
void c90();
void ac90();
void t180();

short int driveX = 122; // each wheel will travel 122 ticks. This gets it from 1 cell to another.
// initilises coordiantes with starting cell as (0,-1)
short int xCord = 0;
short int yCord = -1;
int bearing = 0;
unsigned short int cornerCounter = 0;

// InfaRed and Ping values are stored in the corresponding variables.
short unsigned int irLeft;
short unsigned int irRight;
short int pingDistance;

int main(void)
{
    int i = 0;
    drive_goto(10, 10); //Move from square (-1,0) to (0,0)


    /* Call functions to send robot to corners */
    goCorner(3, 0);
    goCorner(3, 3);
    goCorner(0, 3);
    goCorner(0, -1);

    if (cornerCounter == 4)
    { // Once it gets to last corner, rotate 180 degrees and flash light.
        t180();
        pause(1000);
        do
        {
            high(26);
            pause(200);
            low(26);
            pause(200);
            i++;
        } while (i != 3);
    } 
    runCorner();
    printf("Final (%d, %d) \n", xCord, yCord);

    return 0;
}

void goCorner(int x, int y)
{ //Makes robot go to corner using sensors.
    printf("Current Co-ord (%d, %d) \n", xCord, yCord);
    infaRed();
    printf("Please wait.. \n");
    printf("Current Sensor (%hu, %hu) \n", irLeft, irRight);
    pingDistance = ping_cm(8);
    printf("Sensor\t PD\t CO\t B \n");

    while (!(xCord == x && yCord == y))
    { // Right wall-following to get to each corner in the maze.

        if (irRight == 1)
            c90();
        else if (irLeft == 0 && irRight == 0 && pingDistance < 27)
        {
            t180();
        }
        else if (pingDistance < 27 && irRight == 0)
            ac90();
        drive_goto(driveX + 5, driveX + 5);

        printf("L%hu R%hu\t %d cm\t (%hi,%hi)\t %d \n", irLeft, irRight, pingDistance, xCord, yCord, bearing);
        checkBearing();

        infaRed();
        pingDistance = ping_cm(8);
    }
    cornerCounter++;
    if (!(x == 0 && y == -1))
        deadEnd();
    return;
}

void runCorner()
{ // Runs method to set up IR sensor and holds IR sensor value in variable. Calls checkBearing to check direction robot is facing.
    infaRed();
    printf("Run Corner_3 \n");
    printf("Current Sensor (%hu, %hu) \n", irLeft, irRight);
    pingDistance = ping_cm(8);
    printf("SN\t PD\t CO\t B \n");

    while (!(xCord == 3 && yCord == 3))
    {
        priority();

        printf("L%hu R%hu\t %d cm\t (%hi,%hi)\t %d \n", irLeft, irRight, pingDistance, xCord, yCord, bearing);
        checkBearing();
        infaRed();
        pingDistance = ping_cm(8);
    }
    return;
}

void checkBearing()
{ //Checks the direction the robot is facing
    if (bearing % 4 == 0)
        yCord++;
    else if (bearing % 4 == 1)
        xCord++;
    else if (bearing % 4 == 2)
        yCord--;
    else if (bearing % 4 == 3)
        xCord--;
}

void priority()
{ // Depending on the robots direction, it determines which way it needs to face in order to get to Corner 3 the quickest.
    print("%d \n", bearing % 4);

    // If wall on each side but clear ahead, go straight
    if (irRight == 0 && irLeft == 0 && pingDistance > 27)
        drive_goto(driveX + 5, driveX + 5);

    // If wall on the left and clear ahead, go straight. This gives UP priority to get to the top-left wall.
    else if (irLeft == 0 && pingDistance > 27)
        drive_goto(driveX + 5, driveX + 5);

    // If robot reaches dead end and cannot turn left or right, rotate 180 degrees:
    else if (irLeft == 0 && irRight == 0 && pingDistance < 27)
    {
        t180();
    }

    // If wall in front and on the right, turn left:
    else if (pingDistance < 27 && irRight == 0 && irLeft == 1)
    {
        ac90();
        drive_goto(driveX + 5, driveX + 5);
    }

    // If wall in front and on the left, turn right:
    else if (pingDistance < 27 && irLeft == 0 && irRight == 1)
    {
        c90();
        drive_goto(driveX + 5, driveX + 5);
    }

    else if (bearing % 4 == 0)
    { // If facing Up
        if (irLeft == 1 && pingDistance > 27)
            drive_goto(driveX + 5, driveX + 5);
        else if (irRight == 1)
        {
            c90();
            drive_goto(driveX + 5, driveX + 5);
        }
    }
    else if (bearing % 4 == 1)
    { // If facing Right
        if (irLeft == 1 && irRight == 0 && pingDistance > 27)
        {
            ac90();
            drive_goto(driveX + 5, driveX + 5);
        }
        else if (pingDistance < 27 && irLeft == 1)
        {
            ac90();
            drive_goto(driveX + 5, driveX + 5);
        }
    }
    else if (bearing % 4 == 3)
    { // If facing left
        if (irLeft == 0 && irRight == 1 && pingDistance > 27)
        {
            c90();
            drive_goto(driveX + 5, driveX + 5);
        }
    }
}

void t180()
{ //Rotate 180 degrees
    bearing += 10;
    drive_goto(-51, 51);
}

void c90()
{ //Rotate 90 degrees clockwise
    bearing += 9;
    drive_goto(26, -25);
}

void ac90()
{ //Rotate 90 degrees anti-clockwise
    bearing -= 1;
    drive_goto(-26, 25);
}

void infaRed()
{ // Sets up IR sensor to detect distance in front

    irLeft = 0;
    irRight = 0;
    freqout(11, 1, 38000); // Left IR LED light
    irLeft = input(10);    // Check left IR detector

    freqout(1, 1, 38000); // Repeat for right detector
    irRight = input(2);

    pause(300);

    return;
}

void deadEnd()
{ // If robot hits a dead end and walls on both sides then turn around

    if (irLeft == 0 && irRight == 0 && pingDistance < 28)
    {
        t180();
    }
}