#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include<ctime>
#include <string>
#include "type.h"

using namespace std;

struct OrderNode
{
    Order data;
    OrderNode *next;

    OrderNode(Order value) : data(value), next(nullptr) {}
};

OrderNode *orderHead = nullptr;

string getCurrentDateTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);

    return string(buffer);
}

void freeMemory(){
    OrderNode *current = orderHead;
    if (current != nullptr){
        OrderNode *temp = current;
        current = current->next;
        delete temp;
    }
    orderHead = nullptr;
}

void loadOrders(){
    ifstream myFile;
    myFile.open("orderList.csv");
    if (!myFile.is_open()){
        return;
    }

    string line;
    OrderNode *tail = nullptr;

    while(getline(myFile, line)){
        if (line.empty()){
            continue;
        }
        stringstream iss(line);
        string idStr, customerIdStr, productIdStr, quantityStr, date;

        if (getline(iss, idStr, ',') &&
            getline(iss, customerIdStr, ',') &&
            getline(iss, productIdStr, ',') &&
            getline(iss, quantityStr, ',') &&
            getline(iss, date, ','))
        {
            Order od;
            od.id = stoi(idStr);
            od.customerId = stoi(customerIdStr);
            od.productId = stoi(productIdStr);
            od.quantity = stoi(quantityStr);
            od.date = date;
            OrderNode *newNode = new OrderNode(od);
            if (orderHead == nullptr){
                orderHead = newNode;
                tail = newNode;
            }else{
                OrderNode *temp = tail;
                tail->next = newNode;
                tail = newNode;
            }
        }
    }
    myFile.close();
}

void saveOrders(){
    ofstream myFile;
    myFile.open("orderList.csv");
    if (!myFile.is_open()){
        cout << "Open File Unsuccessfully";
        return;
    }

    OrderNode *temp = orderHead;
    while (temp != nullptr)
    {
        myFile << temp->data.id << ',' <<temp->data.customerId
               << ',' <<temp->data.productId << ',' <<temp->data.quantity << ',' <<temp->data.date << "\n";
        temp = temp->next;
    }
    myFile.close();
    cout << "Orders saved successfully.";
}

void placeOrder(int customerId){
    
    int proId;
    int quan;
    string date;
    cout << "Enter Your ProductID:";
    cin >> proId;
    cout << "Enter Product Quantity";
    cin >> quan;
    date = getCurrentDateTime();

    int orderId = 1;
    OrderNode *temp = orderHead;
    while(temp != nullptr){
        if (temp->data.id >= orderId){
            orderId = temp->data.id + 1;
        }
        temp = temp->next;
    }
    

    Order o;
    o.id = orderId;
    o.customerId = customerId;
    o.productId = proId;
    o.quantity = quan;
    o.date = date;
    OrderNode *newNode = new OrderNode(o);

    if(orderHead != nullptr)
    {
        OrderNode *current = orderHead;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;

    }
    else
    {
        orderHead = newNode;
    }

    cout << "[Success] Order ID:" << orderId << " placed successfully at " << date << "\n";
    saveOrders();
}



// // Function Declarations
// void loadOrders();
// void saveOrders();
// // void placeOrder(int customerId);
// // void viewAllOrders();
// // void viewOrdersByCustomer(int customerId);



// void viewAllOrders()
// {
//     if (orderHead == nullptr)
//     {
//         cout << "\n[Info] No orders found.\n";
//         return;
//     }

//     cout << "\n------------------- ALL ORDERS -------------------\n";
//     cout << left << setw(10) << "Order ID"
//          << setw(15) << "Customer ID"
//          << setw(12) << "Product ID"
//          << setw(10) << "Quantity"
//          << setw(15) << "Date" << "\n";
//     cout << "--------------------------------------------------\n";

//     OrderNode *temp = orderHead;
//     while (temp != nullptr)
//     {
//         cout << left << setw(10) << temp->data.id
//              << setw(15) << temp->data.customerId
//              << setw(12) << temp->data.productId
//              << setw(10) << temp->data.quantity
//              << setw(15) << temp->data.date << "\n";
//         temp = temp->next;
//     }
//     cout << "--------------------------------------------------\n";
// }

#endif