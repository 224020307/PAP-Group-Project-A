#include <stdio.h>
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

static void displayMainMenu(void);

int main(void) {
int choice; 

do {
 displayMainMenu();
 choice = readInt("Enter your choice: ");

switch (choice) {
case 1:employeeMenu();
        break;
    case 2:budgetMenu();
        break;
    case 3:supplierMenu();
        break;
    case 4:assetMenu();
        break;
    case 5:reportsMenu();
        break;
    case 6:
                printf("Thank you for using the MFMS.\n");
break;

default: printf("Invalid choice. Choose 1-6\n");   

}
 } while (choice !=6);

 return 0;

}

static void displayMainMenu(void) {
printf("\n-----\n");
printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");

printf("\n-----\n");

    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}
                
