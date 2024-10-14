// Design a C Program to operate a simple climate control system for a car. 
// When the program starts, read in the threshold temperature which will be considered too hot.
// If the temperature is too hot (bigger than the first number read in), activate the fan connected to Port B Bit 5.
// If the temperature is too low, a sensor connected to Port B Bit 7 produces a high input, which intern results in the heater being activated (Port B Bit 5). 

#include <stdio.h>
#include <stdlib.h>

// Delay constants
#define DELAY_OUTER 1000000     // OUTER Loop delay constant
#define DELAY_INNER 13000       // INNER Loop delay constant

// Bit definitions for Port B
#define PORT_B_BIT_4 0x10       // Bit 4 for Heater (0b00010000)
#define PORT_B_BIT_5 0x20       // Bit 5 for Fan (0b00100000)
#define PORT_B_BIT_7 0x80       // Bit 7 for Sensor (0b10000000)

#define HEATER_THRESHOLD 10      // Threshold for low temperature

// Function Declarations
int readInteger(const char *prompt);                                            // Read an integer from user input with error checking
void activateFan(int *portB, int currentTemperature, int thresholdTemperature); // Activate/Deactivate fan based on temperature
void activateHeater(int *portB, int sensorStatus);                              // Activate/Deactivate heater based on temperature
void printPortBBinary(int portB);                                               // Print Port B's binary state
void delay();                                                                   // Delay to simulate heating or cooling


int main() {
    int currentTemperature, thresholdTemperature;   // Variable to hold the current temperature and threshold Temperature
    int portB = 0;                                  // Simulated Port B

    // Read the threshold temperature from user input
    do {
        thresholdTemperature = readInteger("Enter the threshold temperature (C): ");
        if (thresholdTemperature <= HEATER_THRESHOLD) {    // Check if thresholdTemperature is less than HEATER_THRESHOLD 
            printf("Threshold temperature cannot be lower than the heater threshold (%d C).\n", HEATER_THRESHOLD);
        }
    } while (thresholdTemperature <= HEATER_THRESHOLD);

    while (1) {
        // Read the current temperature from user input
        currentTemperature = readInteger("\nEnter the current temperature (C): ");

        // Activate or deactivate the fan based on the temperature
        activateFan(&portB, currentTemperature, thresholdTemperature);
        
        // Simulating sensor input for heater control
        if (currentTemperature < HEATER_THRESHOLD) {
            portB |= PORT_B_BIT_7;  // Simulate sensor high
        } else {
            portB &= ~PORT_B_BIT_7; // Simulate sensor low
        }

        // Activate or deactivate the heater based on the temperature
        activateHeater(&portB, (portB & PORT_B_BIT_7) != 0);

        // Print the current state of Port B in binary
        printPortBBinary(portB);

        // Wait to simulate heating or cooling
        delay();
    }
    return 0;
}


// Function to display the current state of Port B in binary
void printPortBBinary(int portB) {
    printf("Current state of Port B: ");
    int i;
    for (i = 7; i >= 0; i--) {
        printf("%d", (portB >> i) & 1);     // Shift and mask to get each bit
    }
    printf(" (0x%02X)\n", portB);           // Display in hexadecimal format as well
}


// Function to activate/deactivate the fan based on temperature
void activateFan(int *portB, int currentTemperature, int thresholdTemperature) {
    if (currentTemperature > thresholdTemperature) {
        *portB |= PORT_B_BIT_5;     // Set bit 5 high (activate fan)
        printf("Fan activated\n");
    } else {
        *portB &= ~PORT_B_BIT_5;    // Set bit 5 low (deactivate fan)
        printf("Fan deactivated\n");
    }
}


// Function to activate/deactivate the heater based on sensor status
void activateHeater(int *portB, int sensorStatus) {
    if (sensorStatus) {
        *portB |= PORT_B_BIT_4;     // Set bit 4 high (activate heater)
        *portB |= PORT_B_BIT_7;     // Set bit 7 high (indicating sensor is active)
        printf("Heater activated\n");
    } else {
        *portB &= ~PORT_B_BIT_4;    // Set bit 4 low (deactivate heater)
        printf("Heater deactivated\n");
    }
}


// Delay function using nested loops
void delay() {
    int i, j;                               // Loop variables for outer and inner loops
    for (i = 0; i < DELAY_OUTER; i++) {
        for (j = 0; j < DELAY_INNER; j++);  // Inner loop for additional delay (no operation)
    }
}


// Function to read an integer from user input with error checking
int readInteger(const char *prompt) {
    int value;
    while (1) {
        printf("%s", prompt); // Prompt the user for input

        // Attempt to read an integer directly
        if (scanf("%d", &value) == 1) {
            // Successfully read an integer, now check for additional characters
            char c;
            
            // Clear any remaining characters in the input buffer
            if (scanf("%c", &c) == 1 && c != '\n') {
                // If there are more characters after the integer
                printf("Invalid input. Please enter a valid integer.\n");
                while (getchar() != '\n'); // Discard the rest of the line
            } else {
                return value; // Return the valid integer if no extra characters
            }
        } else {
            printf("Invalid input. Please enter a valid integer.\n"); // Error message
            // Clear invalid input
            while (getchar() != '\n'); // Discard the rest of the line
        }
    }
}
