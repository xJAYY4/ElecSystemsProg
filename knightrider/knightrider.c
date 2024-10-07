#include <stdio.h>
#include <unistd.h>  // for sleep()

// Function to print the binary representation of portB
void print_portB(unsigned char portB) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (portB >> i) & 1);
    }
    printf("\n");
}

// Function to implement the Knight Rider effect
void knight_rider(int speed) {
    unsigned char portB = 0x01; // Initial LED on the far left (00000001)
    int direction = 1;          // 1 for right, -1 for left
    
    // Run two complete back-and-forth cycles
    for (int cycle = 0; cycle < 4; cycle++) {
        // Go from left to right or right to left depending on the direction
        for (int i = 0; i < 7; i++) {
            print_portB(portB); // Print current state of LEDs
            usleep(speed * 1000);  // Delay according to the speed (convert milliseconds to microseconds)
            
            if (direction == 1) {
                portB <<= 1; // Shift LED to the right
            } else {
                portB >>= 1; // Shift LED to the left
            }
        }
        
        // Change direction after reaching the end
        direction = -direction;
    }
}

int main() {
    int speed;

    while (1) {
        // Ask the user to input the speed (in milliseconds)
        printf("Enter the speed (in milliseconds) for the LED movement: ");
        scanf("%d", &speed);
        
        // Start the Knight Rider effect for two full cycles
        knight_rider(speed);
    }
    
    return 0;
}
