#include <iostream>
#include <limits>
#include <string>

// Include modules from all team members
#include "type.h"
#include "customer.h"
#include "product.h"
#include "category.h"
#include "order.h"

using namespace std;

// Helper to clear invalid input from cin
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ---------------- CUSTOMER SUBMENU ----------------
void handleCustomerMenu(CustomerList& customerApp) {
    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "           CUSTOMER MANAGEMENT MODULE             \n";
        cout << "==================================================\n";
        cout << "1. Add New Customer\n";
        cout << "2. View All Customers\n";
        cout << "3. Edit Customer Information\n";
        cout << "4. Delete Customer\n";
        cout << "5. Return to Main Menu\n";
        cout << "--------------------------------------------------\n";
        cout << "Enter your choice (1-5): ";
        if (!(cin >> choice)) {
            clearInput();
            cout << "[Error] Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                customerApp.addCustomer();
                break;
            case 2:
                customerApp.viewCustomers();
                break;
            case 3:
                customerApp.editCustomer();
                break;
            case 4:
                customerApp.deleteCustomer();
                break;
            case 5:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "[Error] Invalid selection! Please enter 1-5.\n";
        }
    } while (choice != 5);
}

// ---------------- PRODUCT SUBMENU ----------------
void handleProductMenu() {
    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "           PRODUCT MANAGEMENT MODULE              \n";
        cout << "==================================================\n";
        cout << "1. Add New Product\n";
        cout << "2. View All Products\n";
        cout << "3. Edit Product Details\n";
        cout << "4. Delete Product\n";
        cout << "5. Sort Products by Price\n";
        cout << "6. Return to Main Menu\n";
        cout << "--------------------------------------------------\n";
        cout << "Enter your choice (1-6): ";
        if (!(cin >> choice)) {
            clearInput();
            cout << "[Error] Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                string name;
                int categoryId, stock;
                double price;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Product Name: ";
                getline(cin, name);

                cout << "Enter Category ID: ";
                while (!(cin >> categoryId)) {
                    clearInput();
                    cout << "Invalid. Enter valid Category ID: ";
                }

                cout << "Enter Product Price ($): ";
                while (!(cin >> price)) {
                    clearInput();
                    cout << "Invalid. Enter valid Price: ";
                }

                cout << "Enter Stock Quantity: ";
                while (!(cin >> stock)) {
                    clearInput();
                    cout << "Invalid. Enter valid Stock: ";
                }

                addProduct(name, categoryId, price, stock);
                saveProducts();
                break;
            }
            case 2:
                cout << "\n--------------------------------------------------\n";
                cout << "                 PRODUCT CATALOG                  \n";
                cout << "--------------------------------------------------\n";
                viewProducts();
                break;
            case 3: {
                int id, categoryId, stock;
                string name;
                double price;

                cout << "Enter Product ID to edit: ";
                while (!(cin >> id)) {
                    clearInput();
                    cout << "Invalid ID. Enter valid Product ID: ";
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter New Product Name: ";
                getline(cin, name);

                cout << "Enter New Category ID: ";
                while (!(cin >> categoryId)) {
                    clearInput();
                    cout << "Invalid. Enter valid Category ID: ";
                }

                cout << "Enter New Price ($): ";
                while (!(cin >> price)) {
                    clearInput();
                    cout << "Invalid. Enter valid Price: ";
                }

                cout << "Enter New Stock Quantity: ";
                while (!(cin >> stock)) {
                    clearInput();
                    cout << "Invalid. Enter valid Stock: ";
                }

                editProduct(id, name, categoryId, price, stock);
                saveProducts();
                break;
            }
            case 4: {
                int id;
                cout << "Enter Product ID to delete: ";
                while (!(cin >> id)) {
                    clearInput();
                    cout << "Invalid ID. Enter valid Product ID: ";
                }
                deleteProduct(id);
                saveProducts();
                break;
            }
            case 5:
                sortByPrice();
                cout << "\n--- Sorted Product List (Lowest to Highest Price) ---\n";
                viewProducts();
                break;
            case 6:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "[Error] Invalid selection! Please enter 1-6.\n";
        }
    } while (choice != 6);
}

// ---------------- CATEGORY SUBMENU ----------------
void handleCategoryMenu(CategoryMananger& categoryApp) {
    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "           CATEGORY MANAGEMENT MODULE             \n";
        cout << "==================================================\n";
        cout << "1. Add Category\n";
        cout << "2. View All Categories\n";
        cout << "3. Edit Category\n";
        cout << "4. Delete Category\n";
        cout << "5. Return to Main Menu\n";
        cout << "--------------------------------------------------\n";
        cout << "Enter your choice (1-5): ";
        if (!(cin >> choice)) {
            clearInput();
            cout << "[Error] Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                categoryApp.addCategory();
                break;
            case 2:
                categoryApp.viewCategories();
                break;
            case 3:
                categoryApp.editCategory();
                break;
            case 4:
                categoryApp.deleteCategory();
                break;
            case 5:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "[Error] Invalid selection! Please enter 1-5.\n";
        }
    } while (choice != 5);
}

// ---------------- ORDER SUBMENU ----------------
void handleOrderMenu(OrderList& orderApp) {
    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "             ORDER MANAGEMENT MODULE              \n";
        cout << "==================================================\n";
        cout << "1. Place New Order\n";
        cout << "2. View All Orders\n";
        cout << "3. View Orders by Customer ID\n";
        cout << "4. Return to Main Menu\n";
        cout << "--------------------------------------------------\n";
        cout << "Enter your choice (1-4): ";
        if (!(cin >> choice)) {
            clearInput();
            cout << "[Error] Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int customerId;
                cout << "Enter Customer ID: ";
                while (!(cin >> customerId)) {
                    clearInput();
                    cout << "Invalid ID. Enter Customer ID: ";
                }
                orderApp.placeOrder(customerId);
                break;
            }
            case 2:
                orderApp.viewAllOrders();
                break;
            case 3: {
                int customerId;
                cout << "Enter Customer ID to search orders: ";
                while (!(cin >> customerId)) {
                    clearInput();
                    cout << "Invalid ID. Enter Customer ID: ";
                }
                orderApp.viewOrdersByCustomer(customerId);
                break;
            }
            case 4:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "[Error] Invalid selection! Please enter 1-4.\n";
        }
    } while (choice != 4);
}

// ---------------- MAIN APPLICATION ----------------
int main() {
    // Initialize module managers
    CustomerList customerApp;
    CategoryMananger categoryApp;
    OrderList orderApp;

    // Load existing products into memory
    loadProducts();

    int choice = 0;
    do {
        cout << "\n==================================================\n";
        cout << "        NGEP STORE MANAGEMENT SYSTEM (MAIN)       \n";
        cout << "==================================================\n";
        cout << "1. Customer Management\n";
        cout << "2. Product Management\n";
        cout << "3. Category Management\n";
        cout << "4. Order Management\n";
        cout << "5. Exit Application\n";
        cout << "--------------------------------------------------\n";
        cout << "Enter your choice (1-5): ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "[Error] Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                handleCustomerMenu(customerApp);
                break;
            case 2:
                handleProductMenu();
                break;
            case 3:
                handleCategoryMenu(categoryApp);
                break;
            case 4:
                handleOrderMenu(orderApp);
                break;
            case 5:
                cout << "\nSaving data and shutting down...\n";
                saveProducts();
                freeAllProducts();
                cout << "Thank you for using NGEP Store Management System!\n";
                break;
            default:
                cout << "[Error] Invalid selection! Please enter a number between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}

