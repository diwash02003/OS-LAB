//FIFO

#include <stdio.h>
int main() {
    int capacity = 4; // Number of frames
    int pageFaults = 0;
    int frames[capacity];
    int frameIndex = 0;
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1; // Initialize frames with -1 to indicate empty
    }
    int numPages;
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);
    int pages[numPages];
    printf("Enter the page reference sequence: \n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }
    for (int i = 0; i < numPages; i++) {
        int page = pages[i];
        int found = 0;
        // Check if the page is already in a frame
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found in any frame, replace the oldest page
        if (!found) {
            frames[frameIndex] = page;
            frameIndex = (frameIndex + 1) % capacity;
            pageFaults++;
        }
    }
    printf("Total number of page faults: %d\n", pageFaults);

    return 0;
}
