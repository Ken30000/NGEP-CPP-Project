#include "customer.h"
#include <iostream> 
using namespace std ;

int main() {
    CustomerList app;
    int choice;

    do {
        cout << "\n================================\n";
        cout << "    CUSTOMER MANAGEMENT SYSTEM   \n";
        cout << "================================\n";
        cout << "1. Add Customer\n";
        cout << "2. View All Customers\n";
        cout << "3. Edit Customer\n";
        cout << "4. Delete Customer\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                app.addCustomer();
                break;
            case 2:
                app.viewCustomers();
                break;
            case 3:
                app.editCustomer();
                break;
            case 4:
                app.deleteCustomer();
                break;
            case 5:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid selection! Please enter a number between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}
