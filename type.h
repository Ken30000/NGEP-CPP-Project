#ifndef type_h
#define type_h
#include <string>
using namespace std;

struct Category {
    int id;
    string name;
};

struct Product {
    int id;
    string name;
    int categoryId;
    double price;
    int stock;
};

struct Customer {
    int id;
    string name;
    string phone;
};

struct Order {
    int id;
    int customerId;
    int productId;
    int quantity;
    string date;
};

#endif