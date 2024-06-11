#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, *ptr, sum = 0;
    printf("Enter number of elements= ");
    scanf("%d", &n);
    ptr = (int*) calloc(n, sizeof(int));
    if (ptr == NULL) {
        printf("\nError, memory is not allocated");
        exit(0);
    }
    printf("Enter elements of array: ");
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("Enter element %d in array: ", i + 1);
        scanf("%d", ptr + i);
        sum += *(ptr + i);
    }
    printf("Sum of elements in array [");
    for (i = 0; i < n; i++) {
        printf("%d", *(ptr + i));
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("] = %d\n", sum);
    free(ptr);
    return 0;
}
