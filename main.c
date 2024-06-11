#include "TM4C123GH6PM.h"
void  initializePortsAndPins(void);
void  initializeTimers(void);
void  TrafficLoop(void);
void ButtonPressedHandler (void);
uint8_t STATE = 0 ;
void initializePortsAndPins() {
    // Enable clock for GPIO ports A, and F
    SYSCTL->RCGCGPIO |= (1 << 0)| (1 << 5);
    GPIOA->LOCK = 0x4C4F434B; // Magic unlock value
    (*((volatile uint32_t *)0x40004524)) = 0x1F; // Make PORTA pins configurable
    // Unlock Port F
    GPIOF->LOCK = 0x4C4F434B; // Magic unlock value
    (*((volatile uint32_t *)0x40025524)) = 0x1F;
    // Set pins A2, A3, A4, A6, A7 as outputs
    GPIOA->DIR |= (1 << 2) | (1 << 3) | (1 << 4)|(1 << 6)|(1 << 7);
    GPIOA->DEN |= (1 << 2) | (1 << 3) | (1 << 4)|(1 << 6)|(1 << 7);;
    // Set pin F4 as input
    GPIOF->DIR &= ~(1 << 4);
    // Enable digital function on pin F4
    GPIOF->DEN |= (1 << 4);
    // Enable pull-up resistor on pin F4
    GPIOF->PUR |= (1 << 4);
    // Configure pin F4 for interrupt
    GPIOF->IS &= ~(1 << 4); // Set pin F4 as edge-sensitive
    GPIOF->IBE &= ~(1 << 4); // Set pin F4 as single edge
    GPIOF->IEV &= ~(1 << 4); // Set pin F4 to trigger on falling edge
    GPIOF->ICR |= (1 << 4); // Clear any prior interrupt
    GPIOF->IM |= (1 << 4); // Enable interrupt for pin F4
    NVIC->IP[30] = 3<<5;
    NVIC->ISER[0] |= (1<<30);  
}
void ButtonPressedHandler(void) {
    // Clear interrupt flag for pin F4
    GPIOF->ICR |= (1 << 4);

    // Pause Timer 0
    TIMER0->CTL &= ~(1 << 0);
    
    GPIOA->DATA &= ~((1 << 2) | (1 << 3) | (1 << 4)| (1 << 6)| (1 << 7)); // Turn off LEDs connected to pins A2, A3, A4
    GPIOA->DATA |= (1 << (4));
    // Turn on pedestrian green
    GPIOA->DATA |= (1 << 7);
        // Turn off pedestrian red
    GPIOA->DATA &= ~(1 << 6);

    // Turn on Timer 1
    TIMER1->CTL |= (1 << 0);

    // Wait for Timer 1 timeout flag
    while (!(TIMER1->RIS & (1 << 0))) {
        // Wait
    }

    // Clear Timer 1 timeout flag
    TIMER1->ICR |= (1 << 0);

    // Turn off pedestrian green
    GPIOA->DATA &= ~(1 << 7);
    // Turn on pedestrian red
    GPIOA->DATA |= (1 << 6);

    // Continue Timer 0
    TIMER0->CTL |= (1 << 0);
    GPIOA->DATA &= ~((1 << 2) | (1 << 3) | (1 << 4)); // Turn off LEDs connected to pins A2, A3, A4

    switch (STATE){
    case 0: GPIOA->DATA |= (1 << (2));  GPIOA->DATA &= ~(1 << 7); GPIOA->DATA |= (1 << 6); break;
    case 1: GPIOA->DATA |= (1 << (3));  GPIOA->DATA &= ~(1 << 7); GPIOA->DATA |= (1 << 6); break;
    case 2: GPIOA->DATA |= (1 << (4));  GPIOA->DATA &= ~(1 << 6); GPIOA->DATA |= (1 << 7);break;
    default:;
}
}

void initializeTimers() {
    // Enable clock for Timer 0 and Timer 1
    SYSCTL->RCGCTIMER |= (1 << 0) | (1 << 1);
 // Disable Timer 0 before configuring
    TIMER0->CTL &= ~(1 << 0);

    // Choose a prescaler of 1
    TIMER0->CFG = 0x0;

    // Set Timer 0 to 32-bit mode
    TIMER0->CTL |= (1 << 1);

    // Configure Timer 0 for one-shot timer mode
    TIMER0->TAMR |= (0x1 << 0); // Set timer mode to one-shot
    
    
    // Disable Timer 1 before configuring
    TIMER1->CTL &= ~(1 << 0);

    // Choose a prescaler of 1
    TIMER1->CFG = 0x0;

    // Set Timer 1 to 32-bit mode
    TIMER1->CTL |= (1 << 1);

    // Configure Timer 1 for one-shot timer mode
    TIMER1->TAMR |= (0x1 << 0); // Set timer mode to one-shot

    // Calculate the reload value for a 2-second delay
    // 2 seconds * 20 MHz (clock frequency) / 1 (prescaler)
    uint32_t reloadValue = 2 * 20000000 ;

    // Set the reload value
    TIMER1->TAILR = reloadValue - 1;

}


void TrafficLoop() {
    // Turn off all LEDs
    GPIOA->DATA &= ~((1 << 2) | (1 << 3) | (1 << 4)); // Turn off LEDs connected to pins A2, A3, A4

    TIMER0->CTL &= ~(1 << 0);

    switch (STATE){
    case 0: // GREEN
        GPIOA->DATA |= (1 << (2)); // Turn on LED connected to pins A2
         // Set Timer 0 to 5 seconds (replace x with the desired duration)
        TIMER0->TAILR = 79999999; /* x seconds in timer ticks */;
        // Turn on pedestrian green
        GPIOA->DATA |= (1 << 6);
         // Turn off pedestrian red
         GPIOA->DATA &= ~(1 << 7);
        break;

     case 1: //YELLOW
        GPIOA->DATA |= (1 << (3)); // Turn on LED connected to pins A3
         // Set Timer 0 to 2 seconds (replace x with the desired duration)
        TIMER0->TAILR = 2*79999999/5; /* x seconds in timer ticks */;
        
        break;
    case 2: //RED
      
      GPIOA->DATA |= (1 << (4)); // Turn on LED connected to pins A4
         // Set Timer 0 to 2 seconds (replace x with the desired duration)
        TIMER0->TAILR = 3*79999999/5; /* x seconds in timer ticks */;
        // Turn off pedestrian green
        GPIOA->DATA &= ~(1 << 6);
        // Turn on pedestrian red
        GPIOA->DATA |= (1 << 7);
        
        break;
    default: break;
    }
        
        // Turn on Timer 0
        TIMER0->CTL |= (1 << 0);

        // Wait for Timer 0 timeout flag
        while (!(TIMER0->RIS & (1 << 0))) ;

        // Clear Timer 0 timeout flag
        TIMER0->ICR |= (1 << 0);
        STATE++;
        if(STATE >= 3 ) STATE = 0 ;
    }


void main() {
  
    initializePortsAndPins();
    initializeTimers();

    while (1) {
        TrafficLoop();
    }

}

