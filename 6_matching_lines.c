#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

void write_details(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) exit(1);

    char detail[MAX_LINE_LENGTH];
    printf("Enter details for %s (type 'exit' to finish):\n", filename);
    while (fgets(detail, sizeof(detail), stdin)) {
        if (strcmp(detail, "exit\n") == 0) break;
        fputs(detail, file);
    }
    fclose(file);
}

void print_matching_lines(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    char line1[MAX_LINE_LENGTH], line2[MAX_LINE_LENGTH];

    printf("\nMatching lines:\n");
    while (fgets(line1, sizeof(line1), f1)) {
        rewind(f2);
        while (fgets(line2, sizeof(line2), f2)) {
            if (strcmp(line1, line2) == 0) {
                printf("%s", line1);
                break;
            }
        }
    }
    fclose(f1);
    fclose(f2);
}

int main() {
    write_details("my_details.txt");
    write_details("friends_details.txt");
    print_matching_lines("my_details.txt", "friends_details.txt");
    return 0;
}
