/* employees.h
 * Header file for Employee Management functions
 * PAP521S - Programming in Practice
 */

#ifndef EMPLOYEES_H
#define EMPLOYEES_H

/* ---------- Constants ---------- */
#define MAX_EMPLOYEES 100
#define NAME_SIZE     50
#define DEPT_SIZE     30

/* ---------- Global Variables ---------- */
/* Declared here as extern, defined in employees.c */
extern int    ids[MAX_EMPLOYEES];
extern char   names[MAX_EMPLOYEES][NAME_SIZE];
extern char   departments[MAX_EMPLOYEES][DEPT_SIZE];
extern double basicSalary[MAX_EMPLOYEES];
extern double housing[MAX_EMPLOYEES];
extern double transport[MAX_EMPLOYEES];
extern double otherAllowance[MAX_EMPLOYEES];
extern double totalSalary[MAX_EMPLOYEES];
extern int    employeeCount;

/* ---------- Function Prototypes ---------- */
void   readText(const char *prompt, char text[], int size);
int    readInt(const char *prompt);
double readMoney(const char *prompt);

int    findEmployeeById(int id);
double calculateSalary(double basic, double house, double trans, double other);

void employeeMenu(void);
void   addEmployee(void);
void   displayEmployees(void);
void   searchEmployee(void);
void   employeeReport(void);
void   displayMenu(void);

#endif /* EMPLOYEES_H */
