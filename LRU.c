#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int capacity = 4; // Number of frames

    int pageFaults = 0;
    int frames[capacity];
    int time[capacity];
    int frameIndex = 0;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1; // Initialize frames with -1 to indicate empty
        time[i] = 0; // Initialize time with 0
    }

    printf("Enter the number of pages: ");
    int numPages;
    scanf("%d", &numPages);

    printf("Enter the page reference sequence: \n");
    int pages[numPages];

    // Read the page reference sequence from the user
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
                time[j] = i; // Update the time of the page
                break;
            }
        }

        // If the page is not found in any frame, replace the least recently used page
        if (!found) {
            int replaceIndex = findLRU(time, capacity);
            frames[replaceIndex] = page;
            time[replaceIndex] = i; // Update the time of the new page
            pageFaults++;
        }
    }

    printf("Total number of page faults: %d\n", pageFaults);

    return 0;
}
