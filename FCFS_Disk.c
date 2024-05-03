#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Function to calculate seek time
int calculateSeekTime(int sequence[], int size, int head) {
    int seek_time = 0;
    int current_head = head;
    // Calculating seek time
    for(int i = 0; i < size; i++) {
        seek_time += abs(sequence[i] - current_head);
        current_head = sequence[i];
    }
    return seek_time;
}
// Function to print seek sequence
void printSeekSequence(int sequence[], int size) {
    printf("Seek Sequence: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");
}
int main() {
    int n, head;
    // Taking inputs
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the disk request sequence:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);
    // Calculating seek time and seek sequence
    int seek_time = calculateSeekTime(requests, n, head);
    printSeekSequence(requests, n);
    printf("Total Seek Time: %d\n", seek_time);

    return 0;
}
