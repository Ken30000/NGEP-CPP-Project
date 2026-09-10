#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "type.h"

using namespace std;

struct OrderNode
{
    Order data;
    OrderNode *next;

    OrderNode(Order value) : data(value), next(nullptr) {}
};

OrderNode *orderHead = nullptr;

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
    ifstream myFile(string("order.csv"));
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
// // Function Declarations
// void loadOrders();
// void saveOrders();
// // void placeOrder(int customerId);
// // void viewAllOrders();
// // void viewOrdersByCustomer(int customerId);

// // ---------------------------------------------------------
// // PERSISTENCE: Load from 'orders.txt' using dynamic memory
// // ---------------------------------------------------------
// void loadOrders()
// {
//     ifstream inFile("order.csv");
//     if (!inFile.is_open())
//         return;

//     // Free existing list memory
//     OrderNode *current = orderHead;
//     while (current != nullptr)
//     {
//         OrderNode *temp = current;
//         current = current->next;
//         delete temp;
//     }
//     orderHead = nullptr;

//     string line;
//     OrderNode *tail = nullptr;

//     while (getline(inFile, line))
//     {
//         if (line.empty())
//             continue;

//         stringstream ss(line);
//         string idStr, custIdStr, prodIdStr, qtyStr, date;

//         if (getline(ss, idStr, ',') &&
//             getline(ss, custIdStr, ',') &&
//             getline(ss, prodIdStr, ',') &&
//             getline(ss, qtyStr, ',') &&
//             getline(ss, date, ','))
//         {

//             Order o;
//             o.id = stoi(idStr);
//             o.customerId = stoi(custIdStr);
//             o.productId = stoi(prodIdStr);
//             o.quantity = stoi(qtyStr);
//             o.date = date;

//             // Dynamic Memory Allocation using the Node Wrapper
//             OrderNode *newNode = new OrderNode(o);

//             if (orderHead == nullptr)
//             {
//                 orderHead = newNode;
//                 tail = newNode;
//             }
//             else
//             {
//                 tail->next = newNode;
//                 tail = newNode;
//             }
//         }
//     }
//     inFile.close();
// }

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