#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Diary {
    char date[11];       // Format: dd-mm-yyyy
    char title[50];
    char content[500];
};

void addEntry() {
    FILE *fp = fopen("diary.txt", "ab"); // append binary mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Diary entry;

    printf("Enter date (dd-mm-yyyy): ");
    scanf("%s", entry.date);
    getchar(); // consume newline

    printf("Enter title: ");
    fgets(entry.title, sizeof(entry.title), stdin);
    strtok(entry.title, "\n"); // remove trailing newline

    printf("Enter content: ");
    fgets(entry.content, sizeof(entry.content), stdin);
    strtok(entry.content, "\n");

    fwrite(&entry, sizeof(entry), 1, fp);
    fclose(fp);

    printf("Entry saved successfully!\n");
}

void viewEntries() {
    FILE *fp = fopen("diary.txt", "rb");
    if (fp == NULL) {
        printf("No entries found.\n");
        return;
    }

    struct Diary entry;
    printf("\n--- All Diary Entries ---\n");

    while (fread(&entry, sizeof(entry), 1, fp)) {
        printf("\nDate: %s\nTitle: %s\nContent: %s\n", entry.date, entry.title, entry.content);
    }

    fclose(fp);
}

void searchByDate() {
    char searchDate[11];
    int found = 0;

    printf("Enter date to search (dd-mm-yyyy): ");
    scanf("%s", searchDate);

    FILE *fp = fopen("diary.txt", "rb");
    if (fp == NULL) {
        printf("No entries found.\n");
        return;
    }

    struct Diary entry;
    while (fread(&entry, sizeof(entry), 1, fp)) {
        if (strcmp(entry.date, searchDate) == 0) {
            printf("\nDate: %s\nTitle: %s\nContent: %s\n", entry.date, entry.title, entry.content);
            found = 1;
        }
    }

    if (!found)
        printf("No entry found for the given date.\n");

    fclose(fp);
}

int main() {
    int choice;

    do {
        printf("\n--- Digital Diary ---\n");
        printf("1. Add Entry\n2. View All Entries\n3. Search by Date\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1: addEntry(); break;
            case 2: viewEntries(); break;
            case 3: searchByDate(); break;
            case 4: printf("Exiting diary.\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
