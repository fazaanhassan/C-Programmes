// Dimensions of the hanlde
handle_radius=10;    
handle_height=100;  
handle_width=50;   

// Dimesions of the base
base_width=95;        
base_depth=80;       
base_thickness=10;  // Can also be read as the height of the base

text_text="Engduino Stand";  // The text that will be on the base
textscale=1;                // The size of the text
// Position of text in the axis relative to the base.
textposition_x=-49;        
textposition_y=-30; 
textposition_z=-1;

Socket_Height = 25;

// Exucute base first then handle and finally postion of USB socket.
base ();                    // First Layer
additonalbases();          // Second, Third and Fourth layers.
handle();
PositionOfUsb();

// Creates the base (Cube takeaway cylinder) whilst carving out the letters of 'Engduno Stand'
module base () 
{
    difference() { 
        translate([0,0,base_thickness/2])
            minkowski(){
                cube([base_width,base_depth,base_thickness],center=true); 
                cylinder(r=5,h=1);
            }
    
        translate([textposition_x,textposition_y,base_thickness+textposition_z]) // Positioning of the text
        linear_extrude(3) // The depth of letters in the base
        text(text_text);
    }
}

// Creates 3 more layers ontop of the first main base
module additonalbases() {
translate([-10,-10, 3]) 
cube(20);          // Creates the 4th Layer (counting from the bottom)

translate([-12.5,-12.5,15])
cube([25,25,5]);        // Creates 3rd Layer

difference () {
cube(30,center=true);
    translate([-15,-15,-25])
    cube(30);           // Creates 2nd Layer
}
}

// Creation of the handle. ( handle = Circle tube - cuboid - 2 cylinders )
module handle()
{
    difference(){
        // This creates a Circular tube postioned in the center
        translate([0,20,handle_height])
        rotate([90,0,0])
        rotate_extrude(angle=360,convexity = 10,$fn=120)
            translate([handle_width, 20, 10])
                circle(r = handle_radius,$fn=120); 
       // This creates a cuboid      
    translate([ -handle_width-handle_radius,
                -handle_radius,    
                0+handle_height-handle_width*2
        ])
        cube([(handle_width+handle_radius)*2,handle_radius*2,handle_width*2]);
    }
    
     // This Section creates 2 cylinders
    translate([-(handle_width),0,0]) // Once cylinder created in the negative X axis
    rotate([0,0,0])
        cylinder(r=handle_radius,h=handle_height,$fn=120);

    translate([(handle_width),0,0]) // Second cylinder created in the positive X axis
    rotate([0,0,0])
        cylinder(r=handle_radius,h=handle_height,$fn=120);
}

// Creates the inner Socket by taking a smaller cube from a larger cube
module Socket_For_USB() {

  difference() {
      cube(size = [15,8,15]);
      translate([1.25, 1.5, 0]) 
      cube(size = [12.5,5,Socket_Height]);
  }
}

// This rotates the socket in the middle and cuts of any excess conntected to it.
module USBAngle() {
  difference() { 
      rotate(a=[0,0,0])
      Socket_For_USB(); // Uses the current socket created in the module above.
      translate([0,0,-30])
      cube(size=[30, 10, 30]);
  }
}

// Positions the socket in the middle. Just above the base.
module PositionOfUsb() {
    translate([-7.5, -3.5, 20])
    USBAngle(15);
}


    

