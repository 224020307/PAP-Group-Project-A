oid reportsMenu(void)
{
    int choice;
    
do{
        printf("\REPORTS\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");
        choice = readInt("Enter your choice: ", 1-5);

        switch (choice)
        {
            case 1:
                displayEmployeeReport();
                pauseScreen();
                break;
            case 2:
                displayBudgetReport();
                pauseScreen();
                break;
            case 3:
                supplierReport();
                pauseScreen();
                break;
            case 4:
                displayAssetReport();
                pauseScreen();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
        }
    } while (choice != 5);
}