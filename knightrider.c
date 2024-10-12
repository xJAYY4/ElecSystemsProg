// Design a software to produce a knight rider effect on an array of 8 lights connected to Port B.
// The program will read in a number which will determine the speed that the lit LED will move.
// The program repeats for two cycles before asking for a new speed.

#include <stdio.h>

#define DELAY_OUTER 150000  // Define OUTER Loop delay constant
#define DELAY_INNER 100     // Define INNER Loop delay constant

// Function Declarations
void print_portB(unsigned char portB);  // Function to print the binary representation of portB
void knight_rider(int speed);           // Function to implement the Knight Rider effect
void delay(int speed);                  // Function that adds a delay based on speed

int main() {
    int speed;   // Speed for LED movement

    //Infinite Loop to prompt speed
    while (1) {
        printf("Enter the speed (in milliseconds) for the LED movement: ");
        scanf("%d", &speed);
        
        // Start the Knight Rider effect with user-defined speed
        knight_rider(speed);   
    }
    return 0;
}

// Function to print the binary representation of the current state of portB (LEDs)
void print_portB(unsigned char portB) {
    int i;
    //Iterate through each bit 7 down to 0
    for (i = 7; i >= 0; i--) {
        printf("%d", (portB >> i) & 1); // Print each bit of portB
    }
    printf("\n");
}

// Function to implement the Knight Rider effect
void knight_rider(int speed) {
    unsigned char portB = 0x01; // Start with LED on the far left
    int cycle, i, direction = 1;
    
    // Run two complete back-and-forth cycles
    for (cycle = 0; cycle < 4; cycle++) {      // Total of 4 half-cycles
        
        // Move the LED across the display
        for (i = 0; i < 7; i++) {
            print_portB(portB);     // Display the current state of LEDs
            delay(speed);
            
            // Shift LED position based on the current direction
            if (direction == 1) {
                portB <<= 1;    // Shift LED to the right
            } else {
                portB >>= 1;    // Shift LED to the left
            }
        }
        
        // Change direction after reaching the end
        direction = -direction;
    }
}

// Delay function using nested loops
void delay(speed){
    int i, j;
    for (i = 0; i < DELAY_OUTER; i++) {
        for (j = 0; j < DELAY_INNER; j++);  // Inner loop for additional delay
    }
}
