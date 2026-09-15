#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"category.h"
using namespace std;



int main(){
    CategoryMananger manager;
    
    manager.loadCategories();
    
    
    int choice;

    do{
        cout << "\n==============================================" << endl;
        cout << "             CATEGORY MANAGERMENT" << endl;
        cout << "==============================================" << endl;
        cout << "1. Add Category." << endl;
        cout << "2. View Categories." << endl;
        cout << "3. Edit Category." << endl;
        cout << "4. Delete Category." << endl;
        cout << "5. Exit." << endl;

        cout << "Choose an option:";
        cin >> choice;

        switch (choice){
            case 1:
                manager.addCategory();
                break;
            case 2:
                manager.viewCategories();
                break;
            case 3:
                manager.editCategory();
                break;
            case 4:
                manager.deleteCategory();
                break;
            case 5:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }

    }while(choice !=5);
    return 0;
}