#include <iostream>
#include <limits>
#include <string>

#include "type.h"
#include "customer.h"
#include "product.h"
#include "category.h"
#include "order.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getIntInput(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) return val;
        clearInput();
        cout << "Invalid input. Please enter a number.\n";
    }
}

double getDoubleInput(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val) return val;
        clearInput();
        cout << "Invalid input. Please enter a number.\n";
    }
}

string getStringInput(const string& prompt) {
    string str;
    cout << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, str);
    return str;
}

void promptAddProduct() {
    string name = getStringInput("Enter Product Name: ");
    int categoryId = getIntInput("Enter Category ID: ");
    double price = getDoubleInput("Enter Price: ");
    int stock = getIntInput("Enter Stock: ");
    addProduct(name, categoryId, price, stock);
    saveProducts();
}

void promptEditProduct() {
    int id = getIntInput("Enter Product ID to edit: ");
    string name = getStringInput("Enter New Name: ");
    int categoryId = getIntInput("Enter New Category ID: ");
    double price = getDoubleInput("Enter New Price: ");
    int stock = getIntInput("Enter New Stock: ");
    editProduct(id, name, categoryId, price, stock);
    saveProducts();
}

void promptDeleteProduct() {
    int id = getIntInput("Enter Product ID to delete: ");
    deleteProduct(id);
    saveProducts();
}

void runOwnerMenu(CustomerList& customerApp, CategoryMananger& categoryApp, OrderList& orderApp) {
    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "                   OWNER MENU                    \n";
        cout << "==================================================\n";
        cout << "  Category\n";
        cout << "  1. View Categories\n";
        cout << "  2. Add Category\n";
        cout << "  3. Edit Category\n";
        cout << "  4. Delete Category\n";
        cout << "  Product\n";
        cout << "  5. View Products\n";
        cout << "  6. Add Product\n";
        cout << "  7. Edit Product\n";
        cout << "  8. Delete Product\n";
        cout << "  9. Sort Products by Price\n";
        cout << "  Customer\n";
        cout << " 10. View Customers\n";
        cout << " 11. Add Customer\n";
        cout << " 12. Edit Customer\n";
        cout << " 13. Delete Customer\n";
        cout << "  Order\n";
        cout << " 14. View All Orders\n";
        cout << " 15. View Orders by Customer\n";
        cout << " 16. Place Order\n";
        cout << "  0. Back\n";
        cout << "--------------------------------------------------\n";
        choice = getIntInput("Choose (0-16): ");

        switch (choice) {
            case 1:  categoryApp.viewCategories(); break;
            case 2:  categoryApp.addCategory(); break;
            case 3:  categoryApp.editCategory(); break;
            case 4:  categoryApp.deleteCategory(); break;
            case 5:  viewProducts(); break;
            case 6:  promptAddProduct(); break;
            case 7:  promptEditProduct(); break;
            case 8:  promptDeleteProduct(); break;
            case 9:  sortByPrice(); viewProducts(); break;
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
                int cid = getIntInput("Enter Customer ID: ");
                orderApp.placeOrder(cid);
                break;
            }
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void runEmployeeMenu(CustomerList& customerApp, CategoryMananger& categoryApp, OrderList& orderApp) {
    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "                 EMPLOYEE MENU                   \n";
        cout << "==================================================\n";
        cout << " 1. View Products\n";
        cout << " 2. Sort Products by Price\n";
        cout << " 3. Add Product\n";
        cout << " 4. Edit Product\n";
        cout << " 5. View Categories\n";
        cout << " 6. View Customers\n";
        cout << " 7. Add Customer\n";
        cout << " 8. Edit Customer\n";
        cout << " 9. Place Order\n";
        cout << "10. View All Orders\n";
        cout << "11. View Orders by Customer\n";
        cout << " 0. Back\n";
        cout << "--------------------------------------------------\n";
        choice = getIntInput("Choose (0-11): ");

        switch (choice) {
            case 1:  viewProducts(); break;
            case 2:  sortByPrice(); viewProducts(); break;
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
                int cid = getIntInput("Enter Customer ID: ");
                orderApp.viewOrdersByCustomer(cid);
                break;
            }
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void runCustomerMenu(CustomerList& customerApp, CategoryMananger& categoryApp, OrderList& orderApp) {
    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "                 CUSTOMER MENU                   \n";
        cout << "==================================================\n";
        cout << " 1. View Products\n";
        cout << " 2. Sort Products by Price\n";
        cout << " 3. View Categories\n";
        cout << " 4. Place Order\n";
        cout << " 5. View My Orders\n";
        cout << " 6. Register Account\n";
        cout << " 0. Back\n";
        cout << "--------------------------------------------------\n";
        choice = getIntInput("Choose (0-6): ");

        switch (choice) {
            case 1: viewProducts(); break;
            case 2: sortByPrice(); viewProducts(); break;
            case 3: categoryApp.viewCategories(); break;
            case 4: {
                int cid = getIntInput("Enter Your Customer ID: ");
                orderApp.placeOrder(cid);
                break;
            }
            case 5: {
                int cid = getIntInput("Enter Your Customer ID: ");
                orderApp.viewOrdersByCustomer(cid);
                break;
            }
            case 6: customerApp.addCustomer(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

int main() {
    CustomerList customerApp;
    CategoryMananger categoryApp;
    OrderList orderApp;
    loadProducts();

    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "          STORE MANAGEMENT SYSTEM          \n";
        cout << "==================================================\n";
        cout << " 1. Owner\n";
        cout << " 2. Employee\n";
        cout << " 3. Customer\n";
        cout << " 4. Exit\n";
        cout << "--------------------------------------------------\n";
        choice = getIntInput("Select Role (1-4): ");

        switch (choice) {
            case 1: runOwnerMenu(customerApp, categoryApp, orderApp); break;
            case 2: runEmployeeMenu(customerApp, categoryApp, orderApp); break;
            case 3: runCustomerMenu(customerApp, categoryApp, orderApp); break;
            case 4:
                saveProducts();
                freeAllProducts();
                cout << "Goodbye!\n";
                break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
