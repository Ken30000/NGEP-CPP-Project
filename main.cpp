#include <iostream>
#include <limits>
#include <string>
#include <iomanip>

// Shared types and team modules
#include "type.h"
#include "customer.h"
#include "product.h"
#include "category.h"
#include "order.h"

using namespace std;

// ---------------- INPUT UTILITIES ----------------
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getIntInput(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            return val;
        }
        clearInput();
        cout << "[Error] Invalid input. Please enter a valid number.\n";
    }
}

double getDoubleInput(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            return val;
        }
        clearInput();
        cout << "[Error] Invalid input. Please enter a valid number.\n";
    }
}

string getStringInput(const string& prompt) {
    string str;
    cout << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, str);
    return str;
}

// ---------------- PRODUCT INTERACTIVE HELPERS ----------------
void promptAddProduct() {
    cout << "\n--------------------------------------------------\n";
    cout << "                 ADD NEW PRODUCT                  \n";
    cout << "--------------------------------------------------\n";
    string name = getStringInput("Enter Product Name: ");
    int categoryId = getIntInput("Enter Category ID: ");
    double price = getDoubleInput("Enter Product Price ($): ");
    int stock = getIntInput("Enter Stock Quantity: ");

    addProduct(name, categoryId, price, stock);
    saveProducts();
}

void promptEditProduct() {
    cout << "\n--------------------------------------------------\n";
    cout << "                 EDIT PRODUCT                     \n";
    cout << "--------------------------------------------------\n";
    int id = getIntInput("Enter Product ID to edit: ");
    string name = getStringInput("Enter New Product Name: ");
    int categoryId = getIntInput("Enter New Category ID: ");
    double price = getDoubleInput("Enter New Price ($): ");
    int stock = getIntInput("Enter New Stock Quantity: ");

    editProduct(id, name, categoryId, price, stock);
    saveProducts();
}

void promptDeleteProduct() {
    cout << "\n--------------------------------------------------\n";
    cout << "                DELETE PRODUCT                    \n";
    cout << "--------------------------------------------------\n";
    int id = getIntInput("Enter Product ID to delete: ");
    deleteProduct(id);
    saveProducts();
}

// ================================================================
// TIER 1: OWNER PORTAL (Full Administrative Access)
// Permissions: Full CRUD on Products, Categories, Customers, Orders
// ================================================================
void runOwnerPortal(CustomerList& customerApp, CategoryMananger& categoryApp, OrderList& orderApp) {
    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "               SMS: OWNER PORTAL                  \n";
        cout << "       [Full Administrative & Management]         \n";
        cout << "==================================================\n";
        cout << " [CATEGORY MANAGEMENT]\n";
        cout << "  1. View All Categories\n";
        cout << "  2. Add Category\n";
        cout << "  3. Edit Category\n";
        cout << "  4. Delete Category\n\n";
        cout << " [PRODUCT MANAGEMENT]\n";
        cout << "  5. View All Products\n";
        cout << "  6. Add New Product\n";
        cout << "  7. Edit Product Details\n";
        cout << "  8. Delete Product\n";
        cout << "  9. Sort Products by Price\n\n";
        cout << " [CUSTOMER MANAGEMENT]\n";
        cout << " 10. View Customer Directory\n";
        cout << " 11. Add New Customer\n";
        cout << " 12. Edit Customer Info\n";
        cout << " 13. Delete Customer\n\n";
        cout << " [ORDER AUDIT & TRANSACTIONS]\n";
        cout << " 14. View All System Orders\n";
        cout << " 15. View Orders by Customer ID\n";
        cout << " 16. Place New Order\n\n";
        cout << "  0. Return to Main Role Selection\n";
        cout << "--------------------------------------------------\n";
        choice = getIntInput("Select an option (0-16): ");

        switch (choice) {
            case 1:  categoryApp.viewCategories(); break;
            case 2:  categoryApp.addCategory(); break;
            case 3:  categoryApp.editCategory(); break;
            case 4:  categoryApp.deleteCategory(); break;

            case 5:
                cout << "\n--- Current Product Catalog ---\n";
                viewProducts();
                break;
            case 6:  promptAddProduct(); break;
            case 7:  promptEditProduct(); break;
            case 8:  promptDeleteProduct(); break;
            case 9:
                sortByPrice();
                cout << "\n--- Products Sorted by Price (Lowest to Highest) ---\n";
                viewProducts();
                break;

            case 10: customerApp.viewCustomers(); break;
            case 11: customerApp.addCustomer(); break;
            case 12: customerApp.editCustomer(); break;
            case 13: customerApp.deleteCustomer(); break;

            case 14: orderApp.viewAllOrders(); break;
            case 15: {
                int cid = getIntInput("Enter Customer ID: ");
                orderApp.viewOrdersByCustomer(cid);
                break;
            }
            case 16: {
                int cid = getIntInput("Enter Customer ID for order: ");
                orderApp.placeOrder(cid);
                break;
            }
            case 0:
                cout << "\n[Notice] Exiting Owner Portal...\n";
                break;
            default:
                cout << "[Error] Invalid selection. Choose between 0 and 16.\n";
        }
    } while (choice != 0);
}

// ================================================================
// TIER 2: EMPLOYEE PORTAL (Operational Access)
// Permissions: View & Add/Edit Products, View Categories,
//              View & Add/Edit Customers, Process Orders.
//              (Destructive Deletions Restricted)
// ================================================================
void runEmployeePortal(CustomerList& customerApp, CategoryMananger& categoryApp, OrderList& orderApp) {
    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "              SMS: EMPLOYEE PORTAL                \n";
        cout << "             [Operational & Sales]                \n";
        cout << "==================================================\n";
        cout << " 1. View Product Catalog\n";
        cout << " 2. Sort Products by Price\n";
        cout << " 3. Add New Product\n";
        cout << " 4. Edit Product Details / Stock\n";
        cout << " 5. View Categories\n";
        cout << " 6. View Customer Directory\n";
        cout << " 7. Register New Customer\n";
        cout << " 8. Edit Customer Info\n";
        cout << " 9. Process / Place Order\n";
        cout << "10. View All Orders\n";
        cout << "11. Search Orders by Customer ID\n";
        cout << " 0. Return to Main Role Selection\n";
        cout << "--------------------------------------------------\n";
        choice = getIntInput("Select an option (0-11): ");

        switch (choice) {
            case 1:
                cout << "\n--- Current Product Catalog ---\n";
                viewProducts();
                break;
            case 2:
                sortByPrice();
                cout << "\n--- Products Sorted by Price ---\n";
                viewProducts();
                break;
            case 3:  promptAddProduct(); break;
            case 4:  promptEditProduct(); break;
            case 5:  categoryApp.viewCategories(); break;
            case 6:  customerApp.viewCustomers(); break;
            case 7:  customerApp.addCustomer(); break;
            case 8:  customerApp.editCustomer(); break;
            case 9: {
                int cid = getIntInput("Enter Customer ID: ");
                orderApp.placeOrder(cid);
                break;
            }
            case 10: orderApp.viewAllOrders(); break;
            case 11: {
                int cid = getIntInput("Enter Customer ID to search: ");
                orderApp.viewOrdersByCustomer(cid);
                break;
            }
            case 0:
                cout << "\n[Notice] Exiting Employee Portal...\n";
                break;
            default:
                cout << "[Error] Invalid selection. Choose between 0 and 11.\n";
        }
    } while (choice != 0);
}

// ================================================================
// TIER 3: CUSTOMER / USER PORTAL (Self-Service Shopping)
// Permissions: Browse Products, Sort by Price, View Categories,
//              Place Order, View Own Orders, Register Profile.
// ================================================================
void runCustomerPortal(CustomerList& customerApp, CategoryMananger& categoryApp, OrderList& orderApp) {
    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "          SMS: CUSTOMER / STOREFRONT              \n";
        cout << "            [Browse, Shop & Order]                \n";
        cout << "==================================================\n";
        cout << " 1. Browse Products Catalog\n";
        cout << " 2. View Products Sorted by Price (Lowest First)\n";
        cout << " 3. View Product Categories\n";
        cout << " 4. Place an Order (Checkout)\n";
        cout << " 5. View My Order History\n";
        cout << " 6. Register as a New Customer\n";
        cout << " 0. Return to Main Role Selection\n";
        cout << "--------------------------------------------------\n";
        choice = getIntInput("Select an option (0-6): ");

        switch (choice) {
            case 1:
                cout << "\n--- Available Products ---\n";
                viewProducts();
                break;
            case 2:
                sortByPrice();
                cout << "\n--- Products Sorted by Price (Lowest to Highest) ---\n";
                viewProducts();
                break;
            case 3:
                categoryApp.viewCategories();
                break;
            case 4: {
                int cid = getIntInput("Enter Your Customer ID: ");
                orderApp.placeOrder(cid);
                break;
            }
            case 5: {
                int cid = getIntInput("Enter Your Customer ID to view orders: ");
                orderApp.viewOrdersByCustomer(cid);
                break;
            }
            case 6:
                customerApp.addCustomer();
                break;
            case 0:
                cout << "\n[Notice] Returning to Role Selection...\n";
                break;
            default:
                cout << "[Error] Invalid selection. Choose between 0 and 6.\n";
        }
    } while (choice != 0);
}

// ================================================================
// MAIN ENTRY POINT - Role-Aware CLI (Owner, Employee, Customer)
// Reference: NGEP Store Management System Presentation Architecture
// ================================================================
int main() {
    // Initialize module managers
    CustomerList customerApp;
    CategoryMananger categoryApp;
    OrderList orderApp;

    // Load initial products from CSV
    loadProducts();

    int roleChoice;
    do {
        cout << "\n==================================================\n";
        cout << "        SMS: STORE MANAGEMENT SYSTEM (C++)        \n";
        cout << "    A Console-Based Application for Retail        \n";
        cout << "       Group 4 - Teramoto Ken (Lead)              \n";
        cout << "==================================================\n";
        cout << "Select Access Tier:\n";
        cout << "  1. Owner    (Full Administrative Scope)\n";
        cout << "  2. Employee (Operational & Sales Scope)\n";
        cout << "  3. Customer (Storefront & Order Placement)\n";
        cout << "  4. Exit Application\n";
        cout << "--------------------------------------------------\n";
        roleChoice = getIntInput("Enter Role (1-4): ");

        switch (roleChoice) {
            case 1:
                runOwnerPortal(customerApp, categoryApp, orderApp);
                break;
            case 2:
                runEmployeePortal(customerApp, categoryApp, orderApp);
                break;
            case 3:
                runCustomerPortal(customerApp, categoryApp, orderApp);
                break;
            case 4:
                cout << "\n[System] Saving all data to CSV files...\n";
                saveProducts();
                freeAllProducts();
                cout << "[System] Shutdown complete. Thank you for using SMS!\n\n";
                break;
            default:
                cout << "[Error] Invalid role. Please select 1, 2, 3, or 4.\n";
        }
    } while (roleChoice != 4);

    return 0;
}
