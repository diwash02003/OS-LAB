#include <stdio.h>

int main() {
    int capacity = 4; // Number of frames
    int pages[100]; // Array to store the page sequence
    int pageFaults = 0;
    int frames[capacity];
    int future[capacity];
    int frameIndex = 0;
    int pageCount;

    printf("Enter the number of pages in the sequence: ");
    scanf("%d", &pageCount);

    printf("Enter the page sequence: \n");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1; // Initialize frames with -1 to indicate empty
    }

    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found in any frame, replace the page with the one that will not be needed for the longest period of time in the future
        if (!found) {
            int replaceIndex = -1;
            int farthest = i + 1;

            // Find the page that will not be needed for the longest period of time in the future
            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < pageCount; k++) {
                    if (pages[k] == frames[j]) {
                        if (k > farthest) {
                            farthest = k;
                            replaceIndex = j;
                        }
                        break;
                    }
                }
                // If the page will not be referenced in the future, replace it
                if (k == pageCount) {
                    replaceIndex = j;
                    break;
                }
            }

            frames[replaceIndex] = page;
            pageFaults++;
        }
    }
    printf("Total number of page faults: %d\n", pageFaults);

    return 0;
}
