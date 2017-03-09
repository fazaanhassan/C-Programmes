#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

// The use of the PI function to calcualte dead reckoning.
#ifndef M_PI
#define M_PI acos(-1.0)
#endif
#define COLUMNS 2

// A struct is defined Below with a size of 200.
#define MAXSIZE 200
struct stack
{
    int stk[MAXSIZE];
    int top;
};
typedef struct stack STACK;
STACK s;


int back = 0; // This variable is used int he while loop when coming back.
// Once alls speeds have been popped the while loop then exits.

int *L,*R;                 // Pointers to the the number of ticks travelled (Co-Ordinates)
double *angle;            // The angle moved from the start
float BotRadius = 105.8;
short signed int irLeft, irRight;   // Distance from Left and Right wall in terms of IR units
int k = 0;                         // To terminate the main while loop.
int speedBack;
double average;           // Average distance the robot has moved
double displacementAngle;

int checkObs(int CheckDistance);
void InfaRed();
void DeadEnd(int wantedDistance);
void deadReckon();
void push(int change);
int  pop(void);

float totalX = 0;
float totalY = 0;
float angularDisplacement = 0;
float w = 105.8;
int previousLeft;
int previousRight;

int main()
{
    L = (int*)malloc(1*sizeof(int));
    R = (int*)malloc(1*sizeof(int));
    drive_getTicks(L, R);
    
    printf("Number of Ticks at Start = %d %d \n", *L, *R);
    
    short signed int error=0;
    short signed int previousError=0;
    short signed int speedDiff;
    short signed int startSpeed=30;
    
    low(26);
    low(27);
    
    while (k==0)
    {
        InfaRed();
        
        error=irLeft-irRight;
        speedDiff=error*3;
        
        if (speedDiff>10) speedDiff=10;
        if (speedDiff<-10) speedDiff=-10;
        
        // If error is between this, just travell normally
        if (error<=1 && error>=-1) {
            drive_speed(startSpeed,startSpeed);
            push(0);
        }
        else if (error>1) { // Closer to right, therefore turn left
            drive_speed(startSpeed,startSpeed+speedDiff + 2);
            push(speedDiff + 2);
        }
        else if (error<-1) { // Closer to left, therefore turn right
            drive_speed((startSpeed-speedDiff) + 2,startSpeed);
            push(speedDiff - 2);
        }
        if(k==0)DeadEnd(20); // If deadend is found then exit the main loop and come back
  drive_getTicks(L,R);
  float leftDist = (*L - previousLeft) * 3.25;
  float rightDist = (*R - previousRight) * 3.25;
  float centreDist=(leftDist+rightDist)/2;
  previousLeft = *L;
  previousRight = *R;
  float angleRotated= 90 - ((180 - ((((*L - *R) * 3.25) / w) * 180/M_PI)) / 2);
  angleRotated = angleRotated * (M_PI/180);
  float changeY=(centreDist*sin(angleRotated));
  totalY+=changeY;
  float changeX=(centreDist*cos(angleRotated));
  totalX+=changeX;
  
    }
    
   /* deadReckon();
    
    average = ((*L + *R) / 2) * 3.25 * 0.1;
    printf("The Rotational angle moved is: %lf degrees \n",*angle);
    printf("Average distance is: %lf cm \n", average);
    printf("The robot has Moved %lf cm at an displacement Angle of %lf degrees \n", average, displacementAngle);
    printf("The Displacement angle is: %lf \n", displacementAngle); */
    
    /*
     free(L);
     free(R);
     free(angle);
     */
    printf("X distance %f mm. Y distance %f mm. \n",totalX,totalY);
    angularDisplacement = atan2(totalY, totalX) * (180/M_PI);
    printf("Angular Displacement is %f degrees \n", angularDisplacement);
    printf("Resultant displacement is %f mm \n", sqrt((totalY*totalY) + (totalX*totalX)));
    
    drive_goto(51,-51);
    pause(500);
    
    /* ALL SENSORS ARE NOW TURNED OF! */
    while(back == 0) {
        speedBack = pop();
        pause(135); // 2nd last map- 135, turn map - 140, both work with 140 to, 145 - 2nd map
        if (speedBack >= -3 && speedBack <= 3) drive_speed(startSpeed,startSpeed);
        else if (speedBack > 3) drive_speed(startSpeed + speedBack,startSpeed);
        else if (speedBack < -3) drive_speed(startSpeed, startSpeed - speedBack);
    }
    return 0;
}

// Calculates the angle travelled from the inital position
void deadReckon() {
    
    displacementAngle = (atan2((*L - *R) * 3.25, BotRadius)) * 180/M_PI;
    angle = (double*)malloc(1 * 8);
    *angle = 90 - ((180 - ((((*L - *R) * 3.25) / BotRadius) * 180/M_PI)) / 2); // Gives the angle the robot has travelled.
    return ;
    
}

void InfaRed() {
    
    irLeft = 0;
    irRight = 0;
    
    for(int dacVal = 0; dacVal < 256; dacVal += 8)
    {
        dac_ctr(26, 0, dacVal);
        freqout(11, 1, 38000);
        irLeft += input(10);
        
        dac_ctr(27, 1, dacVal);
        freqout(1, 1, 38000);
        irRight += input(2);
    }
    return ;
    
}

// Used to check if the robot has reached the deadend. Uses the sensors to determine this.
void DeadEnd(int wantedDistance) {
    
    InfaRed();
    int currentDistance;
    currentDistance = ping_cm(8);
    if(wantedDistance > currentDistance && irRight < 18 && irLeft < 18) {
        drive_speed(0,0);
        pause(300);
        drive_getTicks(L, R);
        // drive_goto(-31,-31);
        //pause(300);
        printf("Co-ordiantes of Ticks (%d, %d) \n", *L, *R);
        printf("DeadEnd: Left irSensor = %d Right irSensor = %d \n", irLeft, irRight);
        k++;
    }
    return ;
    
}

// pushes distance onto the stack
void push (int change)
{
    
    if (s.top == (MAXSIZE - 1))
    {
        printf ("Stack is Full\n");
        return;
    }
    else
    {
        s.top = s.top + 1;
        s.stk[s.top] = change;
    }
    return;
}

/*  Function to delete current speed change from the stack */
int pop ()
{
    int change;
    if (s.top == - 1)
    {
        printf ("Stack is Empty\n");
        back++;
        return (s.top);
    }
    else
    {
        change = s.stk[s.top];
        printf ("poped element is = %d \n", s.stk[s.top]);
        s.top = s.top - 1;
        
    }
    return change;
}



