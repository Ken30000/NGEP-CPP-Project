#ifndef PRODUCT_H
#define PRODUCT_H

#include "type.h"
#include <string>
using namespace std;

// Same idea as your W3 linked list lessons: a node holds one Product
// and a pointer to the next node.
struct ProductNode {
    Product data;
    ProductNode* next;
};

// Plain global variables instead of hiding them inside a class.
// Declared here with "extern" (means: this variable exists, but its
// actual storage is defined in product.cpp), used in main.cpp too.
extern ProductNode* head;
extern int nextId;

// Just plain functions -- no class, no "this", no references.
void addProduct(string name, int categoryId, double price, int stock);
void editProduct(int id, string name, int categoryId, double price, int stock);
void deleteProduct(int id);
void viewProducts();
void loadProducts();
void saveProducts();
void sortByPrice();
void freeAllProducts(); // call this before the program ends

#endif
