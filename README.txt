                                                        =============================================
                                                                    Restaurant Management
                                                        =============================================

Preamble:
   - Program Author: Victor Igwe
   - Student Number: 101237544
   - Purpose: This program manages manage a restaurant, with patrons and reservations that are stored in different types of collection structures.
   - Source Files:
        - defs.h: Header file containing structure definitions and function prototypes.

        - main.c: Contains the main program logic.
        
        - patrons.c: Source file containing functions implementating the patrons actions ie:
            (a) initPatronArray(PatronArrayType *arr) -     function that initializes every field of the given patron collection to default values.
            (b) addPatron(PatronArrayType *arr, char *n) -  function that adds a new patron to the back of the given patron collection
            (c) findPatron(PatronArrayType *arr, int id, PatronType **p) - function that searches through the given patron collection to find the patron with an id
            (d) printPatrons(PatronArrayType *arr) -        function that prints out to the screen all the details of every patron in the given patron collection.       
            (e) cleanupPatronArray(PatronArrayType *arr) -  function that deallocates all the required dynamically allocated memory for the given patron collection.
        
        - resv.c: Source file containing functions implementating the reservation actions ie: 
            (a) initResvList(ResvListType *list)          - function that initializes both fields of the given list parameter to default values.
            (b) initResvTime(ResvTimeType **rt, int yr, int mth, int day, int hr,int min) - function that dynamically allocates memory for a ResvTimeType structure, initializes its fields to the given parameters, and “returns” this new structure
            (c) initResv(ResvType **r, PatronType *p, ResvTimeType *rt)    - function that dynamically allocates memory for a ResvType structure, initializes its patron and reservation
            (d) lessThan(ResvTimeType *r1, ResvTimeType *r2)   -   function that compares two reservation times
            (e) addResv(ResvListType *list, ResvType *r)  -    function that adds the reservation "r" in its correct position in the given "list"
            (f) printReservation(ResvType *r)              - function that prints out all the details of the given reservation. 
            (g) printReservations(ResvListType *list)     - function that prints out the details of every reservation in the given list.
            (h) cleanupResvList(ResvListType *list)       - function that deallocates all the required dynamically allocated memory for the given list.

        -restaurant.c: Source file containing functions implementating the restaurant actions ie: 
            (a) initRestaurant(RestaurantType *r, char *n)  -function that initializes the three fields of the given restaurant structure.
            (b) validateResvTime(int yr, int mth, int day, int hr, int min) -function that checks that the parameters represent a valid date and time
            (c) createResv(RestaurantType *r, int pId, int yr, int mth, int day,int hr, int min)    -function that creates a new reservation and adds it to the given restaurant
            (d) printResByPatron(RestaurantType *r, int id)    -function that prints out the restaurant name and the details of every reservation made by the patron with the given id.
            (e) void cleanupRestaurant(RestaurantType *r)   - function that cleans up all the dynamically allocated memory for the given restaurant r.
        
        -load.c: Source file containing functions loading default patrons and reservations:
            (a) loadResData(RestaurantType* r)  -function loads the intial reservation details
            (b) loadPatronData(RestaurantType* r) - function loads the intial patron details

Compilation and Launching Instructions:

   Compilation:
   1. Open a terminal or command prompt.
   2. Navigate to the directory containing the source codes.
   3. Compile the program using a C compiler (e.g., gcc):
      ```
      gcc -o restaurant_management main.c restaurant.c load.c patrons.c resv.c
      ```

   Launching:
   1. After successful compilation, run the program:
      ```
      ./restaurant_management
      ```
      Note: The above command assumes a Unix-like environment.