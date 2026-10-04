#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS       100

#define SUPPLIER_NAME_LEN   80
#define SUPPLIER_EMAIL_LEN  80
#define SUPPLIER_TEL_LEN    20
#define SUPPLIER_TOWN_LEN   50

typedef struct {
    int  id;
    char name[SUPPLIER_NAME_LEN];
    char email[SUPPLIER_EMAIL_LEN];
    char telephone[SUPPLIER_TEL_LEN];
    char town[SUPPLIER_TOWN_LEN];
    int  active;            /* 1 = registered, 0 = removed/unused */
} Supplier;

void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplierByID(void);
void searchSupplierByName(void);
void compareSuppliers(void);
void supplierReport(void);

#endif 
