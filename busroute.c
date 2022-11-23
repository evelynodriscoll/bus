#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 100
#define Load 1
#define Delete 2
#define Exit 3

typedef struct {
    unsigned int hours;
    unsigned int minutes;
} Time;

typedef struct {
    unsigned int busRouteNumber;
    char* startingLocation;
    char* endingLocation;
    Time routeStartTime;
    Time routeEndTime;
} BusRoute;

void executeMenuItem(int);
int displayMenu();
BusRoute** detectNull(BusRoute**);
void loadBusRoute(BusRoute**);
void deleteBusRoute(BusRoute**);

BusRoute* ActiveBusRoutes[SIZE] = {0};

int main(void){   
   int choice = Exit;
   do{
      choice = displayMenu();
	   executeMenuItem(choice);
   } while (choice != Exit);

   printf("Program exited\n");
   exit(EXIT_SUCCESS);
}

int displayMenu(){  
    int input = Exit;
    printf("Select one of the following:\n\n");
    printf("%d. Load a bus route\n", Load);
    printf("%d. Delete a bus route\n", Delete);
    printf("%d. Exit Program\n", Exit);
    scanf("%d", &input);
    return input;
}

void executeMenuItem(int menuItem){

    switch(menuItem) {

    case Exit: break;

    case Load: 
    loadBusRoute(ActiveBusRoutes);
    break;

    case Delete: 
    deleteBusRoute(ActiveBusRoutes);
    break;

    
    default:
            printf("Bad menu value entered; ");
    }
    printf("\n");
}

BusRoute** detectNull (BusRoute* ActiveBusRoutes[]) {

    BusRoute** p;
    BusRoute** firstNull;

    for(p = ActiveBusRoutes; p<ActiveBusRoutes+SIZE; p++) {
        if(*p ==0) {
           firstNull = p;
            break;
        }   
    }
    return firstNull;
}

void loadBusRoute (BusRoute* ActiveBusRoutes []) {

    BusRoute* newRoute = malloc(sizeof(BusRoute));
    BusRoute** newRoutePtr = detectNull(ActiveBusRoutes);

    char tempStart[30] = {'\0'};
    char tempEnd[30] = {'\0'};
    Time startTime;
    Time endTime;
    
    
    printf("Please enter the bus route number: ");
    scanf("%u", &newRoute->busRouteNumber);
    getchar();

    printf("Please enter the starting location: ");
    gets(tempStart);
    tempStart[strlen(tempStart)]='\0';

    printf("Please enter the ending location: ");
    gets(tempEnd);
    tempEnd[strlen(tempEnd)]='\0';

    printf("Please enter the hour of the start time: ");
    scanf(" %u", &startTime.hours);

    printf("Please enter the minutes of the start time: ");
    scanf(" %u", &startTime.minutes);

    printf("Please enter the hour of the end time: ");
    scanf(" %u", &endTime.hours);

    printf("Please enter the minutes of the end time: ");
    scanf(" %u", &endTime.minutes);

    newRoute->routeStartTime = startTime;
    newRoute->routeEndTime = endTime;

    newRoute->startingLocation =(char *)malloc(strlen(tempStart)+1);
    strcpy(newRoute->startingLocation, tempStart);

    newRoute->endingLocation =(char *)malloc(strlen(tempEnd)+1);
    strcpy(newRoute->endingLocation, tempEnd);

    *newRoutePtr = newRoute;

}

void deleteBusRoute(BusRoute* ActiveBusRoutes[]) {
    int deleteNum;
    int routeNum;

    printf("Enter the bus route number you wish to delete: ");
    scanf("%d", &deleteNum);
    
    BusRoute** p;
    for(p = ActiveBusRoutes+SIZE; p>=ActiveBusRoutes; p--) {
        BusRoute* deletePtr = *p;
        if(deletePtr!=0){
            if(deletePtr->busRouteNumber==deleteNum) {
            free(deletePtr->startingLocation);
            free(deletePtr->endingLocation);
            free(deletePtr);
            *p = NULL;
            }
        }
        
    }

}


