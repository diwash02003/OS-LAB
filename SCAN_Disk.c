#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void scanDiskScheduling(int requests[], int n, int headPosition, int maxCylinder) {
    int totalSeekTime = 0;
    int currentCylinder = headPosition;

    // Sort the requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    printf("Sequence of disk access:\n");

    // Move towards lower cylinder numbers
    for (int i = n - 1; i >= 0; i--) {
        if (requests[i] < headPosition) {
            printf("%d ", requests[i]);
            totalSeekTime += abs(requests[i] - currentCylinder);
            currentCylinder = requests[i];
        }
    }

    // Move towards the lowest cylinder
    printf("%d ", 0);
    totalSeekTime += abs(0 - currentCylinder);
    currentCylinder = 0;

    // Move towards higher cylinder numbers
    for (int i = 0; i < n; i++) {
        if (requests[i] >= headPosition) {
            printf("%d ", requests[i]);
            totalSeekTime += abs(requests[i] - currentCylinder);
            currentCylinder = requests[i];
        }
    }

    printf("\nTotal seek time: %d\n", totalSeekTime);
}

int main() {
    int requests[MAX_REQUESTS];
    int n; // Number of disk requests
    int headPosition; // Initial position of disk head
    int maxCylinder; // Maximum cylinder number

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of disk head: ");
    scanf("%d", &headPosition);

    printf("Enter the maximum cylinder number: ");
    scanf("%d", &maxCylinder);

    printf("\nDirection: To the smallest value\n\n");

    scanDiskScheduling(requests, n, headPosition, maxCylinder);

    return 0;
}
