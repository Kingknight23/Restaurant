#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define C_OK            0
#define C_NOK          -1
#define C_TRUE          1
#define C_FALSE         0

#define MAX_STR        64
#define MAX_CAP       128

#define PATRON_IDS   1001
#define RES_IDS      4001

typedef struct {
  int   id;
  char  name[MAX_STR];
} PatronType;

typedef struct {
  int day;
  int month;
  int year;
  int hours;
  int minutes;
} ResvTimeType;

typedef struct {
  int           id;
  PatronType   *patron;
  ResvTimeType *resvTime;
} ResvType;

/*** Define the PatronArrayType here ***/
typedef struct {
    PatronType* elements;  // Dynamically allocated array of PatronType structures
    int size;             // Current number of patrons in the elements array
    int nextId;           // Unique identifier for the next patron
} PatronArrayType;

/*** Define the NodeType here ***/
typedef struct NodeType {
    ResvType *reservation;
    struct NodeType *prev;
    struct NodeType *next;
} NodeType;

/*** Define the ResvListType here ***/
typedef struct ResvListType {
    NodeType *head;
    int nextId;
} ResvListType;


/*** Define the RestaurantType here ***/
typedef struct {
    char name[MAX_STR];
    ResvListType resList;
    PatronArrayType patrons;
} RestaurantType;

void printMenu(int*);
void loadPatronData(RestaurantType*);
void loadResData(RestaurantType*);

void initPatronArray(PatronArrayType*);
void addPatron(PatronArrayType*, char*);
int findPatron(PatronArrayType*, int, PatronType**);
void printPatrons(PatronArrayType*);
void cleanupPatronArray(PatronArrayType*);

void initResvList(ResvListType*);
void initResvTime(ResvTimeType**, int, int, int, int, int);
void initResv(ResvType**, PatronType*, ResvTimeType*);
int lessThan(ResvTimeType*, ResvTimeType*);
void addResv(ResvListType*, ResvType*);
void printReservation(ResvType*);
void printReservations(ResvListType*);
void cleanupResvList(ResvListType*);

void initRestaurant(RestaurantType*, char*);
int validateResvTime(int, int, int, int, int);
void createResv(RestaurantType*, int, int, int, int, int, int);
void printResByPatron(RestaurantType*, int);
void cleanupRestaurant(RestaurantType*); 



