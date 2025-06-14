#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <ctime>
#include <cstdlib>

// ---------- Product Class ----------
class Product {
public:
    int id;
    std::string name;
    double price;
    int stock;

    Product() {}
    Product(int pid, std::string pname, double pprice, int pstock)
        : id(pid), name(pname), price(pprice), stock(pstock) {}

    void display() const {
        std::cout << "ID: " << id << ", Name: " << name
                  << ", Price: " << price << ", Stock: " << stock << std::endl;
    }

    std::string toCSV() const {
        std::ostringstream oss;
        oss << id << "," << name << "," << price << "," << stock;
        return oss.str();
    }
};

// ---------- User Class ----------
class User {
public:
    std::string username;
    std::string password;
    std::string role;

    User() {}
    User(std::string uname, std::string pwd, std::string r)
        : username(uname), password(pwd), role(r) {}

    std::string toCSV() const {
        return username + "," + password + "," + role;
    }
};

// ---------- File Managers ----------
class ProductFileManager {
public:
    static void saveProducts(const std::map<int, Product>& products, const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& pair : products) {
            file << pair.second.toCSV() << std::endl;
        }
        file.close();
    }

    static void loadProducts(std::map<int, Product>& products, const std::string& filename) {
        products.clear();
        std::ifstream file(filename);
        std::string line;
        while (getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            int id, stock;
            double price;
            std::string name;

            getline(iss, token, ','); id = stoi(token);
            getline(iss, name, ',');
            getline(iss, token, ','); price = stod(token);
            getline(iss, token, ','); stock = stoi(token);

            products[id] = Product(id, name, price, stock);
        }
        file.close();
    }
};

class UserFileManager {
public:
    static void saveUsers(const std::vector<User>& users, const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& user : users) {
            file << user.toCSV() << std::endl;
        }
        file.close();
    }

    static void loadUsers(std::vector<User>& users, const std::string& filename) {
        users.clear();
        std::ifstream file(filename);
        std::string line;
        while (getline(file, line)) {
            std::istringstream iss(line);
            std::string username, password, role;
            getline(iss, username, ',');
            getline(iss, password, ',');
            getline(iss, role, ',');
            users.push_back(User(username, password, role));
        }
        file.close();
    }
};

// ---------- Authentication System ----------
class AuthSystem {
private:
    std::vector<User> users;
    std::string filename = "users.txt";

public:
    AuthSystem() {
        UserFileManager::loadUsers(users, filename);
    }

    void registerUser() {
        std::string uname, pwd, role;
        std::cout << "Enter username: ";
        std::cin >> uname;

        for (auto& user : users) {
            if (user.username == uname) {
                std::cout << "Username already exists!\n";
                return;
            }
        }

        std::cout << "Enter password: ";
        std::cin >> pwd;

        while (true) {
            std::cout << "Enter role (admin/customer): ";
            std::cin >> role;
            if (role == "admin" || role == "customer") break;
            else std::cout << "Invalid role.\n";
        }

        users.push_back(User(uname, pwd, role));
        UserFileManager::saveUsers(users, filename);
        std::cout << "Registration successful!\n";
    }

    User* loginUser() {
        std::string uname, pwd;
        std::cout << "Enter username: ";
        std::cin >> uname;
        std::cout << "Enter password: ";
        std::cin >> pwd;

        for (auto& user : users) {
            if (user.username == uname && user.password == pwd) {
                std::cout << "Login Successful as " << user.role << "\n";
                return &user;
            }
        }
        std::cout << "Invalid credentials!\n";
        return nullptr;
    }
};

// ---------- Order Manager ----------
class OrderManager {
public:
    static void placeOrder(const std::string& username, const std::vector<Product>& cart) {
        if (cart.empty()) {
            std::cout << "Cart is empty!\n";
            return;
        }

        double total = 0;
        std::ostringstream orderDetails;

        orderDetails << "Order for " << username << ":\n";
        for (const auto& item : cart) {
            double subtotal = item.price * item.stock;
            total += subtotal;
            orderDetails << item.name << " x" << item.stock << " = " << subtotal << "\n";
        }
        orderDetails << "Total: " << total << "\n";

        // Save order to file
        std::ofstream file("orders.txt", std::ios::app);
        file << orderDetails.str() << std::endl;
        file.close();

        std::cout << "Order placed successfully!\n";
    }

    static void viewOrders() {
        std::ifstream file("orders.txt");
        if (!file.is_open()) {
            std::cout << "No orders found.\n";
            return;
        }
        std::cout << "\n--- All Orders ---\n";
        std::string line;
        while (getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
};

// ---------- Main System Controller ----------
class ECommerceSystem {
private:
    std::map<int, Product> products;
    AuthSystem auth;

public:
    void loadData() {
        ProductFileManager::loadProducts(products, "products.txt");
    }

    void saveData() {
        ProductFileManager::saveProducts(products, "products.txt");
    }

    void adminMenu(User* user) {
        int choice;
        while (true) {
            std::cout << "\n--- Admin Menu ---\n";
            std::cout << "1. Add Product\n2. Remove Product\n3. Update Stock\n4. View Products\n5. View Orders\n6. Logout\n";
            std::cout << "Enter choice: ";
            std::cin >> choice;
            switch (choice) {
                case 1: addProduct(); break;
                case 2: removeProduct(); break;
                case 3: updateStock(); break;
                case 4: viewProducts(); break;
                case 5: OrderManager::viewOrders(); break;
                case 6: saveData(); return;
                default: std::cout << "Invalid choice.\n";
            }
        }
    }

    void customerMenu(User* user) {
        int choice;
        std::vector<Product> cart;
        while (true) {
            std::cout << "\n--- Customer Menu ---\n";
            std::cout << "1. View Products\n2. Add To Cart\n3. Checkout\n4. Logout\n";
            std::cout << "Enter choice: ";
            std::cin >> choice;
            switch (choice) {
                case 1: viewProducts(); break;
                case 2: addToCart(cart); break;
                case 3: checkout(cart, user->username); break;
                case 4: saveData(); return;
                default: std::cout << "Invalid choice.\n";
            }
        }
    }

    void addProduct() {
        int id, stock;
        std::string name;
        double price;
        std::cout << "Enter Product ID: "; std::cin >> id;
        std::cout << "Enter Name: "; std::cin >> name;
        std::cout << "Enter Price: "; std::cin >> price;
        std::cout << "Enter Stock: "; std::cin >> stock;

        products[id] = Product(id, name, price, stock);
        std::cout << "Product Added.\n";
    }

    void removeProduct() {
        int id;
        std::cout << "Enter Product ID to remove: "; std::cin >> id;
        if (products.erase(id))
            std::cout << "Product Removed.\n";
        else
            std::cout << "Product Not Found.\n";
    }

    void updateStock() {
        int id, stock;
        std::cout << "Enter Product ID to update stock: "; std::cin >> id;
        if (products.find(id) != products.end()) {
            std::cout << "Enter new stock: "; std::cin >> stock;
            products[id].stock = stock;
            std::cout << "Stock updated.\n";
        } else {
            std::cout << "Product Not Found.\n";
        }
    }

    void viewProducts() {
        if (products.empty()) {
            std::cout << "No products available.\n";
            return;
        }
        for (const auto& p : products)
            p.second.display();
    }

    void addToCart(std::vector<Product>& cart) {
        int id, qty;
        std::cout << "Enter Product ID to add: "; std::cin >> id;
        if (products.find(id) != products.end()) {
            std::cout << "Enter quantity: "; std::cin >> qty;
            if (qty <= products[id].stock) {
                cart.push_back(Product(id, products[id].name, products[id].price, qty));
                std::cout << "Added to cart.\n";
            } else {
                std::cout << "Insufficient stock.\n";
            }
        } else {
            std::cout << "Product not found.\n";
        }
    }

    void checkout(std::vector<Product>& cart, const std::string& username) {
        if (cart.empty()) {
            std::cout << "Cart is empty.\n";
            return;
        }

        // Deduct stock
        for (auto& item : cart) {
            products[item.id].stock -= item.stock;
        }

        OrderManager::placeOrder(username, cart);
        cart.clear();
    }

    void run() {
        loadData();
        int choice;
        while (true) {
            std::cout << "\n--- Mini E-Commerce ---\n";
            std::cout << "1. Register\n2. Login\n3. Exit\nEnter choice: ";
            std::cin >> choice;
            if (choice == 1) auth.registerUser();
            else if (choice == 2) {
                User* loggedIn = auth.loginUser();
                if (loggedIn != nullptr) {
                    if (loggedIn->role == "admin") adminMenu(loggedIn);
                    else customerMenu(loggedIn);
                }
            }
            else if (choice == 3) break;
            else std::cout << "Invalid option.\n";
        }
    }
};

// ---------- Main ----------
int main() {
    ECommerceSystem system;
    system.run();
    return 0;
}
