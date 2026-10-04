# PAP-Group-Project-A
Group project A

1. Wame Griffiths, 224029339
2. ⁠Ameer Majiet, 223067172 - Files:** `assets.c`, `assets.h`
**Description: Implements the municipal asset register. Assets are stored
in an array of structures (up to 100 records) with ID, name, type, purchase
value, department and condition.
**Features: - Add assets with full input validation (unique positive ID, non-empty
  name/department, positive purchase value, type and condition chosen from
  fixed lists)
- Display all assets in a formatted table
- Search by Asset ID, name (partial, case-insensitive), type or department
- Update an asset's condition
- Calculate total asset value
- Asset report with totals, average value, assets in poor condition and a
  count by asset type
**Main functions: `assetMenu()`, `addAsset()`, `displayAssets()`,
`searchAsset()`, `updateAssetCondition()`, `calculateTotalAssetValue()`,
`getAssetCount()`, `displayAssetReport()`
**Integration:** `main.c` calls `assetMenu()` for the Asset Management
option; `reports.c` calls `displayAssetReport()` for the Asset Report.

3. Lasarus Lucas, 216083443 Part 1: Employee management
4. Ethan Khembo, 224020307 
5. Shikongo Gerson, 224042823 Part 3: Supplier management
6. ⁠Thomas Nikanor, 225000431 Part 2: Budget management
7. Werner Maria 223039136
