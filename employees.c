#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 100

typedef struct {
    int id;
    char name[50];
    char department[30];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
    float otherAllowance;
    float totalSalary;
} Employee;

// Function prototypes
void addEmployee(Employee employees[], int *count);
void displayEmployees(Employee employees[], int count);
void searchEmployee(Employee employees[], int count, int id);
void calculateSalary(Employee *emp);

int main() {
    Employee employees[MAX_EMPLOYEES];
    int count = 0;
    int choice, id;

    while (1) {
        printf("\n===== Employee Management System =====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &count);
                break;
            case 2:
                displayEmployees(employees, count);
                break;
            case 3:
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                searchEmployee(employees, count, id);
                break;
            case 4:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Add Employee
void addEmployee(Employee employees[], int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("Employee list is full!\n");
        return;
    }

    Employee emp;
    printf("Enter Employee ID:\n");
    scanf("%d", &emp.id);
    printf("Enter Name:\n");
    scanf("%s", emp.name);
    printf("Enter Department:\n");
    scanf("%s", emp.department);
    printf("Enter Basic Salary:\n");
    scanf("%f", &emp.basicSalary);
    printf("Enter Housing Allowance:\n");
    scanf("%f", &emp.housingAllowance);
    printf("Enter Transport Allowance:\n");
    scanf("%f", &emp.transportAllowance);
    printf("Enter Other Allowance:\n");
    scanf("%f", &emp.otherAllowance);

    calculateSalary(&emp);

    employees[*count] = emp;
    (*count)++;

    printf("Employee added successfully!\n");
}

// Display Employees
void displayEmployees(Employee employees[], int count) {
    if (count == 0) {
        printf("No employees to display.\n");
        return;
    }

    printf("\n--- Employee List ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Dept: %s | Total Salary: %.2f\n",
               employees[i].id, employees[i].name, employees[i].department, employees[i].totalSalary);
    }
}

// Search Employee
void searchEmployee(Employee employees[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            printf("\n--- Employee Found ---\n");
            printf("ID: %d\n", employees[i].id);
            printf("Name: %s\n", employees[i].name);
            printf("Department: %s\n", employees[i].department);
            printf("Basic Salary: %.2f\n", employees[i].basicSalary);
            printf("Housing Allowance: %.2f\n", employees[i].housingAllowance);
            printf("Transport Allowance: %.2f\n", employees[i].transportAllowance);
            printf("Other Allowance: %.2f\n", employees[i].otherAllowance);
            printf("Total Salary: %.2f\n", employees[i].totalSalary);
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

// Calculate Salary
void calculateSalary(Employee *emp) {
    emp->totalSalary = emp->basicSalary +
                       emp->housingAllowance +
                       emp->transportAllowance +
                       emp->otherAllowance;
}
