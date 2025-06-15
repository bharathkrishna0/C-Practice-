#include <iostream>
#include <string>
using namespace std;

// General template
template<typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    Pair(T1 a, T2 b) : first(a), second(b) {}

    void display() {
        cout << "First: " << first << ", Second: " << second << endl;
    }
};

// Specialization when second type is string
template<typename T1>
class Pair<T1, string> {
public:
    T1 first;
    string second;

    Pair(T1 a, string b) : first(a), second(b) {}

    void display() {
        cout << "First: " << first << ", Second length: " << second.length() << endl;
    }
};

int main() {
    Pair<int, float> p1(10, 3.14);
    Pair<double, char> p2(2.718, 'A');
    Pair<int, string> p3(42, "Hello");

    p1.display();
    p2.display();
    p3.display();

    return 0;
}
