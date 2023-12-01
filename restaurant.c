#include "defs.h"

/**
 * Initializes a restaurant with the given name, an empty reservation list, and an empty patrons array.
 *
 * Parameters:
 * - r (RestaurantType*): A pointer to the restaurant structure to be initialized. -input-output parameter
 * - n (char*): The name of the restaurant.  -input parameter
 *
 * Returns: None
 */
void initRestaurant(RestaurantType *r, char *n) {
    // Initialize the restaurant's name from the given parameter
    strcpy(r->name, n);


    // Initialize the reservations list
    initResvList(&(r->resList));


    // Initialize the patrons array
    initPatronArray(&(r->patrons));
}

/**
 * Validates the given date and time parameters.
 *
 * Parameters:
 * - yr (int): Year.  -input parameter
 * - mth (int): Month.  -input parameter
 * - day (int): Day.    -input parameter
 * - hr (int): Hour.     -input parameter
 * - min (int): Minute.   -input parameter
 *
 * Returns:
 * - int: 1 if the parameters are valid, 0 otherwise.
 */
int validateResvTime(int yr, int mth, int day, int hr, int min) {
    

    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);

    

    if (yr < localTime->tm_year + 1900) {
        return 0;  
    }

    
    if (mth < 1 || mth > 12 || day < 1 || day > 31 || hr < 0 || hr > 23 || min < 0 || min > 59) {
        return 0;  
    }

    return 1; 
}


/**
 * Creates a reservation for the given patron with specified date and time parameters.
 *
 * Parameters:
 * - r (RestaurantType*): A pointer to the restaurant structure.  -input-output parameter
 * - pId (int): ID of the patron making the reservation. -input parameter
 * - yr (int): Year of the reservation time.  -input parameter
 * - mth (int): Month of the reservation time.  -input parameter
 * - day (int): Day of the reservation time.    -input parameter
 * - hr (int): Hour of the reservation time.    -input parameter
 * - min (int): Minute of the reservation time.  -input parameter
 *
 * Returns: None
 */
void createResv(RestaurantType *r, int pId, int yr, int mth, int day, int hr, int min) {
    

    if (!validateResvTime(yr, mth, day, hr, min)) {
        fprintf(stderr, "Error: Invalid date and time parameters.\n");
        return; 
    }

    

    PatronType *foundPatron;
    if (!findPatron(&(r->patrons), pId, &foundPatron)) {
        fprintf(stderr, "Error: Patron with ID %d not found.\n", pId);
        return; 
    }

    

    ResvTimeType *newResvTime;
    initResvTime(&newResvTime, yr, mth, day, hr, min);

    

    ResvType *newReservation;
    initResv(&newReservation, foundPatron, newResvTime);

    

    addResv(&(r->resList), newReservation);
}


/**
 * Prints details of reservations made by a specific patron in the restaurant.
 *
 * Parameters:
 * - r (RestaurantType*): A pointer to the restaurant structure.  -input-output parameter
 * - id (int): ID of the patron.   -input parameter
 *
 * Returns: None
 */
void printResByPatron(RestaurantType *r, int id) {
    

    PatronType *foundPatron;
    if (!findPatron(&(r->patrons), id, &foundPatron)) {
        fprintf(stderr, "Error: Patron with ID %d not found.\n", id);
        return;
    }

    
    printf("Restaurant Name: %s\n", r->name);

    
    printf("Reservations made by Patron (ID: %d, Name: %s):\n", foundPatron->id, foundPatron->name);

    NodeType *current = r->resList.head;
    while (current != NULL) {
        

        if (current->reservation->patron->id == id) {
            printReservation(current->reservation);
        }
        current = current->next;
    }
}

/**
 * Cleans up memory allocated for the restaurant's patrons and reservations.
 *
 * Parameters:
 * - r (RestaurantType*): A pointer to the restaurant structure.    -input-output parameter
 *
 * Returns: None
 */
void cleanupRestaurant(RestaurantType *r) {
    
    cleanupPatronArray(&(r->patrons));

    
    cleanupResvList(&(r->resList));
}


