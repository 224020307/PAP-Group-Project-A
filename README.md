# Municipal Financial Management System (MFMS)

**Course:** PAP521S – Programming in Practice (NUST)
**Project:** Project A
**Group:** Project A

## Group Members

| Student | Student number |
|---|---|
| Wame Griffiths | 224029339 |
| Ameer Majiet | 223067172 |
| Lasarus Lucas | 216083443 |
| Ethan Khembo | 224020307 |
| Shikongo Gerson | 224042823 |
| Thomas Nikanor | 225000431 |
| Werner Maria | 223039136 |

## Project Description

MFMS is a console-based program written in C that helps a municipal finance office manage employees, budgets, suppliers and assets from one menu. It is split into modules (one `.c` and `.h` file each) and keeps its records in memory while the program runs.

## System Features

- **Main menu** – a looping menu for all modules; invalid options are rejected.
- **Employee management** – add, display and search employees; salary is calculated as basic + housing + transport + other allowance; employee report.
- **Budget management** – 7 departments; enter allocated budget and expenditure, rename and search departments, list over-budget departments; balance = allocated − expenditure; budget report.
- **Supplier management** – register, display and search suppliers (by ID or partial name); compare two suppliers; e-mail and telephone validation; duplicate e-mail check; supplier report.
- **Asset management** – add, display and search assets (by ID, name, type or department); update asset condition; total asset value; asset report.
- **Reports** – one menu that shows the employee, budget, supplier and asset reports.
- **Input validation** – empty text, invalid numbers, out-of-range values and invalid menu choices are rejected.

## Files

`main.c`, `employees.c/.h`, `budget.c/.h`, `suppliers.c/.h`, `assets.c/.h`, `reports.c/.h`

## Compilation Instructions

Requires a C compiler such as GCC (on Windows, MinGW-w64). Open a terminal in the project folder and compile all the `.c` files together.

**Windows (PowerShell):**

```
gcc (Get-ChildItem *.c).FullName -o main
```

**Windows (Command Prompt), Linux or macOS:**

```
gcc main.c employees.c budget.c suppliers.c assets.c reports.c -o main
```

This creates the executable `main.exe` on Windows, or `main` on Linux/macOS. Compile again after any change to the code.

## How to Run the System

**Windows (PowerShell):**

```
.\main.exe
```

**Linux / macOS:**

```
./main
```

Enter a number from the main menu (1–6) to open a module: 1 Employee Management, 2 Budget Management, 3 Supplier Management, 4 Asset Management, 5 Reports, 6 Exit. Each module has its own sub-menu with a "back" option that returns to the main menu.

## Individual Responsibilities

| Member | Responsibility |
|---|---|
| Ameer Majiet | Asset management (`assets.c`, `assets.h`) |
| Lasarus Lucas | Part 1: Employee management (`employees.c`, `employees.h`); reports module (`reports.c`, `reports.h`) |
| Ethan Khembo | Main program and menu (`main.c`), GitHub coordination, integration, testing and documentation |
| Shikongo Gerson | Part 3: Supplier management (`suppliers.c`, `suppliers.h`); header files |
| Thomas Nikanor | Part 2: Budget management (`budget.c`, `budget.h`) |
