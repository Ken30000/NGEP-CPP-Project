#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include "type.h"
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std ;
class CustomerList {
    private : 
    struct CustomerNode {
        Customer data ;
        CustomerNode *next ;
        CustomerNode(Customer value) : data(value),next(nullptr) {}
    };
    CustomerNode *head ;
    CustomerNode *tail ;
    public:
    CustomerList() : head(nullptr), tail(nullptr)
    {
        loadCustomers();
    }

    ~CustomerList()
    {
        freeMemory();
    }

    void freeMemory()
    {
        CustomerNode *current = head;
        while (current != nullptr)
        {
            CustomerNode *temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }
    void loadCustomers()
    {
        ifstream myFile;
        myFile.open("customerList.csv");
        if (!myFile.is_open())
        {
            return;
        }

        freeMemory();
        string line;

        while (getline(myFile, line))
        {
            if (line.empty())
            {
                continue;
            }

            stringstream iss(line);
            string idStr, name, phone;

            if (getline(iss, idStr, ',') &&
                getline(iss, name, ',') &&
                getline(iss, phone))
            {
                Customer c;
                c.id = stoi(idStr);
                c.name = name;
                c.phone = phone;

                CustomerNode *newNode = new CustomerNode(c);
                if (head == nullptr)
                {
                    head = newNode;
                    tail = newNode;
                }
                else
                {
                    tail->next = newNode;
                    tail = newNode;
                }
            }
        }
        myFile.close();
    }

    void saveCustomers()
    {
        ofstream myFile;
        myFile.open("customerList.csv");
        if (!myFile.is_open()){
            cout << "[Error] Failed to open customerList.csv\n";
            return;
        }

        CustomerNode *temp = head;
        while (temp != nullptr)
        {
            myFile << temp->data.id << ',' 
                   << temp->data.name << ',' 
                   << temp->data.phone << "\n";
            temp = temp->next;
        }
        myFile.close();
    }
    void addCustomer(){
        int newId = 1  ;
        CustomerNode *temp = head ;
        while (temp != nullptr ){
            if (temp->data.id >= newId){
                newId = temp->data.id + 1 ;
            }
             temp = temp->next ;
        }

    string name , phone ;
        cout << "\n--------------------------------------------------" << endl;
        cout << setw(32) << "ADD NEW CUSTOMER" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Generated Customer ID: " << newId << endl;
        cin.ignore();

        cout<< "Enter  Customer Name: ";
        getline(cin,name);
        
        cout <<"Enter Phone Number: ";
        cin>>phone;
        Customer c;
        c.id = newId;
        c.name = name;
        c.phone = phone;

        CustomerNode *newNode = new CustomerNode(c);

        if (head == nullptr){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }
        cout << "[Success] Customer ID " << newId << " added successfully.\n";
        saveCustomers();
    }
    void viewCustomers()
    {
        if (head == nullptr)
        {
            cout << "\n[Info] No customers found in the system.\n";
            return;
        }

        cout << "\n--------------------------------------------------" << endl;
        cout << setw(33) << "CUSTOMER DIRECTORY" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << left << setw(10) << "ID"
             << setw(25) << "Full Name"
             << setw(15) << "Phone Number" << endl;
        cout << "--------------------------------------------------" << endl;

        int count = 0;
        CustomerNode *temp = head;
        while (temp != nullptr)
        {
            cout << left << setw(10) << temp->data.id
                 << setw(25) << temp->data.name
                 << setw(15) << temp->data.phone << endl;
            temp = temp->next;
            count++;
        }

        cout << "--------------------------------------------------" << endl;
        cout << "Total Customers: " << count << endl;
        cout << "--------------------------------------------------\n" << endl;
    }

    void editCustomer()
    {
        if (head == nullptr)
        {
            cout << "\n[Info] No customers available to edit.\n";
            return;
        }

        int targetId;
        cout << "\nEnter Customer ID to edit: ";
        cin >> targetId;

        CustomerNode *temp = head;
        while (temp != nullptr)
        {
            if (temp->data.id == targetId)
            {
                cout << "\n[Current Details] Name: " << temp->data.name 
                     << " | Phone: " << temp->data.phone << "\n";

                cin.ignore();
                cout << "Enter New Name: ";
                getline(cin, temp->data.name);

                cout << "Enter New Phone Number: ";
                cin >> temp->data.phone;

                saveCustomers();
                cout << "[Success] Customer updated successfully.\n";
                return;
            }
            temp = temp->next;
        }

        cout << "[Error] Customer ID " << targetId << " not found.\n";
    }

    void deleteCustomer()
    {
        if (head == nullptr)
        {
            cout << "\n[Info] No customers available to delete.\n";
            return;
        }

        int targetId;
        cout << "\nEnter Customer ID to delete: ";
        cin >> targetId;

        CustomerNode *current = head;
        CustomerNode *prev = nullptr;

        while (current != nullptr)
        {
            if (current->data.id == targetId)
            {
                // Deleting the head node
                if (current == head)
                {
                    head = head->next;
                    if (head == nullptr)
                    {
                        tail = nullptr;
                    }
                }
                else
                {
                    prev->next = current->next;
                    // Deleting the tail node
                    if (current == tail)
                    {
                        tail = prev;
                    }
                }

                delete current;
                saveCustomers();
                cout << "[Success] Customer ID " << targetId << " deleted successfully.\n";
                return;
            }

            prev = current;
            current = current->next;
        }

        cout << "[Error] Customer ID " << targetId << " not found.\n";
    }

};

#endif 
