#include <stdio.h>
#include <stdlib.h>

#define DELAY_OUTER 1000000     // OUTER Loop delay constant
#define DELAY_INNER 13000       // INNER Loop delay constant
#define PORT_B_BIT_4 0x10       // Bit 4 for Heater (0b00010000)
#define PORT_B_BIT_5 0x20       // Bit 5 for Fan (0b00100000)
#define PORT_B_BIT_7 0x80       // Bit 7 for Sensor (0b10000000)
#define HEATER_THRESHOLD 10     // Threshold for low temperature

// Function Declarations
void printPortBBinary(int portB);                                               // Print Port B's binary state
void activateFan(int *portB, int currentTemperature, int thresholdTemperature); // Activate/Deactivate fan based on temperature
void activateHeater(int *portB, int sensorStatus);                              // Activate/Deactivate heater based on temperature
void delay();                                                                   // Delay to simulate heating or cooling

int main() {
    int currentTemperature, thresholdTemperature; // Variable to hold the current temperature and threshold Temperature
    int portB = 0;                                // Simulated Port B

    // Read the threshold temperature from user input
    printf("Enter the threshold temperature (C): ");
    scanf("%d", &thresholdTemperature);

    while (1) {
        // Reads the current temperature from user input
        printf("\nEnter the current temperature (C): ");
        scanf("%d", &currentTemperature);

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