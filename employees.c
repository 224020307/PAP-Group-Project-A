/*
* MFMS - Employee Management Module (Project A)
 * Uses arrays, strings and loops,
 * decisions, functions. No Struckt.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 100
#define NAME_SIZE 50
#define DEP_SIZE 30

/* One array per field. Position i in every array = employee i */
int    ids[MAX_EMPLOYEES];
char   names[MAX_EMPLOYEES][NAME_SIZE];
char   departments[MAX_EMPLOYEES][DEPT_SIZE];
double basicSalary[MAX_EMPLOYEES];
double housing[MAX_EMPLOYEES];
double transport[MAX_EMPLOYEES];
double otherAllowance[MAX_EMPLOYEES];
double totalSalary[MAX_EMPLOYEES];
int    employeeCount = 0;

/* ---------- Function prototypes ---------- */
void   readText(const char *prompt, char text[], int size);
int    readInt(const char *prompt);
double readMoney(const char *prompt);
int    findEmployeeById(int id);
double calculateSalary(double basic, double house, double trans, double other);
void   addEmployee(void);
void   displayEmployees(void);
void   searchEmployee(void);
void   employeeReport(void);
void   displayMenu(void);

/* ---------- Function prototypes ---------- */
void employeeMenu(void)
{
    int choice;

    do
    {
        displayMenu();
        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                employeeReport();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please enter 1 to 5.\n");
        }
    } while (choice != 5);

    return 0;
}

/* ---------- Menu ---------- */
void displayMenu(void)
{
    printf("\n========================================\n");
    printf("         EMPLOYEE MANAGEMENT\n");
    printf("========================================\n");
    printf("1. Add Employee\n");
    printf("2. Display Employees\n");
    printf("3. Search Employee\n");
    printf("4. Employee Report\n");
    printf("5. Back / Exit\n");
}

/* ---------- Input helpers (validation) ---------- */

/* Reads a line of text (spaces allowed). Rejects empty input. */
void readText(const char *prompt, char text[], int size)
{
    while (1)
    {
        printf("%s", prompt);

        if (fgets(text, size, stdin) == NULL)
        {
            exit(0); /* input ended */
        }

        /* If there is no newline, the line was too long: discard the rest */
        if (strchr(text, '\n') == NULL)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
        }

        /* Remove the newline added by fgets() */
        text[strcspn(text, "\n")] = '\0';

        if (strlen(text) > 0)
        {
            return;
        }

        printf("Input cannot be empty. Try again.\n");
    }
}

/* Reads a whole number. Repeats until the user types a valid one. */
int readInt(const char *prompt)
{
    char line[50];
    int value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            exit(0);
        }

        if (sscanf(line, "%d", &value) == 1)
        {
            return value;
        }

        printf("Invalid number. Try again.\n");
    }
}

/* Reads an amount that is zero or more. */
double readMoney(const char *prompt)
{
    char line[50];
    double value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            exit(0);
        }

        if (sscanf(line, "%lf", &value) != 1)
        {
            printf("Invalid number. Try again.\n");
        }
        else if (value < 0)
        {
            printf("Amount cannot be negative. Try again.\n");
        }
        else
        {
            return value;
        }
    }
}

/* ---------- Employee functions ---------- */

/* Returns the position of the employee, or -1 if not found (linear search) */
int findEmployeeById(int id)
{
    for (int i = 0; i < employeeCount; i++)
    {
        if (ids[i] == id)
        {
            return i;
        }
    }
    return -1;
}

/* Total Salary = Basic + Housing + Transport + Other */
double calculateSalary(double basic, double house, double trans, double other)
{
    return basic + house + trans + other;
}

void addEmployee(void)
{
    char tempName[NAME_SIZE];
    char tempDept[DEPT_SIZE];
    int id;

    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("Employee list is full!\n");
        return;
    }

    id = readInt("Enter Employee ID: ");

    if (id <= 0)
    {
        printf("ID must be greater than 0.\n");
        return;
    }

    if (findEmployeeById(id) != -1)
    {
        printf("An employee with ID %d already exists.\n", id);
        return;
    }

    readText("Enter Name: ", tempName, NAME_SIZE);
    readText("Enter Department: ", tempDept, DEPT_SIZE);

    int i = employeeCount;

    ids[i] = id;
    strcpy(names[i], tempName);
    strcpy(departments[i], tempDept);
    basicSalary[i]    = readMoney("Enter Basic Salary: ");
    housing[i]        = readMoney("Enter Housing Allowance: ");
    transport[i]      = readMoney("Enter Transport Allowance: ");
    otherAllowance[i] = readMoney("Enter Other Allowance: ");
    totalSalary[i]    = calculateSalary(basicSalary[i], housing[i],
                                        transport[i], otherAllowance[i]);

    employeeCount++;
    printf("Employee added successfully!\n");
}

void displayEmployees(void)
{
    if (employeeCount == 0)
    {
        printf("No employees to display.\n");
        return;
    }

    printf("---------------------------------------------------------\n");
    printf("\n%-6s %-20s %-15s %12s\n", "ID", "Name", "Department", "Total Salary");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i < employeeCount; i++)
    {
        printf("%-6d %-20s %-15s %12.2f\n",
               ids[i], names[i], departments[i], totalSalary[i]);
    }
}

void searchEmployee(void)
{
    int option;
    int found = 0;

    printf("Search by: 1. ID   2. Name\n");
    option = readInt("Enter option: ");

    if (option == 1)
    {
        int id = readInt("Enter Employee ID: ");
        int i = findEmployeeById(id);

        if (i != -1)
        {
            found = 1;
            printf("\n--- Employee Found ---\n");
            printf("ID: %d\n", ids[i]);
            printf("Name: %s\n", names[i]);
            printf("Department: %s\n", departments[i]);
            printf("Basic Salary: %.2f\n", basicSalary[i]);
            printf("Housing Allowance: %.2f\n", housing[i]);
            printf("Transport Allowance: %.2f\n", transport[i]);
            printf("Other Allowance: %.2f\n", otherAllowance[i]);
            printf("Total Salary: %.2f\n", totalSalary[i]);
        }
    }
    else if (option == 2)
    {
        char searchName[NAME_SIZE];
        readText("Enter Name: ", searchName, NAME_SIZE);

        for (int i = 0; i < employeeCount; i++)
        {
            if (strcmp(names[i], searchName) == 0)
            {
                found = 1;
                printf("ID: %d | Name: %s | Dept: %s | Total Salary: %.2f\n",
                       ids[i], names[i], departments[i], totalSalary[i]);
            }
        }
    }
    else
    {
        printf("Invalid option.\n");
        return;
    }

    if (!found)
    {
        printf("Employee not found.\n");
    }
}

void employeeReport(void)
{
    double total = 0;
    double highest;
    double lowest;

    if (employeeCount == 0)
    {
        printf("No employees to report on.\n");
        return;
    }

    /* Start highest and lowest with the first salary (see Week 5 notes) */
    highest = totalSalary[0];
    lowest = totalSalary[0];

    for (int i = 0; i < employeeCount; i++)
    {
        total = total + totalSalary[i];

        if (totalSalary[i] > highest)
        {
            highest = totalSalary[i];
        }
        if (totalSalary[i] < lowest)
        {
            lowest = totalSalary[i];
        }
    }

    printf("\n--- Employee Report ---\n");
    printf("Total Employees: %d\n", employeeCount);
    printf("Total Salary Expenditure: N$%.2f\n", total);
    printf("Average Salary: N$%.2f\n", total / employeeCount);
    printf("Highest Salary: N$%.2f\n", highest);
    printf("Lowest Salary: N$%.2f\n", lowest);
    printf("\n--- End Of Employee Report ---\n");
}
