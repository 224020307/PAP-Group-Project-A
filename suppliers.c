#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"
#include "utils.h"   // readInt, readString, readPositiveDouble — from Student 6

void supplierMenu(Supplier suppliers[], int *count) {
    int choice;
    do {
        printf("\n---- SUPPLIER MANAGEMENT ----\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search by ID\n");
        printf("4. Search by Name\n");
        printf("5. Supplier Report\n");
        printf("6. Back to Main Menu\n");
        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice) {
            case 1: 
	addSupplier(suppliers, count); 
break;
            case 2: 
	displaySuppliers(suppliers, *count); 
break;
            case 3: 
	searchSupplierByID(suppliers, *count);
 break;
            case 4: 
	searchSupplierByName(suppliers, *count);
 break;
            case 5: 
	supplierReport(suppliers, *count);
 break;
            case 6: 
	printf("Returning to main menu...\n");
 break;
        }
    } while (choice != 6);
}

/* Very simple email check: must contain '@' and a '.' after it. */
static int isValidEmail(const char *email) {
    const char *at = strchr(email, '@');
    if (at == NULL) return 0;
    const char *dot = strchr(at, '.');
    if (dot == NULL) return 0;
    return 1;
}

static int isDuplicateID(const Supplier suppliers[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (suppliers[i].active && suppliers[i].id == id) {
            return 1;
        }
    }
    return 0;
}

void addSupplier(Supplier suppliers[], int *count) {
    if (*count >= MAX_SUPPLIERS) {
        printf("Supplier list is full.\n");
        return;
    }

    Supplier s;
    s.id = readInt("Enter Supplier ID: ", 1, 999999);

    if (isDuplicateID(suppliers, *count, s.id)) {
        printf("A supplier with that ID already exists.\n");
        return;
    }

    readString("Enter Supplier Name: ", s.name, sizeof(s.name));

    char email[];
    do {
        readString("Enter Email: ", email, sizeof(email));
        if (!isValidEmail(email)) {
            printf("Invalid email format. Try again.\n");
        }
    } while (!isValidEmail(email));
    strcpy(s.email, email);

    readString("Enter Telephone: ", s.telephone, sizeof(s.telephone));
    readString("Enter Town/Location: ", s.town, sizeof(s.town));
    s.active = 1;

    suppliers[*count] = s;
    (*count)++;
    printf("Supplier added successfully.\n");
}

void displaySuppliers(const Supplier suppliers[], int count) {
    if (count == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    printf("\n%-6s %-20s %-25s %-15s %-15s\n",
           "ID", "Name", "Email", "Telephone", "Town");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        if (suppliers[i].active) {
            printf("%-6d %-20s %-25s %-15s %-15s\n",
                   suppliers[i].id, suppliers[i].name, suppliers[i].email,
                   suppliers[i].telephone, suppliers[i].town);
        }
    }
}

void searchSupplierByID(const Supplier suppliers[], int count) {
    int id = readInt("Enter Supplier ID to search: ", 1, 999999);

    for (int i = 0; i < count; i++) {
        if (suppliers[i].active && suppliers[i].id == id) {
            printf("Found: %s | %s | %s | %s\n",
                   suppliers[i].name, suppliers[i].email,
                   suppliers[i].telephone, suppliers[i].town);
            return;
        }
    }
    printf("Supplier with ID %d not found.\n", id);
}

void searchSupplierByName(const Supplier suppliers[], int count) {
    char name[50];
    readString("Enter name (or part of name) to search: ", name, sizeof(name));

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (suppliers[i].active && strstr(suppliers[i].name, name) != NULL) {
            printf("Match: ID %d | %s | %s | %s\n",
                   suppliers[i].id, suppliers[i].name,
                   suppliers[i].email, suppliers[i].town);
            found = 1;
        }
    }
    if (!found) {
        printf("No supplier matching \"%s\" found.\n", name);
    }
}

void supplierReport(const Supplier suppliers[], int count) {
    int active = 0;
    for (int i = 0; i < count; i++) {
        if (suppliers[i].active) active++;
    }

    printf("\n---- SUPPLIER REPORT ----\n");
    printf("Total Suppliers Registered: %d\n", active);
    displaySuppliers(suppliers, count);
}
