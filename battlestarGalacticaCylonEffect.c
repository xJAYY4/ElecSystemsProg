#include <stdio.h>

#define DELAY_OUTER 150000      // Define OUTER Loop delay constant
#define DELAY_INNER 2000        // Define INNER Loop delay constant

// Function Declarations
void display_binary(unsigned char portB);   // Display the current state of Port B in binary
void delay(int speed);                      // Function to create a time delay based on user input

int main() {
    unsigned char portB = 0x01;  // Start with the first light ON (bit 0)
    int speed;

    // Prompt the user for the speed at which the light moves
    printf("Enter the speed (in milliseconds) for the light movement: ");
    
    // Catch for invalid user inputs
    while (scanf("%d", &speed) != 1 || speed <= 0) {
        printf("Invalid input. Please enter a positive integer for speed: ");
        // Clear the input buffer if the input is invalid
        while (getchar() != '\n');  // Clear invalid input
    }

    // Infinite loop to simulate the Cylon light effect
    while (1) {
        int i;
        // Move light from left to right (bit 0 to bit 7)
        for (i = 0; i < 8; i++) {      // Loop through bits 0 to 7
            portB = (1 << i);          // Shift 1 to the current bit position
            display_binary(portB);     // Display the current state of Port B
            delay(speed);              // Delay for the user-defined speed
        }

        // Move light from right to left (bit 7 to bit 0)
        for (i = 6; i >= 0; i--) {      // Loop through bits 6 to 0
            portB = (1 << i);           // Shift 1 to the current bit position
            display_binary(portB);      // Display the current state of Port B
            delay(speed);               // Delay for the user-defined speed
        }
    }
    return 0; // This line is unreachable due to the infinite loop
}

// Function to display the current state of Port B in binary
void display_binary(unsigned char portB) {
    int i;
    for (i = 7; i >= 0; i--) {
        printf("%d", (portB >> i) & 1);  // Shift and mask to print each bit
    }
    printf("\n");
}

// Delay function using nested loops
void delay(int speed){
    int i, j;
    // Outer loop for overall delay based on DELAY_OUTER constant
    for (i = 0; i < DELAY_OUTER; i++) {
        for (j = 0; j < DELAY_INNER; j++);  // Inner loop for additional delay
    }
}
