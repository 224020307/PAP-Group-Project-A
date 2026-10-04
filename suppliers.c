#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"

/* Supplier data is private to this module. */
static Supplier suppliers[MAX_SUPPLIERS];
static int supplierCount = 0;

/* ---------- private input helpers (this file only) ---------- */

/* Discard the rest of the current input line. */
static void clearLine(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}

/* Read a whole number between min and max. Asks again until valid. */
static int readIntRange(const char *prompt, int min, int max) {
    char line[64];
    char *end;
    long value;

    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nInput closed. Exiting.\n");
            exit(EXIT_FAILURE);
        }
        if (strchr(line, '\n') == NULL && !feof(stdin)) {
            clearLine();                     /* line was too long */
            printf("Input too long. Try again.\n");
            continue;
        }
        line[strcspn(line, "\n")] = '\0';

        if (line[0] == '\0') {
            printf("Input cannot be empty. Enter a whole number.\n");
            continue;
        }
        value = strtol(line, &end, 10);
        if (*end != '\0') {
            printf("Invalid input. Enter a whole number.\n");
            continue;
        }
        if (value < min || value > max) {
            printf("Value must be between %d and %d.\n", min, max);
            continue;
        }
        return (int)value;
    }
}

/* Read a non-empty line into dest (at most size-1 characters). */
static void readNonEmpty(const char *prompt, char *dest, size_t size) {
    size_t i;
    int blank;

    while (1) {
        printf("%s", prompt);
        if (fgets(dest, (int)size, stdin) == NULL) {
            printf("\nInput closed. Exiting.\n");
            exit(EXIT_FAILURE);
        }
        if (strchr(dest, '\n') == NULL && !feof(stdin)) {
            clearLine();                     /* line did not fit in dest */
            printf("Input too long (maximum %d characters).\n", (int)size - 1);
            continue;
        }
        dest[strcspn(dest, "\n")] = '\0';

        blank = 1;
        for (i = 0; dest[i] != '\0'; i++) {
            if (!isspace((unsigned char)dest[i])) {
                blank = 0;
                break;
            }
        }
        if (blank) {
            printf("Input cannot be empty. Try again.\n");
            continue;
        }
        return;
    }
}

/* ---------- validation and lookup helpers ---------- */

/* Email must have no spaces, one '@' that is not first, and a '.' after
 * the '@' that is neither right after it nor the last character. */
static int isValidEmail(const char *email) {
    const char *at;
    const char *dot;

    if (strchr(email, ' ') != NULL) return 0;

    at = strchr(email, '@');
    if (at == NULL || at == email) return 0;
    if (strchr(at + 1, '@') != NULL) return 0;

    dot = strchr(at, '.');
    if (dot == NULL || dot == at + 1) return 0;
    if (dot[1] == '\0') return 0;
    return 1;
}

/* Telephone: 7 to 15 digits, with an optional leading '+'. */
static int isValidTelephone(const char *tel) {
    size_t len = strlen(tel);
    size_t start = (tel[0] == '+') ? 1 : 0;
    size_t i;

    if (len - start < 7 || len - start > 15) return 0;
    for (i = start; i < len; i++) {
        if (!isdigit((unsigned char)tel[i])) return 0;
    }
    return 1;
}

/* Returns the index of the active supplier with this ID, or -1. */
static int findSupplierIndex(int id) {
    for (int i = 0; i < supplierCount; i++) {
        if (suppliers[i].active && suppliers[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* Returns 1 if another active supplier already uses this email. */
static int isDuplicateEmail(const char *email) {
    for (int i = 0; i < supplierCount; i++) {
        if (suppliers[i].active && strcmp(suppliers[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

/* Case-insensitive "contains": returns 1 if needle is inside text. */
static int containsIgnoreCase(const char *text, const char *needle) {
    size_t tlen = strlen(text);
    size_t nlen = strlen(needle);
    size_t i, j;

    if (nlen > tlen) return 0;
    for (i = 0; i + nlen <= tlen; i++) {
        for (j = 0; j < nlen; j++) {
            if (tolower((unsigned char)text[i + j]) !=
                tolower((unsigned char)needle[j])) {
                break;
            }
        }
        if (j == nlen) return 1;
    }
    return 0;
}

/* ---------- menu ---------- */

void supplierMenu(void) {
    int choice;
    do {
        printf("\n---- SUPPLIER MANAGEMENT ----\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search by ID\n");
        printf("4. Search by Name\n");
        printf("5. Compare Two Suppliers\n");
        printf("6. Supplier Report\n");
        printf("7. Back to Main Menu\n");
        choice = readIntRange("Enter your choice: ", 1, 7);

        switch (choice) {
            case 1:
                addSupplier();
                break;
            case 2:
                displaySuppliers();
                break;
            case 3:
                searchSupplierByID();
                break;
            case 4:
                searchSupplierByName();
                break;
            case 5:
                compareSuppliers();
                break;
            case 6:
                supplierReport();
                break;
            case 7:
                printf("Returning to main menu...\n");
                break;
        }
    } while (choice != 7);
}

/* ---------- supplier operations ---------- */

void addSupplier(void) {
    if (supplierCount >= MAX_SUPPLIERS) {
        printf("Supplier list is full.\n");
        return;
    }

    Supplier s;
    s.id = readIntRange("Enter Supplier ID: ", 1, 999999);

    if (findSupplierIndex(s.id) != -1) {
        printf("A supplier with that ID already exists.\n");
        return;
    }

    readNonEmpty("Enter Supplier Name: ", s.name, sizeof(s.name));

    while (1) {
        readNonEmpty("Enter Email: ", s.email, sizeof(s.email));
        if (!isValidEmail(s.email)) {
            printf("Invalid email format (example: name@company.com). Try again.\n");
        } else if (isDuplicateEmail(s.email)) {
            printf("A supplier with that email already exists. Try again.\n");
        } else {
            break;
        }
    }

    do {
        readNonEmpty("Enter Telephone: ", s.telephone, sizeof(s.telephone));
        if (!isValidTelephone(s.telephone)) {
            printf("Invalid telephone. Use 7-15 digits, optional leading '+'.\n");
        }
    } while (!isValidTelephone(s.telephone));

    readNonEmpty("Enter Town/Location: ", s.town, sizeof(s.town));
    s.active = 1;

    suppliers[supplierCount] = s;
    supplierCount++;
    printf("Supplier added successfully.\n");
}

void displaySuppliers(void) {
    int shown = 0;

    printf("\n%-6s %-22s %-28s %-16s %-20s\n",
           "ID", "Name", "Email", "Telephone", "Town");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < supplierCount; i++) {
        if (suppliers[i].active) {
            printf("%-6d %-22s %-28s %-16s %-20s\n",
                   suppliers[i].id, suppliers[i].name, suppliers[i].email,
                   suppliers[i].telephone, suppliers[i].town);
            shown++;
        }
    }
    if (shown == 0) {
        printf("No suppliers registered yet.\n");
    }
}

void searchSupplierByID(void) {
    int id = readIntRange("Enter Supplier ID to search: ", 1, 999999);
    int index = findSupplierIndex(id);

    if (index == -1) {
        printf("Supplier with ID %d not found.\n", id);
        return;
    }
    printf("Found: %s | %s | %s | %s\n",
           suppliers[index].name, suppliers[index].email,
           suppliers[index].telephone, suppliers[index].town);
}

void searchSupplierByName(void) {
    char name[SUPPLIER_NAME_LEN];
    readNonEmpty("Enter name (or part of name) to search: ", name, sizeof(name));

    int found = 0;
    for (int i = 0; i < supplierCount; i++) {
        if (suppliers[i].active && containsIgnoreCase(suppliers[i].name, name)) {
            printf("Match: ID %d | %s | %s | %s | %s\n",
                   suppliers[i].id, suppliers[i].name, suppliers[i].email,
                   suppliers[i].telephone, suppliers[i].town);
            found = 1;
        }
    }
    if (!found) {
        printf("No supplier matching \"%s\" found.\n", name);
    }
}


void compareSuppliers(void) {
    int idA, idB, a, b;

    if (supplierCount < 2) {
        printf("At least two suppliers are needed to compare.\n");
        return;
    }

    idA = readIntRange("Enter first Supplier ID: ", 1, 999999);
    idB = readIntRange("Enter second Supplier ID: ", 1, 999999);
    a = findSupplierIndex(idA);
    b = findSupplierIndex(idB);

    if (a == -1 || b == -1) {
        printf("One or both supplier IDs were not found.\n");
        return;
    }
    if (a == b) {
        printf("Please choose two different suppliers.\n");
        return;
    }

    printf("\n%-12s %-28s %-28s\n", "", "Supplier A", "Supplier B");
    printf("-------------------------------------------------------------------\n");
    printf("%-12s %-28d %-28d\n", "ID", suppliers[a].id, suppliers[b].id);
    printf("%-12s %-28s %-28s\n", "Name", suppliers[a].name, suppliers[b].name);
    printf("%-12s %-28s %-28s\n", "Email", suppliers[a].email, suppliers[b].email);
    printf("%-12s %-28s %-28s\n", "Telephone",
           suppliers[a].telephone, suppliers[b].telephone);
    printf("%-12s %-28s %-28s\n", "Town", suppliers[a].town, suppliers[b].town);

    if (strcmp(suppliers[a].town, suppliers[b].town) == 0) {
        printf("\nResult: both suppliers are in the same town (%s).\n",
               suppliers[a].town);
    } else {
        printf("\nResult: the suppliers are in different towns.\n");
    }
}

void supplierReport(void) {
    int active = 0;
    for (int i = 0; i < supplierCount; i++) {
        if (suppliers[i].active) active++;
    }

    printf("\n---- SUPPLIER REPORT ----\n");
    printf("Total Suppliers Registered: %d\n", active);
    displaySuppliers();
}
