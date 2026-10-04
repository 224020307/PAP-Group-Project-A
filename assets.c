 *
 * assets.c
 * Asset Management module - Municipal Financial Management System (MFMS)
 * PAP521S Project A  |  Student 4
 *
 * Features: add, display, search (ID / name / type / department),
 *           update condition, total value, asset report, input validation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assets.h"
 
#define NUM_TYPES 6
#define NUM_CONDITIONS 4
 
/* ------------------------------------------------------------------ */
/* Data storage: array of structures (private to this file)            */
/* ------------------------------------------------------------------ */
static Asset assets[MAX_ASSETS];
static int   assetCount = 0;
 
static const char *ASSET_TYPES[NUM_TYPES] = {
    "Vehicle", "Computer", "Building", "Equipment", "Office Furniture", "Other"
};
static const char *CONDITIONS[NUM_CONDITIONS] = {
    "Good", "Fair", "Poor", "Needs Repair"
};
 
/* ------------------------------------------------------------------ */
/* Private helper prototypes                                           */
/* ------------------------------------------------------------------ */
static void   trimSpaces(char *s);
static void   readLine(const char *prompt, char *buf, int size);
static int    readInt(const char *prompt, int min, int max);
static double readPositiveDouble(const char *prompt);
static void   readNonEmpty(const char *prompt, char *buf, int size);
static int    chooseFromList(const char *title, const char *list[], int n);
static int    findAssetById(int id);
static int    containsIgnoreCase(const char *text, const char *part);
static void   printTableHeader(void);
static void   printAssetRow(const Asset *a);
 
/* ================================================================== */
/* Input helpers (validation)                                          */
/* ================================================================== */
 
/* Remove leading and trailing whitespace in place. */
static void trimSpaces(char *s)
{
    int start = 0;
    int len;
 
    while (s[start] != '\0' && isspace((unsigned char)s[start])) {
        start++;
    }
    if (start > 0) {
        memmove(s, s + start, strlen(s + start) + 1);
    }
    len = (int)strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[--len] = '\0';
    }
}
 
/* Read one line safely with fgets (never overflows buf). */
static void readLine(const char *prompt, char *buf, int size)
{
    size_t len;
    int c;
 
    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {
        printf("\nInput closed. Exiting.\n");
        exit(0);
    }
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        /* line was longer than the buffer: discard the rest */
        while ((c = getchar()) != '\n' && c != EOF) {
            ;
        }
    }
    trimSpaces(buf);
}
 
/* Keep asking until the user enters a whole number in [min, max]. */
static int readInt(const char *prompt, int min, int max)
{
    char line[64];
    char *end;
    long value;
 
    while (1) {
        readLine(prompt, line, (int)sizeof(line));
        if (strlen(line) == 0) {
            printf("  Error: input cannot be empty.\n");
            continue;
        }
        value = strtol(line, &end, 10);
        if (*end != '\0') {
            printf("  Error: '%s' is not a valid whole number.\n", line);
        } else if (value < min || value > max) {
            printf("  Error: enter a number between %d and %d.\n", min, max);
        } else {
            return (int)value;
        }
    }
}
 
/* Keep asking until the user enters a number greater than 0. */
static double readPositiveDouble(const char *prompt)
{
    char line[64];
    char *end;
    double value;
 
    while (1) {
        readLine(prompt, line, (int)sizeof(line));
        if (strlen(line) == 0) {
            printf("  Error: input cannot be empty.\n");
            continue;
        }
        value = strtod(line, &end);
        if (*end != '\0') {
            printf("  Error: '%s' is not a valid number.\n", line);
        } else if (value < 0) {
            printf("  Error: value cannot be negative.\n");
        } else if (value == 0) {
            printf("  Error: value must be greater than zero.\n");
        } else if (value > 1000000000.0) {
            printf("  Error: value is unrealistically large.\n");
        } else {
            return value;
        }
    }
}
 
/* Keep asking until the user types something that is not blank. */
static void readNonEmpty(const char *prompt, char *buf, int size)
{
    while (1) {
        readLine(prompt, buf, size);
        if (strlen(buf) > 0) {
            return;
        }
        printf("  Error: this field cannot be empty.\n");
    }
}
 
/* Show a numbered list and return the chosen index (0-based). */
static int chooseFromList(const char *title, const char *list[], int n)
{
    int i;
    printf("%s\n", title);
    for (i = 0; i < n; i++) {
        printf("  %d. %s\n", i + 1, list[i]);
    }
    return readInt("  Choose option: ", 1, n) - 1;
}
 
/* ================================================================== */
/* Lookup / string helpers                                             */
/* ================================================================== */
 
/* Linear search by ID. Returns array index or -1 if not found. */
static int findAssetById(int id)
{
    int i;
    for (i = 0; i < assetCount; i++) {
        if (assets[i].id == id) {
            return i;
        }
    }
    return -1;
}
 
/* Case-insensitive "does text contain part?" (returns 1 or 0). */
static int containsIgnoreCase(const char *text, const char *part)
{
    char a[ASSET_NAME_LEN + ASSET_DEPT_LEN];
    char b[ASSET_NAME_LEN + ASSET_DEPT_LEN];
    size_t i;
 
    strncpy(a, text, sizeof(a) - 1);
    a[sizeof(a) - 1] = '\0';
    strncpy(b, part, sizeof(b) - 1);
    b[sizeof(b) - 1] = '\0';
 
    for (i = 0; i < strlen(a); i++) a[i] = (char)tolower((unsigned char)a[i]);
    for (i = 0; i < strlen(b); i++) b[i] = (char)tolower((unsigned char)b[i]);
 
    return strstr(a, b) != NULL;
}
 
/* ================================================================== */
/* Output helpers                                                      */
/* ================================================================== */
static void printTableHeader(void)
{
    printf("\n%-6s %-22s %-17s %-15s %-16s %-12s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printf("------------------------------------------------------"
           "-------------------------------\n");
}
 
static void printAssetRow(const Asset *a)
{
    printf("%-6d %-22.22s %-17.17s %-15.2f %-16.16s %-12.12s\n",
           a->id, a->name, a->type, a->purchaseValue,
           a->department, a->condition);
}
 
/* ================================================================== */
/* Core operations                                                     */
/* ================================================================== */
 
/* Add a new asset after validating every field. */
void addAsset(void)
{
    Asset a;
    int id;
 
    printf("\n--- ADD NEW ASSET ---\n");
 
    if (assetCount >= MAX_ASSETS) {
        printf("Asset register is full (%d assets). Cannot add more.\n",
               MAX_ASSETS);
        return;
    }
 
    /* Asset ID: positive and must be unique */
    while (1) {
        id = readInt("Asset ID (positive number): ", 1, 999999);
        if (findAssetById(id) != -1) {
            printf("  Error: Asset ID %d already exists.\n", id);
        } else {
            break;
        }
    }
    a.id = id;
 
    readNonEmpty("Asset name: ", a.name, ASSET_NAME_LEN);
    strcpy(a.type, ASSET_TYPES[chooseFromList("Asset type:", ASSET_TYPES,
                                              NUM_TYPES)]);
    a.purchaseValue = readPositiveDouble("Purchase value (N$): ");
    readNonEmpty("Department: ", a.department, ASSET_DEPT_LEN);
    strcpy(a.condition, CONDITIONS[chooseFromList("Condition:", CONDITIONS,
                                                  NUM_CONDITIONS)]);
 
    assets[assetCount] = a;
    assetCount++;
    printf("\nAsset '%s' added successfully.\n", a.name);
}
 
/* Display every asset in a table. */
void displayAssets(void)
{
    int i;
 
    printf("\n--- ASSET REGISTER ---\n");
    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }
    printTableHeader();
    for (i = 0; i < assetCount; i++) {
        printAssetRow(&assets[i]);
    }
    printf("\nTotal assets: %d\n", assetCount);
}
 
/* Search by ID, name, type or department. */
void searchAsset(void)
{
    int choice, i, found = 0;
    char keyword[ASSET_NAME_LEN];
 
    printf("\n--- SEARCH ASSETS ---\n");
    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }
 
    printf("1. Search by Asset ID\n");
    printf("2. Search by Name (partial match)\n");
    printf("3. Search by Asset Type\n");
    printf("4. Search by Department (partial match)\n");
    choice = readInt("Choose search option: ", 1, 4);
 
    switch (choice) {
    case 1: {
        int id = readInt("Enter Asset ID: ", 1, 999999);
        int idx = findAssetById(id);
        if (idx != -1) {
            printTableHeader();
            printAssetRow(&assets[idx]);
            found = 1;
        }
        break;
    }
    case 2:
        readNonEmpty("Enter name (or part of it): ", keyword, ASSET_NAME_LEN);
        for (i = 0; i < assetCount; i++) {
            if (containsIgnoreCase(assets[i].name, keyword)) {
                if (!found) printTableHeader();
                printAssetRow(&assets[i]);
                found++;
            }
        }
        break;
    case 3: {
        const char *type = ASSET_TYPES[chooseFromList("Asset type:",
                                                      ASSET_TYPES, NUM_TYPES)];
        for (i = 0; i < assetCount; i++) {
            if (strcmp(assets[i].type, type) == 0) {
                if (!found) printTableHeader();
                printAssetRow(&assets[i]);
                found++;
            }
        }
        break;
    }
    case 4:
        readNonEmpty("Enter department (or part of it): ", keyword,
                     ASSET_NAME_LEN);
        for (i = 0; i < assetCount; i++) {
            if (containsIgnoreCase(assets[i].department, keyword)) {
                if (!found) printTableHeader();
                printAssetRow(&assets[i]);
                found++;
            }
        }
        break;
    }
 
    if (!found) {
        printf("\nNo matching assets found.\n");
    } else {
        printf("\n%d asset(s) found.\n", found);
    }
}
 
/* Change the condition of an existing asset. */
void updateAssetCondition(void)
{
    int id, idx;
 
    printf("\n--- UPDATE ASSET CONDITION ---\n");
    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }
    id = readInt("Enter Asset ID: ", 1, 999999);
    idx = findAssetById(id);
    if (idx == -1) {
        printf("Asset ID %d not found.\n", id);
        return;
    }
    printf("Current condition of '%s': %s\n", assets[idx].name,
           assets[idx].condition);
    strcpy(assets[idx].condition,
           CONDITIONS[chooseFromList("New condition:", CONDITIONS,
                                     NUM_CONDITIONS)]);
    printf("Condition updated to '%s'.\n", assets[idx].condition);
}
 
/* ================================================================== */
/* Calculations and report support                                     */
/* ================================================================== */
 
/* Sum of the purchase values of all assets (returns a value). */
double calculateTotalAssetValue(void)
{
    double total = 0.0;
    int i;
    for (i = 0; i < assetCount; i++) {
        total += assets[i].purchaseValue;
    }
    return total;
}
 
/* Number of assets currently registered (for the Reports module). */
int getAssetCount(void)
{
    return assetCount;
}
 
/* Asset report: full register + summary figures. */
void displayAssetReport(void)
{
    int i, poor = 0;
    int typeCount[NUM_TYPES] = {0};
    int t;
 
    printf("\n========================================\n");
    printf("            ASSET REPORT\n");
    printf("========================================\n");
 
    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }
 
    printTableHeader();
    for (i = 0; i < assetCount; i++) {
        printAssetRow(&assets[i]);
 
        if (strcmp(assets[i].condition, "Poor") == 0 ||
            strcmp(assets[i].condition, "Needs Repair") == 0) {
            poor++;
        }
        for (t = 0; t < NUM_TYPES; t++) {
            if (strcmp(assets[i].type, ASSET_TYPES[t]) == 0) {
                typeCount[t]++;
            }
        }
    }
 
    printf("\nTotal Assets          : %d\n", assetCount);
    printf("Total Asset Value     : N$%.2f\n", calculateTotalAssetValue());
    printf("Average Asset Value   : N$%.2f\n",
           calculateTotalAssetValue() / assetCount);
    printf("Assets in Poor/Needs Repair condition: %d\n", poor);
    printf("\nAssets by type:\n");
    for (t = 0; t < NUM_TYPES; t++) {
        if (typeCount[t] > 0) {
            printf("  %-18s: %d\n", ASSET_TYPES[t], typeCount[t]);
        }
    }
}
 
/* ================================================================== */
/* Demo data                                                           */
/* ================================================================== */
static void addSample(int id, const char *name, const char *type,
                      double value, const char *dept, const char *cond)
{
    if (assetCount >= MAX_ASSETS) return;
    assets[assetCount].id = id;
    strcpy(assets[assetCount].name, name);
    strcpy(assets[assetCount].type, type);
    assets[assetCount].purchaseValue = value;
    strcpy(assets[assetCount].department, dept);
    strcpy(assets[assetCount].condition, cond);
    assetCount++;
}
 
void loadSampleAssets(void)
{
    addSample(1001, "Toyota Hilux Bakkie", "Vehicle", 450000.00, "Roads", "Good");
    addSample(1002, "Dell Latitude Laptop", "Computer", 18500.00, "Finance", "Good");
    addSample(1003, "Town Hall Building", "Building", 12500000.00, "Administration", "Fair");
    addSample(1004, "Water Pump Unit", "Equipment", 85000.00, "Water", "Needs Repair");
    addSample(1005, "Council Boardroom Table", "Office Furniture", 22000.00, "Administration", "Good");
}
 
/* ================================================================== */
/* Asset management menu                                               */
/* ================================================================== */
void assetMenu(void)
{
    int choice;
 
    do {
        printf("\n========================================\n");
        printf("          ASSET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Asset\n");
        printf("2. Display All Assets\n");
        printf("3. Search Assets\n");
        printf("4. Update Asset Condition\n");
        printf("5. Show Total Asset Value\n");
        printf("6. Back to Main Menu\n");
        choice = readInt("Enter your choice: ", 1, 6);
 
        switch (choice) {
        case 1: addAsset();            break;
        case 2: displayAssets();       break;
        case 3: searchAsset();         break;
        case 4: updateAssetCondition(); break;
        case 5:
            printf("\nTotal value of %d asset(s): N$%.2f\n",
                   assetCount, calculateTotalAssetValue());
            break;
        case 6: printf("Returning to main menu...\n"); break;
        }
    } while (choice != 6);
}
