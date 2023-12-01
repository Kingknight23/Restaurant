#include "defs.h"



/**
 * Initializes a patron array with default values.
 *
 * Parameters:
 * - arr (PatronArrayType*): A pointer to the patron array structure to be initialized. -input-output parameter
 *
 * Returns: None
 */
void initPatronArray(PatronArrayType *arr) {
    
    arr->size = 0;
    arr->nextId = PATRON_IDS ;

    
    arr->elements = (PatronType *)malloc(PATRON_IDS * sizeof(PatronType));

    
    if (arr->elements == NULL) {

        fprintf(stderr, "Memory allocation error for PatronArrayType elements.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * Adds a patron with the given name to the patron array.
 *
 * Parameters:
 * - arr (PatronArrayType*): A pointer to the patron array.  -input-output parameter
 * - n (char*): The name of the patron to be added. -input parameter
 *
 * Returns: None
 */
void addPatron(PatronArrayType *arr, char *n) {
    
    if (arr->size >= MAX_CAP) {
        
        arr->elements = (PatronType *)realloc(arr->elements, 2 * arr->size * sizeof(PatronType));

        
        if (arr->elements == NULL) {
            
            fprintf(stderr, "Memory allocation error during array resize.\n");
            exit(EXIT_FAILURE);
        }
    }

    
    PatronType *newPatron = &(arr->elements[arr->size]);
    strcpy(newPatron->name, n);
    newPatron->id = arr->nextId;

    
    arr->nextId++;


    arr->size++;
}

/**
 * Finds a patron with the given ID in the patron array.
 *
 * Parameters:
 * - arr (PatronArrayType*): A pointer to the patron array.  -input-output parameter
 * - id (int): The ID of the patron to be found. -input parameter
 * - p (PatronType**): A pointer to a pointer to the found patron structure -output parameter
 *
 * Returns:
 * - int: 1 if the patron with the given ID is found, 0 otherwise.
 */
int findPatron(PatronArrayType *arr, int id, PatronType **p) {
    
    for (int i = 0; i < arr->size; i++) {
        if (arr->elements[i].id == id) {
            
            *p = &(arr->elements[i]);
            return 1;  
        }
    }

    
    *p = NULL;
    return 0;  
}

/**
 * Prints details of all patrons in the patron array.
 *
 * Parameters:
 * - arr (PatronArrayType*): A pointer to the patron array. -input-output parameter
 *
 * Returns: None
 */
void printPatrons(PatronArrayType *arr) {

    for (int i = 0; i < arr->size; i++) {
        printf("Patron ID: %d, Name: %s\n", arr->elements[i].id, arr->elements[i].name);
    }
}


/**
 * Frees memory allocated for the patron array and resets its values to default.
 *
 * Parameters:
 * - arr (PatronArrayType*): A pointer to the patron array. -input parameter
 *
 * Returns: None
 */
void cleanupPatronArray(PatronArrayType *arr) {
    
    free(arr->elements);

    
    arr->size = 0;
    arr->nextId = PATRON_IDS ;  
}