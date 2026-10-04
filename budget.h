#ifndef BUDGET_H
#define BUDGET_H

//number of departments
#define BUDGET_DEPTS 7
//size of each department
#define BUDGET_NAME_LEN 30

//Menu
void budgetMenu(void);
//Data entry
void enterBudget(int idx);
void enterExpenditure(int idx);
//Read expenditure

//Change the name of the department idx
void renameDepartment(int idx);

//Calculations
double calculateBudget(double allocated, double expenditure);
int isWithinBudget(double allocated, double expenditure);

//Searching
int searchDepartment(char name[]);

//Displaying options
void displayDepartment(int idx);
void displayBudget(void);
void displayOverBudget(void);

//Function for the reports module
double getTotalBudget(void);
double getTotalExpenditure(void);
double getTotalRemaining(void);
int countOverBudget(void);
void displayBudgetReport(void);

#endif

