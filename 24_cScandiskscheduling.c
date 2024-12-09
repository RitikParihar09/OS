#include <stdio.h>
#include <stdlib.h>

void cscanDiskScheduling(int requests[], int n, int head, int disk_size, int direction) {
    int seek_sequence[n + 2];
    int seek_count = 0;
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int start = -1;
    for (i = 0; i < n; i++) {
        if (requests[i] >= head) {
            start = i;
            break;
        }
    }

    if (direction == 1) {
        for (i = start; i < n; i++) {
            seek_sequence[seek_count++] = requests[i];
        }
        seek_sequence[seek_count++] = disk_size - 1;
        seek_sequence[seek_count++] = 0;
        for (i = 0; i < start; i++) {
            seek_sequence[seek_count++] = requests[i];
        }
    } else {
        for (i = start - 1; i >= 0; i--) {
            seek_sequence[seek_count++] = requests[i];
        }
        seek_sequence[seek_count++] = 0;
        seek_sequence[seek_count++] = disk_size - 1;
        for (i = n - 1; i >= start; i--) {
            seek_sequence[seek_count++] = requests[i];
        }
    }

    int total_seek = 0;
    int current_position = head;
    for (i = 0; i < seek_count; i++) {
        total_seek += abs(seek_sequence[i] - current_position);
        current_position = seek_sequence[i];
    }

    printf("Seek Sequence: ");
    for (i = 0; i < seek_count; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Seek Time: %d\n", total_seek);
}

int main() {
    int n, head, disk_size, direction;

    printf("Enter number of requests: ");
    scanf("%d", &n);
    int requests[n];

    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter current position of head: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    printf("Enter direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    cscanDiskScheduling(requests, n, head, disk_size, direction);

    return 0;
}
