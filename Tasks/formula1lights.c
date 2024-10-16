// Design a software to operate the starting lights of a Formula 1 race.
// When the user presses 'S' or 's', the five red lights will appear in sequence at one-second intervals.
// The lights correspond to the five lower bits of the variable.
// Setting the bit turns on the light. (e.g. 00000011, simulates the first two lights being on).
// The red lights are extinguished to signal the start of the race.

#include <stdio.h>

#define DELAY_OUTER 150000  // Define OUTER Loop delay constant
#define DELAY_INNER 100     // Define INNER Loop delay constant

// Function Declarations
void print_lights(unsigned char lights);    // Function to print the binary representation of the lights state
void delay();                               // Function that adds a delay to the countdown

int main() {
    // Declare Variables
    unsigned char lights = 0;   // Stores the state of the lights
    char start_signal;          // Holds user input for starting the race
    int i;                      // Loop counter
    
    // Prompt user to press 'S' or 's'
    printf("Press 'S' to start the race sequence: ");
    scanf(" %c", &start_signal);    // Read user input
    
    // Start race if valid input
    if (start_signal == 'S' || start_signal == 's') {
        
        // Turn on lights with delay
        for (i = 0; i < 5; i++) {   
            lights |= (1 << i);     // Set the i'th light
            print_lights(lights);   // Display current lights
            delay();                // Wait for 1 second
        }
        
        // Additional wait before starting the race
        delay();
        printf("Start of the race! Lights off.\n");
        
        // Turn off all lights
        lights = 0;
        print_lights(lights);   // Show all lights off
    } else {
        printf("Invalid input. Please press 'S' to start.\n");
    }
    
    return 0;
}

//Function to print the binary representation of a lights
void print_lights(unsigned char lights) {
    // Print only the lower 5 bits
    int i;
    for (i = 7; i >= 0; i--) {  
        if (i < 5) {            
            printf("%d", (lights >> i) & 1);    // Extract and print bit value
        }
    }
    printf("\n");
}


// Delay function using nested loops
void delay(){
    int i, j;
    for (i = 0; i < DELAY_OUTER; i++) {
        for (j = 0; j < DELAY_INNER; j++);  // Inner loop for additional delay
    }
}
