#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void reportsMenu(void)
{
    int choice;

    do
    {
        printf("\nREPORTS\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");

        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1:
                employeeReport();
                break;

            case 2:
                displayBudgetReport();
                break;

            case 3:
                supplierReport();
                break;

            case 4:
                displayAssetReport();
                break;

            case 5:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice. Please enter 1-5.\n");
        }

    } while (choice != 5);
}