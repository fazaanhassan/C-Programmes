#include "abdrive.h"
#include "simpletext.h"
#include "simpletools.h"
#ifdef BUILDING_IN_SIMULATOR
#include "simulator.h"
#endif


int h = 100;    //Number of Ticks to Travel. 32.5cm
int w = 50;    // 16.25cm to travel.
int rotation; // store the number of ticks for each wheel to travel
int gap = 20;

void rotate(int r) {
#ifdef BUILDING_IN_SIMULATOR
    simulator_stopSmokeTrail();
#endif
 rotation = r * 0.284;
 drive_goto(rotation, (-1) * rotation); // turns around the centre point of radious 0
}  

// Go to the left of the map to get some space before drawing
void goLeftMap() {

  drive_goto(-150,-150);
}

// Produce a gap between each character
void makeGap(int left, int right) {
#ifdef BUILDING_IN_SIMULATOR
    simulator_stopSmokeTrail();
#endif
  drive_goto(left, right);
}

// Go in a straightline     
void straight(int x, int y) {
#ifdef BUILDING_IN_SIMULATOR
    simulator_startNewSmokeTrail();
#endif
  drive_goto(x,y);
}

// Draw Letter 'A'
void drawA() {
    
    rotate(-90);
    straight(h,h);
    rotate(90);
    straight(w,w);
    rotate(90);
    straight(h,h);
    rotate(180);
    straight(w,w);
    rotate(-90);
    straight(w,w);
    rotate(180);
    straight(w,w);
    rotate(90);
    straight(w,w);
    rotate(-90);
}

// Draw Letter 'L'
void drawL() {
    
    rotate(-90);
    straight(h,h);
    rotate(180);
    straight(h,h);
    rotate(-90);
    straight(w,w);
  
}          

// Draw Letter 'I'
void drawI() {
  rotate(-90);
  straight(h,h);
  rotate(180);
  straight(h,h);
  rotate(-90);  
}

// Draw Letter 'K'
void drawK() {
  
  rotate(-90);
  straight(h,h);
  rotate(180);
  straight(w,w);
  rotate(-135);
  straight(w, w);
  rotate(180);
  straight(w, w);
  rotate(-90);
  straight(w, w);
  rotate(180);
  straight(w,w);
  rotate(-135);
    straight(w,w);
    rotate(-90);

}  

// Draw Letter 'E'
void drawE() {
  
  straight(w,w);
  rotate(180);
  straight(w,w);
  rotate(90);
  straight(h / 2, h / 2);
  rotate(90);
  straight(w,w);
  rotate(180);
  straight(w,w);
  rotate(90);
  straight(h / 2,h / 2);
  rotate(90);
  straight(w,w);
}

// Draw letter 'F'
void drawF() {
    
    rotate(-90);
    straight(w,w);
    rotate(90);
    straight(w,w);
    rotate(180);
    straight(w,w);
    rotate(90);
    straight(w,w);
    rotate(90);
    straight(w,w);
    rotate(180);
    straight(w,w);
    rotate(-90);
    straight(h,h);
    rotate(-90);
    straight(w,w);
    
    
}

// Draw Letter 'H'
void drawH() {
    
    rotate(-90);
    straight(h,h);
    rotate(180);
    straight(w,w);
    rotate(-90);
    straight(w,w);
    rotate(-90);
    straight(w,w);
    rotate(180);
    straight(h,h);
    rotate(-90);
    
}
  
int main() {
    
    char word[7];
    int start = 0;
    printf("Choose a word with letters ALIKEFH: \t");
    scanf("%7s", word);
    
    goLeftMap();     // Go to leftside of map for space

    for(start = 0; start < 7; start++) {
        
        switch(word[start]) {
             case 'A':
                drawA();
                makeGap(gap,gap);
                break;
                
              case 'L':
                drawL();
                makeGap(gap,gap);
                break;
                
              case 'I':
                drawI();
                makeGap(gap,gap);
                break;
                
              case 'K':
                drawK();
                makeGap(gap + 50,gap + 50);
                break;
                
              case 'E':
                drawE();
                makeGap(gap,gap);
                break;
                
              case 'F':
                drawF();
                makeGap(gap+50,gap+50);
                break;
                
              case 'H':
                drawH();
                makeGap(gap,gap);
                break;
                
            default:
                return 0;
        }
        
        
    }
    
  
 return 0;
}

  
  
