#include "Car_Driving.h"
#include <stdio.h>
#include <stdlib.h>

// Variables
int speed = 0;
int distance = 0;
int threshold = 50;
int US_Get_distance_random(int l, int r, int count);
int US_Get_distance_random(int l, int r, int count)
{
    int i;
    int rand_number = -1;
    for (i = 0; i < count; i++)
    {
        rand_number = (rand() % (r - l + 1)) + l;
    }
    return rand_number;
}
// State pointer to function
void (*CA_state)();

State_define(Waiting)
{
    // State_Name
    Car_States_ID = Waiting;
    // State_Action
    speed = 0;
    // DC_Motor(speed)
    // US_Get_distance(distance)
    distance = US_Get_distance_random(45, 55, 1);
    // Event_Check
    (distance <= threshold) ? (CA_state = State(Waiting)) : (CA_state = State(Driving));
    printf("Waiting State : distance = %d speed = %d\n", distance, speed); // Added newline character for clarity
}

State_define(Driving)
{
    // State_Name
    Car_States_ID = Driving;
    // State_Action
    speed =30;
    // DC_Motor(speed)
    // US_Get_distance(distance)
    distance = US_Get_distance_random(45, 55, 1);
    // Event_Check
    (distance > threshold) ? (CA_state = State(Driving)) : (CA_state = State(Waiting));
    printf("Driving State : distance = %d speed = %d\n", distance, speed); // Added newline character for clarity
}
