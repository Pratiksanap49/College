#include <stdio.h>

#define MAXP 100
#define MAXF 10

// Function to check if page exists in frame (returns index or -1)
int findPage(int frames[], int fsize, int page) {
    for (int i = 0; i < fsize; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

// Function to print frames
void printFrames(int frames[], int fsize) {
    printf("[ ");
    for (int i = 0; i < fsize; i++) {
        if (frames[i] == -1) printf("_ ");
        else printf("%d ", frames[i]);
    }
    printf("]\n");
}

int main() {
    int n, fsize;
    int pages[MAXP], frames[MAXF], lastUsed[MAXF];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter frame size (>=3): ");
    scanf("%d", &fsize);

    if(fsize < 3 || fsize > MAXF) {
        printf("Frame size must be >= 3\n");
        return 0;
    }

    // Initialize frames and lastUsed arrays
    for(int i = 0; i < fsize; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    int time = 0, faults = 0;

    printf("\nLRU Page Replacement:\n");

    for(int i = 0; i < n; i++) {
        int page = pages[i];
        int pos = findPage(frames, fsize, page); // check if page exists

        if(pos != -1) {
            // Page HIT -> update last used time
            lastUsed[pos] = time;
        }
        else {
            // Page MISS -> page fault
            faults++;

            // check empty frame first
            int empty = -1;
            for(int j = 0; j < fsize; j++) {
                if(frames[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if(empty != -1) {
                // Put in empty frame
                frames[empty] = page;
                lastUsed[empty] = time;
            }
            else {
                // Find least recently used page
                int lru = 0;
                for(int j = 1; j < fsize; j++) {
                    if(lastUsed[j] < lastUsed[lru])
                        lru = j;
                }
                // Replace LRU page
                frames[lru] = page;
                lastUsed[lru] = time;
            }
        }

        printf("Page %d -> ", page);
        printFrames(frames, fsize);
        time++;
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
