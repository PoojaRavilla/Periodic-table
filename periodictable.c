#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTS 118  // Total elements

// Structure to store element data
typedef struct {
    int atomicNumber;
    char symbol[3];
    char name[20];
    float atomicWeight;
    char group[30];
} Element;

// Function to load elements from file
int loadElements(Element elements[]) {
    FILE *file = fopen("elements.txt", "r");
    if (!file) {
        printf("Error: Could not open elements file.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%d %s %s %f %s", 
                  &elements[count].atomicNumber, 
                  elements[count].symbol, 
                  elements[count].name, 
                  &elements[count].atomicWeight, 
                  elements[count].group) != EOF) {
        count++;
        if (count >= MAX_ELEMENTS) break;
    }

    fclose(file);
    return count;
}

// Function to search by atomic number
void searchByAtomicNumber(Element elements[], int total, int atomicNum) {
    for (int i = 0; i < total; i++) {
        if (elements[i].atomicNumber == atomicNum) {
            printf("\nElement Found:\n");
            printf("Atomic Number: %d\n", elements[i].atomicNumber);
            printf("Symbol: %s\n", elements[i].symbol);
            printf("Name: %s\n", elements[i].name);
            printf("Atomic Weight: %.3f\n", elements[i].atomicWeight);
            printf("Group: %s\n", elements[i].group);
            return;
        }
    }
    printf("No element found with atomic number %d.\n", atomicNum);
}

// Function to search by symbol or name
void searchBySymbolOrName(Element elements[], int total, char input[]) {
    for (int i = 0; i < total; i++) {
        if (strcasecmp(elements[i].symbol, input) == 0 || strcasecmp(elements[i].name, input) == 0) {
            printf("\nElement Found:\n");
            printf("Atomic Number: %d\n", elements[i].atomicNumber);
            printf("Symbol: %s\n", elements[i].symbol);
            printf("Name: %s\n", elements[i].name);
            printf("Atomic Weight: %.3f\n", elements[i].atomicWeight);
            printf("Group: %s\n", elements[i].group);
            return;
        }
    }
    printf("No element found with name or symbol '%s'.\n", input);
}

int main() {
    Element elements[MAX_ELEMENTS];
    int totalElements = loadElements(elements);

    if (totalElements == 0) {
        printf("No elements loaded. Exiting...\n");
        return 1;
    }

    int choice;
    printf("Periodic Table Lookup\n");
    printf("1. Search by Atomic Number\n");
    printf("2. Search by Symbol or Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int atomicNum;
        printf("Enter Atomic Number: ");
        scanf("%d", &atomicNum);
        searchByAtomicNumber(elements, totalElements, atomicNum);
    } else if (choice == 2) {
        char input[20];
        printf("Enter Element Symbol or Name: ");
        scanf("%s", input);
        searchBySymbolOrName(elements, totalElements, input);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
