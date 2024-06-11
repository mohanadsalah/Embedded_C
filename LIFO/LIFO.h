#ifndef LIFO_H_
#define LIFO_H_

// Type definitions
typedef struct {
    unsigned int length;    // Length of the LIFO buffer
    unsigned int count;     // Number of items currently in the LIFO buffer
    unsigned int* base;     // Pointer to the base of the LIFO buffer
    unsigned int* head;     // Pointer to the head of the LIFO buffer
} LIFO_BUF_t;

typedef enum {
    LIFO_no_error,   // No error occurred
    LIFO_Full,       // LIFO buffer is full
    LIFO_empty,      // LIFO buffer is empty
    LIFO_NULL        // NULL pointer encountered
} LIFO_Status;

// APIs
// Function to add an item to the LIFO buffer
LIFO_Status LIFO_Add_item(LIFO_BUF_t* lifo_buf, unsigned int item);

// Function to get an item from the LIFO buffer
LIFO_Status LIFO_get_item(LIFO_BUF_t* lifo_buf, unsigned int* item);

// Function to initialize the LIFO buffer
LIFO_Status LIFO_init_item(LIFO_BUF_t* lifo_buf, unsigned int* buf, unsigned int length);

#endif /* LIFO_H_ */
