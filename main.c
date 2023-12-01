#include "defs.h"

int main() {
    RestaurantType myRestaurant;

   
    initRestaurant(&myRestaurant, "My Restaurant");

    loadPatronData(&myRestaurant);

    loadResData(&myRestaurant);

    int userChoice;

    do {

        printMenu(&userChoice);

        switch (userChoice) {
            case 1:
                printf("Restaurant Name: %s\n", myRestaurant.name);
                printPatrons(&myRestaurant.patrons);
                break;
            case 2:
                printf("Restaurant Name: %s\n", myRestaurant.name);
                printReservations(&myRestaurant.resList);
                break;
            case 3:
                int id;
                printf("Please enter Patron ID: ");
                scanf("%d", &id);
                printResByPatron(&myRestaurant, id);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option. Please enter a valid menu option.\n");
                break;
        }

    } while (userChoice != 0);

    cleanupRestaurant(&myRestaurant);
    return 0;
}

void printMenu(int *choice) {
    int c = -1;
    int numOptions = 3;

    printf("\nMAIN MENU\n");
    printf("  (1) Print patrons\n");
    printf("  (2) Print reservations\n");
    printf("  (3) Print reservations by patron\n");
    printf("  (0) Exit\n\n");

    printf("Please enter your selection: ");
    scanf("%d", &c);

    while (c < 0 || c > numOptions) {
        printf("Invalid option. \nPlease enter a valid menu option: ");
        scanf("%d", &c);
    }

    *choice = c;
}
