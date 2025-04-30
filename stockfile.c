#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILENAME "stock.txt"

typedef struct {
    int item_code;
    char item_name[50];
    int quantity;
    int reorder_level;
} StockItem;

void createStockFile(int n) {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    StockItem item;
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for item %d:\n", i + 1);
        printf("Item Code: ");
        scanf("%d", &item.item_code);
        printf("Item Name: ");
        scanf(" %[^\n]", item.item_name); 
        printf("Quantity: ");
        scanf("%d", &item.quantity);
        printf("Reorder Level: ");
        scanf("%d", &item.reorder_level);

        fwrite(&item, sizeof(StockItem), 1, fp);
    }

    fclose(fp);
    printf("\nStock file created successfully.\n");
}

void listLowStockItems() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    StockItem item;
    printf("\nItems with quantity below reorder level:\n");
    printf("Code\tName\t\tQty\tReorder Level\n");
    printf("-------------------------------------------------\n");

    while (fread(&item, sizeof(StockItem), 1, fp)) {
        if (item.quantity < item.reorder_level) {
            printf("%d\t%-15s\t%d\t%d\n", item.item_code, item.item_name, item.quantity, item.reorder_level);
        }
    }

    fclose(fp);
}

int main() {
    int n;
    printf("Enter number of stock items: ");
    scanf("%d", &n);

    createStockFile(n);
    listLowStockItems();

    return 0;
}
