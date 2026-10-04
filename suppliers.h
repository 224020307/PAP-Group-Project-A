#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100

typedef struct {
    int  id;
    char name[];
    char email[];
    char telephone[];
    char town[];
    int  active; // 1 = in use, 0 = empty slot (lets you "delete" without shifting)
} Supplier;

void supplierMenu(Supplier suppliers[], int *count);
void addSupplier(Supplier suppliers[], int *count);
void displaySuppliers(const Supplier suppliers[], int count);
void searchSupplierByID(const Supplier suppliers[], int count);
void searchSupplierByName(const Supplier suppliers[], int count);
void supplierReport(const Supplier suppliers[], int count);

#endif
