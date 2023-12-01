#include "defs.h"

/**
 * Initializes a reservation list with default values.
 *
 * Parameters:
 * - list (ResvListType*): A pointer to the reservation list structure to be initialized. -input-output parameter
 *
 * Returns: None
 */
void initResvList(ResvListType *list) {
    // Initialize fields to default values
    list->head = NULL;  // Since the list is empty initially
    list->nextId = RES_IDS;
}

/**
 * Initializes a reservation time structure with the given parameters.
 *
 * Parameters:
 * - rt (ResvTimeType**): A pointer to a pointer to the reservation time structure to be initialized. - output parameter
 * - yr (int): Year of the reservation time. - input parameter
 * - mth (int): Month of the reservation time. - input parameter
 * - day (int): Day of the reservation time. - input parameter
 * - hr (int): Hour of the reservation time. - input parameter
 * - min (int): Minute of the reservation time. - input parameter
 *
 * Returns: None
 */
void initResvTime(ResvTimeType **rt, int yr, int mth, int day, int hr, int min) {
    // Allocate memory for a ResvTimeType structure
    *rt = (ResvTimeType *)malloc(sizeof(ResvTimeType));

    // Check if memory allocation was successful
    if (*rt == NULL) {
        // Handle memory allocation failure, e.g., print an error message and exit the program
        fprintf(stderr, "Memory allocation error for ResvTimeType.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize fields to the given parameters
    (*rt)->year = yr;
    (*rt)->month = mth;
    (*rt)->day = day;
    (*rt)->hours = hr;
    (*rt)->minutes = min;
}

/**
 * Initializes a reservation structure with the given patron and reservation time.
 *
 * Parameters:
 * - r (ResvType**): A pointer to a pointer to the reservation structure to be initialized. - input-output parameter
 * - p (PatronType*): A pointer to the patron associated with the reservation. - input parameter
 * - rt (ResvTimeType*): A pointer to the reservation time structure associated with the reservation. - input parameter
 *
 * Returns: None
 */
void initResv(ResvType **r, PatronType *p, ResvTimeType *rt) {
    // Dynamically allocate memory for ResvType
    *r = (ResvType*)malloc(sizeof(ResvType));

    // Check if allocation was successful
    if (*r == NULL) {
        fprintf(stderr, "Memory allocation failed for ResvType.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize ResvType fields
    (*r)->id = 0; // Temporary value until added to a reservation list
    (*r)->patron = p;
    (*r)->resvTime = rt;
}

/**
 * Compares two reservation times to check if the first one is earlier than the second.
 *
 * Parameters:
 * - r1 (ResvTimeType*): A pointer to the first reservation time. - input parameter
 * - r2 (ResvTimeType*): A pointer to the second reservation time. - input parameter
 *
 * Returns:
 * - int: 1 if r1 is earlier than r2, 0 otherwise.
 */
int lessThan(ResvTimeType *r1, ResvTimeType *r2) {
    
    if (r1->year < r2->year) {
        return 1;  
    } else if (r1->year > r2->year) {
        return 0;  
    }

    
    if (r1->month < r2->month) {
        return 1;
    } else if (r1->month > r2->month) {
        return 0;
    }

    
    if (r1->day < r2->day) {
        return 1;
    } else if (r1->day > r2->day) {
        return 0;
    }

    // Compare hours
    if (r1->hours < r2->hours) {
        return 1;
    } else if (r1->hours > r2->hours) {
        return 0;
    }

    // Compare minutes
    if (r1->minutes < r2->minutes) {
        return 1;
    }

    // If all fields are equal, r1 is not less than r2
    return 0;
}

/**
 * Adds a reservation to the reservation list in a sorted order based on reservation time.
 *
 * Parameters:
 * - list (ResvListType*): A pointer to the reservation list. - input-output parameter
 * - r (ResvType*): A pointer to the reservation to be added. - input parameter
 *
 * Returns: None
 */
void addResv(ResvListType *list, ResvType *r) {
    // Generate a unique identifier for the new reservation
    r->id = list->nextId;

    // Increment the nextId for the next reservation
    list->nextId++;

    // Create a new node for the reservation
    NodeType *newNode = malloc(sizeof(NodeType));

    // Check if memory allocation was successful
    if (newNode == NULL) {
        // Handle memory allocation failure, e.g., print an error message and exit the program
        fprintf(stderr, "Memory allocation error for ResvListNode.\n");
        exit(EXIT_FAILURE);
    }

    // Set the fields of the new node
    newNode->reservation = r;
    newNode->next = NULL;
    newNode->prev = NULL;

    // Special case: If the list is empty, the new node becomes the head
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }

    // Traverse the list to find the correct position to insert the new reservation
    NodeType *current = list->head;
    while (current != NULL && lessThan(r->resvTime, current->reservation->resvTime)) {
        current = current->next;
    }

    // Insert the new node at the correct position
    if (current == NULL) {
        // Insert at the end of the list
        NodeType *tail = list->head;
        while (tail->next != NULL) {
            tail = tail->next;
        }

        tail->next = newNode;
        newNode->prev = tail;
    } else {
        // Insert in the middle of the list
        newNode->next = current;
        newNode->prev = current->prev;

        if (current->prev != NULL) {
            current->prev->next = newNode;
        } else {
            list->head = newNode;
        }

        current->prev = newNode;
    }
}

/**
 * Prints details of a given reservation.
 *
 * Parameters:
 * - r (ResvType*): A pointer to the reservation to be printed. -input-output parameter
 *
 * Returns: None
 */
void printReservation(ResvType *r) {
    // Print details of the given reservation
    printf("Reservation ID: %04d | Patron ID: %04d | Name: %-20s | Date: %04d-%02d-%02d | Time: %02d:%02d\n",
           r->id, r->patron->id, r->patron->name, r->resvTime->year, r->resvTime->month, r->resvTime->day,
           r->resvTime->hours, r->resvTime->minutes);
}

/**
 * Prints all reservations in the reservation list in both forward and backward directions.
 *
 * Parameters:
 * - list (ResvListType*): A pointer to the reservation list. -input parameter
 *
 * Returns: None
 */
void printReservations(ResvListType *list) {
    printf("Printing reservations in forward direction:\n");

    // Print in the forward direction using the next links
    NodeType *currentForward = list->head;
    while (currentForward != NULL) {
        printReservation(currentForward->reservation);
        currentForward = currentForward->next;
    }

    printf("\nPrinting reservations in backward direction:\n");

    // Print in the backward direction using the prev links
    NodeType *currentBackward = list->head;
    while (currentBackward->next != NULL) {
        currentBackward = currentBackward->next;
    }

    while (currentBackward != NULL) {
        printReservation(currentBackward->reservation);
        currentBackward = currentBackward->prev;
    }
}

/**
 * Frees memory allocated for the reservation list and resets its values to default.
 *
 * Parameters:
 * - list (ResvListType*): A pointer to the reservation list. -input parameter
 *
 * Returns: None
 */
void cleanupResvList(ResvListType *list) {
    // Start with the head of the list
    NodeType *current = list->head;

    // Traverse the list and free each node
    while (current != NULL) {
        NodeType *nextNode = current->next;
        free(current);
        current = nextNode;
    }

    // Reset the head and nextId to their default values
    list->head = NULL;
    list->nextId = RES_IDS;  // Assuming STARTING_RESV_ID is a constant defined in your program
}