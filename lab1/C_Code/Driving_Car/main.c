#include "Car_Driving.h"

void set_up()
{
    // INIT all the drivers
    // INIT IRQ ...........
    // INIT HAL US_Driver,DC_Driver
    // INIT Block
    // sets states pointers for each block
    CA_state = State(Waiting);
}

int main()
{
    volatile int j;
    set_up();
    while(1)
    {
    // Call state for each block
         CA_state();
         for(j=0;j<900000000;j++);
    }
    return 0;
}
