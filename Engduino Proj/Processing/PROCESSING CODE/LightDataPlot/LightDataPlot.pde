import processing.serial.*;         

Serial myPort;  

// Global Variables
float xPos = 40;                 // Starting X value point for plotting the data                
float InComingData = 0;
PFont title;
PFont Xtitle;
PFont Ytitle;

void setup () {
  size(640, 480);                               // set the window size (width,height)
  
  myPort = new Serial(this,"/dev/cu.usbmodem1421", 9600); // Change port name inside speechmark to your machines Portname
  myPort.bufferUntil('\n');                     // don't generate a serialEvent() unless you get a newline character:           
  background(0);                                // set inital background color:
  
  // Create name of title, Font and Size
  title = createFont("Arial",16,true);          
  Xtitle = createFont("Arial", 12,true);
}

void draw () {
    
  // Main title
  textFont(title,16);                            // initilises 'title' which is declared in void setup
  fill(255);                                    // Specify font color 
  textAlign(CENTER);                           // Aligns the Text on the screen
  text("Light Measurer Graph",width/2,15);    // Displays the Text at half of screen size
  
  // X axis title
  textFont(Xtitle, 12);
  fill(#32CD32);
  textAlign(CENTER); 
  text("Time (Seconds)",width/2,470);
  
  // Y axis title
  float x = 15;
  float y = 220;
  textAlign(CENTER,BOTTOM);
  pushMatrix();
  translate(x,y);
  rotate(-HALF_PI);
  text("Light Intesity (Lux)",0,0);
  popMatrix();
  
  // light line  
  strokeWeight(4);      // Indicates the size of each stroke-line
  stroke(175);          //  Indicates the color of the line            
  line(40,height,40,0);
  
  // Time line
  strokeWeight(4); 
  stroke(175);
  line(0, 430, 640, 430);
  
  // Calls  a function to plot values on the Y and X axis
  datavalues();

  // Data  line:
  strokeWeight(4);
  stroke(#791F33);                               // Color of he data line
  line(xPos, height-53, xPos, height - InComingData); // Restricts where the dataline starts and ends

  // If at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 40;          //Indicates the X value starting point of the real time data.
    background(0);
  } else {
    
    xPos = xPos + 1;  // increment the horizontal position:
  }
}


void serialEvent (Serial myPort) {
  
  String inString = myPort.readStringUntil('\n');// Takes in the Data from the port:

  if (inString != null) {
    inString = trim(inString);                  // This trims off any whitespace:
    InComingData = float(inString)/2;                 // This converts the data to an float and divides incoming data by 2 to give a more accurate measurement.
    println(InComingData);                            // Prints data onto screen
    InComingData = map(InComingData, 0, 1023, 49, height);  //Starts the data plotting
  }
}

void datavalues() {
  
  // Y axis Values
  strokeWeight(1);
  stroke(175);
  line(35, 390, 40, 390) ;
  text("1",30,390);
  
  strokeWeight(1);
  stroke(175);
  line(35, 350, 40, 350) ;
  text("2",30,350);
  
  strokeWeight(1);
  stroke(175);
  line(35, 310, 40, 310) ;
  text("3",30,310);
  
  strokeWeight(1);
  stroke(175);
  line(35, 270, 40, 270) ;
  text("4",30,270);
  
  strokeWeight(1);
  stroke(175);
  line(35, 230, 40, 230) ;
  text("5",30,230);
  
  strokeWeight(1);
  stroke(175);
  line(35, 190, 40, 190) ;
  text("6",30,190);
  
  strokeWeight(1);
  stroke(175);
  line(35, 150, 40, 150) ;
  text("7",30,150);
  
  strokeWeight(1);
  stroke(175);
  line(35, 110, 40, 110) ;
  text("8",30,110);
  
  strokeWeight(1);
  stroke(175);
  line(35, 70, 40, 70) ;
  text("9",30,70);
  
  // X axis Values
  text("0",50,460);
 
  strokeWeight(1); 
  stroke(175);
  line(90, 430, 90, 440);
  text("1", 90, 460);
  
  strokeWeight(1); 
  stroke(175);
  line(140, 430, 140, 440);
  text("2", 140, 460);
  
  strokeWeight(1); 
  stroke(175);
  line(190, 430, 190, 440);
  text("3", 190, 460);
  
  strokeWeight(1); 
  stroke(175);
  line(240, 430, 240, 440);
  text("4", 240, 460);
  
  strokeWeight(1); 
  stroke(175);
  line(290, 430, 290, 440);
  text("5", 290, 460);
  
  strokeWeight(1); 
  stroke(175);
  line(340, 430, 340, 440);
  text("6", 340, 460);
  
  strokeWeight(1); 
  stroke(175);
  line(390, 430, 390, 440);
  text("7", 390, 460);
  
  strokeWeight(1); 
  stroke(175);
  line(440, 430, 440, 440);
  text("8", 440, 460);
  
  strokeWeight(1); 
  stroke(175);
  line(490, 430, 490, 440);
  text("9", 490, 460);
  
  strokeWeight(1); 
  stroke(175);
  line(540, 430, 540, 440);
  text("10", 540, 460);
  
  strokeWeight(1); 
  stroke(175);
  line(590, 430, 590, 440);
  text("11", 590, 460);
   
}