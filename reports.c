/* reports.c
 * Reports Module for Municipal Financial Management System
 */

#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

/* ---------- Employee Report ---------- */
void employeeReport(void)
{
    double total = 0;
    double highest, lowest;

    if (employeeCount == 0)
    {
        printf("No employees to report on.\n");
        return;
    }

    highest = totalSalary[0];
    lowest  = totalSalary[0];

    for (int i = 0; i < employeeCount; i++)
    {
        total += totalSalary[i];
        if (totalSalary[i] > highest) highest = totalSalary[i];
        if (totalSalary[i] < lowest)  lowest  = totalSalary[i];
    }

    printf("\n--- Employee Report ---\n");
    printf("Total Employees: %d\n", employeeCount);
    printf("Average Salary: N$%.2f\n", total / employeeCount);
    printf("Highest Salary: N$%.2f\n", highest);
    printf("Lowest Salary: N$%.2f\n", lowest);
}

/* ---------- Budget Report ---------- */
void budgetReport(void)
{
    double totalBudget = 0;
    double totalExpenditure = 0;

    if (budgetCount == 0)
    {
        printf("No budget data available.\n");
        return;
    }

    printf("\n--- Budget Report ---\n");
    for (int i = 0; i < budgetCount; i++)
    {
        double remaining = allocated[i] - expenditure[i];
        totalBudget     += allocated[i];
        totalExpenditure+= expenditure[i];

        printf("Department: %s\n", departmentsBudget[i]);
        printf("Allocated: N$%.2f | Expenditure: N$%.2f | Remaining: N$%.2f | Status: %s\n",
               allocated[i], expenditure[i], remaining,
               (remaining < 0 ? "OVER BUDGET" : "WITHIN BUDGET"));
    }

    printf("\nTotal Allocated Budget: N$%.2f\n", totalBudget);
    printf("Total Expenditure: N$%.2f\n", totalExpenditure);
    printf("Remaining Budget: N$%.2f\n", totalBudget - totalExpenditure);
}

/* ---------- Supplier Report ---------- */
void supplierReport(void)
{
    if (supplierCount == 0)
    {
        printf("No suppliers registered.\n");
        return;
    }

    printf("\n--- Supplier Report ---\n");
    for (int i = 0; i < supplierCount; i++)
    {
        printf("ID: %d | Name: %s | Email: %s | Phone: %s | Town: %s\n",
               supplierIDs[i], supplierNames[i], supplierEmails[i],
               supplierPhones[i], supplierTowns[i]);
    }
}

/* ---------- Asset Report ---------- */
void assetReport(void)
{
    if (assetCount == 0)
    {
        printf("No assets registered.\n");
        return;
    }

    printf("\n--- Asset Report ---\n");
    for (int i = 0; i < assetCount; i++)
    {
        printf("ID: %d | Name: %s | Type: %s | Value: N$%.2f | Dept: %s | Condition: %s\n",
               assetIDs[i], assetNames[i], assetTypes[i],
               assetValues[i], assetDepartments[i], assetConditions[i]);
    }
}

/* ---------- Reports Menu ---------- */
void displayReports(void)
{
    int choice;
    do
    {
        printf("\n========== REPORTS ==========\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back\n");

        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1: employeeReport(); break;
            case 2: budgetReport();   break;
            case 3: supplierReport(); break;
            case 4: assetReport();    break;
            case 5: printf("Returning...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
}
