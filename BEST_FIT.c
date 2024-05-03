#include<stdio.h>
void main() {
    int bsize[10], psize[10], bno, pno, flags[10], allocation[10], i, j, smallest;
    for(i = 0; i < 10; i++) {
        flags[i] = 0;
        allocation[i] = -1;
    }
    printf("Enter the number of memory blocks: ");
    scanf("%d", &bno);
    printf("Enter the size of each memory block: \n");
    for(i = 0; i < bno; i++) {
        scanf("%d", &bsize[i]);
    }
    printf("Enter the number of processes: ");
    scanf("%d", &pno);
    printf("Enter the size of each process: \n");
    for(i = 0; i < pno; i++) {
        scanf("%d", &psize[i]);
    }
    for(i = 0; i < pno; i++) {
        smallest = -1;
        for(j = 0; j < bno; j++) {
            if(flags[j] == 0 && bsize[j] >= psize[i]) {
                if(smallest == -1) {
                    smallest = j;
                } else if(bsize[j] < bsize[smallest]) {
                    smallest = j;
                }
            }
        }
        if(smallest != -1) {
            allocation[i] = smallest;
            flags[smallest] = 1;
        }
    }
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for(i = 0; i < pno; i++) {
        printf("%d\t\t%d\t\t", i+1, psize[i]);
        if(allocation[i] != -1) {
            printf("%d\n", allocation[i]+1);
        } else {
            printf("Not Allocated\n");
        }
    }
}
