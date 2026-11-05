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
         printf("\nREPORTS\n"
             "1. Employee Report\n"
             "2. Budget Report\n"
             "3. Supplier Report\n"
             "4. Asset Report\n"
             "5. Back to Main Menu\n");

        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1: employeeReport(); break;
            case 2: displayBudgetReport(); break;
            case 3: supplierReport(); break;
            case 4: displayAssetReport(); break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please enter 1-5.\n");
        }

    } while (choice != 5);
}
