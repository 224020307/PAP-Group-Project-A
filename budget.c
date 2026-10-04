#include <stdio.h>
#include <string.h>
#include "budget.h"

char budgetNames[BUDGET_DEPTS][BUDGET_NAME_LEN]={
"IT Department", "Finance Department", "HR Department", "Operations Department", "Marketing Department", "Sales Department", "Procurement Department"
};
double budgetAllocated[BUDGET_DEPTS]={0};
double budgetSpent[BUDGET_DEPTS]={0};
double budgetRemaining[BUDGET_DEPTS]={0};
int budgetEntered[BUDGET_DEPTS]={0};

void clearBudgetInput(void){
    int c;
    c=getchar ();
    while (c != '\n' && c != EOF){
        c=getchar();
    }
}

//Read a whole number from minimum to maximum, it repeats until the input is valid
int readBudgetChoice(int min, int max){
    int value;
    while (scanf("%d", &value) !=1 || value<min || value > max){
        clearBudgetInput();
        printf("Invalid choice, please enter a number from %d to %d: ", min, max);
    }
    clearBudgetInput();
    return value;
}

//Reading an amount of money, the amount should be above 0
double readBudgetAmount(int allowZero){
    double value;
    while(scanf("%lf", &value) !=1 || value<0 || (allowZero==0 && value==0))
    {
        clearBudgetInput();
        if (allowZero==1)
        {
            printf("Invalid amount, please enter a non-negative number: ");
        }
        else{
            printf("Invalid amount, please enter a positive number: ");
        }
    }
    clearBudgetInput();
    return value;
}

//Data entry for each municipal department
void enterBudget(int idx){
    printf("Please enter budget for %s (N$): ", budgetNames[idx]);
    budgetAllocated[idx]=readBudgetAmount(0);
}
void enterExpenditure(int idx){
    printf("Please enter the expenditure for %s (N$): ", budgetNames[idx]);
    budgetSpent[idx]=readBudgetAmount(1);
}
void renameDepartment(int idx){
    char newName[100];
    printf("Please enter the new name for %s: ", budgetNames[idx]);
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")]= '\0';
    if (strlen(newName)==0){
        printf("The name cannot be empty. Name not changed.\n");
    }
    else if(strlen(newName)>= BUDGET_NAME_LEN){
        printf("The name is too long (maximum %d characters). Name not changed.\n", BUDGET_NAME_LEN -1);
    }
    else if (searchDepartment(newName) != -1){
        printf("A department with that name already exists, name not changed.\n");
    }
    else{
        strcpy(budgetNames[idx], newName);
        printf("Department renamed to %s.\n", budgetNames[idx]);
    }
}

//Budget calculations
double calculateBudget(double allocated, double expenditure){
    return allocated - expenditure;
}
int isWithinBudget(double allocated, double expenditure){
    if(expenditure <= allocated){
        return 1;
    }
    return 0;
}

//Search for a department
int searchDepartment(char name[]){
    int i;
    for(i=0; i<BUDGET_DEPTS; i++){
        if(strcmp(budgetNames[i], name)==0){
            return i;
        }
    }
    return -1;
}

//Displaying budget information
void displayDepartment(int idx){
    printf("\nDepartment: %s\n", budgetNames[idx]);
    printf("Allocated Budget: N$%.2f\n", budgetAllocated[idx]);
    printf("Expenditure: N$%.2f\n", budgetSpent[idx]);
    printf("Remaining Budget: N$%.2f\n", budgetRemaining[idx]);
    if (isWithinBudget(budgetAllocated[idx], budgetSpent[idx])==1){
        printf("Status: WITHIN BUDGET\n");
    }
    else{
        printf("Status: BUDGET EXCEEDED by N$%.2f\n", -budgetRemaining[idx]);
    }
}
void displayBudget(void){
    int i;
    int count=0;

    printf("\n-------BUDGET INFORMATION------\n");
    for(i=0; i<BUDGET_DEPTS; i++){
        if(budgetEntered[i]==1){
            displayDepartment(i);
            count++;
        }
    }
    if (count==0){
        printf("No department data was entered.\n");
    }
}
void displayOverBudget(void){
    int i;
    printf("\n------DEPARTMENTS OVER BUDGET------\n");
    if(countOverBudget()==0){
        printf("No department has exceeded its budget.\n");
    }
    else{
        for (i=0; i<BUDGET_DEPTS; i++){
            if (budgetEntered[i]==1 && isWithinBudget(budgetAllocated[i], budgetSpent[i])==0){
                printf("%-24s over by N$%.2f\n", budgetNames[i], -budgetRemaining[i]);
            }
        }
    }
}

double getTotalBudget(void){
    int i;
    double total=0;
    for(i=0; i<BUDGET_DEPTS; i++){
        if(budgetEntered[i]==1){
            total=total + budgetAllocated[i];
        }
    }
    return total;
}
double getTotalExpenditure(void){
    int i;
    double total=0;
    for(i=0; i<BUDGET_DEPTS; i++){
        if(budgetEntered[i]==1){
            total= total + budgetSpent[i];
        }
    }
    return total;
}
double getTotalRemaining(void){
    return calculateBudget(getTotalBudget(), getTotalExpenditure());
}
int countOverBudget(void){
    int i;
    int count=0;
    for(i=0; i< BUDGET_DEPTS; i++){
        if (budgetEntered[i]==1 && isWithinBudget(budgetAllocated[i], budgetSpent[i])==0){
            count++;
        }
    }
    return count;
}
void displayBudgetReport(void){
    int i;
    int count=0;
    printf("\n--------BUDGET REPORT--------\n");
    for(i=0; i<BUDGET_DEPTS; i++){
        if(budgetEntered[i]==1){
            count++;
        }
    }
    if (count==0){
        printf("No department data was entered.\n");
    }
    else{
        printf("Total Allocated Budget: N$%.2f\n", getTotalBudget());
        printf("Total Expenditure:    N$%.2f\n", getTotalExpenditure());
        printf("Total Remaining Budget: N$%.2f\n", getTotalRemaining());
        displayOverBudget();
    }
}

//Shows the numbered department list
void displayDepartmentList(void){
    int i;
    printf("\n------MUNICIPAL DEPARTMENTS------\n");
    for(i=0; i< BUDGET_DEPTS; i++){
        printf("%d. %s", i + 1, budgetNames[i]);
        if (budgetEntered[i]==1){
            printf(" (Data entered)");
        }
        printf("\n");
    }
    printf("0. Back\n");
}

//Lets the user pick a certain department and returns its index
int selectDepartment(void){
    int choice;
    displayDepartmentList();
    printf("\nSelect a department (0-%d): ", BUDGET_DEPTS);
    choice=readBudgetChoice(0, BUDGET_DEPTS);
    return choice -1;
}

//Menu option 1: Enters the data for one department
void enterDepartmentData(void){
    int idx;
    idx=selectDepartment();
    if (idx != -1){
        enterBudget(idx);
        enterExpenditure(idx);
        budgetRemaining[idx]=calculateBudget(budgetAllocated[idx], budgetSpent[idx]);
        budgetEntered[idx]=1;
        displayDepartment(idx);
    }
}

//Menu option 3, Search for a department by name
void searchDepartmentMenu(void){
    char name[100];
    int idx;
    printf("Please enter the department name to search for: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")]='\0';
    if (strlen(name)==0){
        printf("The department name cannot be empty.\n");
    }
    else{
        idx= searchDepartment(name);
        if (idx == -1){
            printf("No department named \"%s\" was found.\n", name);
        }
        else if (budgetEntered[idx]==0){
            printf("%s exists, but no data has been entered yet.\n", budgetNames[idx]);
        }
        else{
            displayDepartment(idx);
        }
    }
}

void renameDepartmentMenu(void){
    int idx;
    idx=selectDepartment();
    if(idx != -1){
        renameDepartment(idx);
    }
}
void budgetMenu(void){
    int choice;
    do{
        printf("\n----------------------------------------\n");
        printf("           BUDGET MANAGEMENT\n");
        printf("----------------------------------------\n");
        printf("1. Enter department budget and expenditure\n");
        printf("2. Display budget information\n");
        printf("3. Search for a department\n");
        printf("4. Show departments over their budget\n");
        printf("5. Budget summary report\n");
        printf("6. Rename a department\n");
        printf("0. Back to main menu\n");
        printf("Please enter your choice: ");
        choice= readBudgetChoice(0,6);

        switch (choice){
            case 1:
            enterDepartmentData();
            break;

            case 2:
            displayBudget();
            break;

            case 3:
            searchDepartmentMenu();
            break;

            case 4:
            displayOverBudget();
            break;

            case 5:
            displayBudgetReport();
            break;

            case 6:
            renameDepartmentMenu();
            break;

            case 0:
            printf("Returning to main menu....\n");
            break;
        }
    }while (choice !=0);
}
