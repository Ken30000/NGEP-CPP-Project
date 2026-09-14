

class ProductList {
private:
    struct Node {
        Product data; ❶
        Node* next; ❷
    };
    Node* head; ❸
    int count; ❹

public:
    ProductList(); ❺
    ~ProductList(); ❻
    void insert(Product p);
    void remove(int id);
    void display();
};