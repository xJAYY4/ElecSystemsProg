#include <stdio.h>
#include <unistd.h>  // for sleep() function

// Function to print the binary representation of a variable
void print_lights(unsigned char lights) {
    // Print only the lower 5 bits
    int i;
    for (i = 7; i >= 0; i--) {
        if (i < 5) {
            printf("%d", (lights >> i) & 1);
        }
    }
    printf("\n");
}

int main() {
    unsigned char lights = 0;  // This will store the state of the lights
    char start_signal;
    int i;
    
    // Wait for the user to press 'S'
    printf("Press 'S' to start the race sequence: ");
    scanf(" %c", &start_signal);
    
    if (start_signal == 'S' || start_signal == 's') {
        // Turn on each light with a 1-second delay
        for (i = 0; i < 5; i++) {
            lights |= (1 << i);  // Set the ith bit to 1
            print_lights(lights); // Print the current state of lights
            sleep(1);  // Wait for 1 second
        }
        
        // Wait 1 more second before turning off all lights
        sleep(1);
        printf("Start of the race! Lights off.\n");
        
        // Turn off all lights (set all lower 5 bits to 0)
        lights = 0;
        print_lights(lights);  // Print the current state of lights (all off)
    } else {
        printf("Invalid input. Please press 'S' to start.\n");
    }
    
    return 0;
}
