/*
 * assets.h
 * Asset Management module - Municipal Financial Management System (MFMS)
 * PAP521S Project A  |  Student 4
 */
#ifndef ASSETS_H
#define ASSETS_H
 
#define MAX_ASSETS   100
#define ASSET_NAME_LEN   50
#define ASSET_TYPE_LEN   30
#define ASSET_DEPT_LEN   40
#define ASSET_COND_LEN   20
 
typedef struct {
    int    id;
    char   name[ASSET_NAME_LEN];
    char   type[ASSET_TYPE_LEN];
    double purchaseValue;               /* in N$ */
    char   department[ASSET_DEPT_LEN];
    char   condition[ASSET_COND_LEN];
} Asset;
 
/* ---- Called from main.c (menu option 4) ---- */
void assetMenu(void);
 
/* ---- Core operations ---- */
void addAsset(void);
void displayAssets(void);
void searchAsset(void);
void updateAssetCondition(void);
 
/* ---- Calculations / helpers for other modules (e.g. Reports) ---- */
double calculateTotalAssetValue(void);
int    getAssetCount(void);
void   displayAssetReport(void);        /* call this from reports.c */
 
/* ---- Optional: pre-load demo data (call once from main before the menu) ---- */
void loadSampleAssets(void);
 
#endif /* ASSETS_H */
