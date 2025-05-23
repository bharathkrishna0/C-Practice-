#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void showSignal(char *direction, char *color, int time) {
    printf("=================================\n");
    printf("     %s Signal: %s (%d sec)\n", direction, color, time);
    printf("=================================\n");
    for (int i = time; i > 0; i--) {
        printf("\r%s Light: %d seconds remaining", color, i);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}
void clearScreen(){
  #ifdef _WIN32
    system("cls");
  #else 
    system("clear");
  #endif
}
void simulateTrafficSignal() {
    char *directions[] = {"North", "East", "South", "West"};

    for (int i = 0; i < 4; i++) {
        clearScreen();
        printf("\nTraffic Signal Simulation\n\n");
        showSignal(directions[i], "GREEN", 5);
        showSignal(directions[i], "YELLOW", 2);
        showSignal(directions[i], "RED", 7);
    }
}
int main() {
    char choice;
    do {
        simulateTrafficSignal();
        printf("\nRepeat simulation? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    printf("Simulation ended.\n");
    return 0;
}
