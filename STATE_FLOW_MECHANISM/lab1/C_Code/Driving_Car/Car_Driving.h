#ifndef CAR_DRIVING_H_
#define CAR_DRIVING_H_

#include "State.h"
#include <stdio.h>
#include <stdlib.h>

// Define States
enum {
    Waiting,
    Driving
} Car_States_ID;

// Declare state functions CA
State_define(Waiting);
State_define(Driving);

// State pointer to function
extern void (*CA_state)();

#endif /* CAR_DRIVING_H_ */
