#include <stdio.h>
#include <string.h>
#include "inventory.h"

struct Product inventory[MAX_PRODUCTS];
int num_products = 0;

void addProduct() {
    if (num_products >= MAX_PRODUCTS) {
        printf("Inventory is full. Cannot add more products.\n");
        return;
    }

    struct Product new_product;

    printf("Enter product name: ");
    scanf(" %[^\n]", new_product.name);

    printf("Enter product location: ");
    scanf(" %[^\n]", new_product.location);

    printf("Enter product quantity: ");
    scanf("%d", &new_product.quantity);

    printf("Enter selling price: ");
    scanf("%f", &new_product.selling_price);

    printf("Enter profit margin (in percentage): ");
    scanf("%f", &new_product.profit_margin);

    inventory[num_products++] = new_product;
    printf("Product added successfully.\n");
}

void displayInventory() {
    if (num_products == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    printf("\nProduct Name\tLocation\tQuantity\tSelling Price\tProfit Margin\n");
    for (int i = 0; i < num_products; i++) {
        printf("%s\t%s\t%d\t\t%.2f\t\t%.2f%%\n", inventory[i].name, inventory[i].location,
               inventory[i].quantity, inventory[i].selling_price, inventory[i].profit_margin);
    }
}

void saveInventory() {
    FILE* fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < num_products; i++) {
        fprintf(fp, "%s,%s,%d,%.2f,%.2f\n", inventory[i].name, inventory[i].location,
                inventory[i].quantity, inventory[i].selling_price, inventory[i].profit_margin);
    }

    fclose(fp);
    printf("Inventory saved successfully.\n");
}

void loadInventory() {
    FILE* fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("File not found. Starting with an empty inventory.\n");
        return;
    }

    num_products = 0;
    char line[100];

    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%d,%f,%f",
               inventory[num_products].name,
               inventory[num_products].location,
               &inventory[num_products].quantity,
               &inventory[num_products].selling_price,
               &inventory[num_products].profit_margin);
        num_products++;
    }

    fclose(fp);
    printf("Inventory loaded successfully.\n");
}
