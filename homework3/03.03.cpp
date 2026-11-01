#include<print>
#include<cassert>

class Node {
private:
    int value;
    Node * next;
public:
    Node(int value) : value(value), next(nullptr) {}   
    
    void set_next(Node * next_node) {
        next = next_node;
    }

    bool has_next() {
        return next != nullptr;
    }

    Node * get_next() {
        return next;
    }

    int get_value() {
        return value;
    }
};


class List {
private:
    Node * first_node;
    Node * last_node;

public:
    List() : first_node(nullptr), last_node(nullptr) {}

    ~List() {
        while (!empty()) {
            pop_front(); 
        }
    }

    bool empty() {
        if (first_node == nullptr) {
            return true;
        }
        return false;
    }

    void push_back(int value) {
        Node * new_node = new Node(value);
        if (empty()) {
            first_node = new_node;
            last_node = new_node;
        } else {
            (*last_node).set_next(new_node);
            last_node = new_node;
        }
    }

    void push_front(int value) {
        Node * new_node = new Node(value);
        if (empty()) {
            first_node = new_node;
            last_node = new_node;
        } else {
            (*new_node).set_next(first_node);
            first_node = new_node;
        }
    }

    void show() {
        if (empty()) {
            return;
        }
        Node * tmp = first_node;
        while(tmp != nullptr) {
            std::print("{}\n", (*tmp).get_value());
            tmp = (*tmp).get_next();
        }
    }

    void pop_back() {
        if (empty()) {
            return;
        }
        Node * tmp = first_node;
        if (first_node == last_node) {
           delete tmp;
            first_node = nullptr;
            last_node = nullptr;
            return;
        }
        while((*tmp).get_next() != last_node) {
            tmp = (*tmp).get_next();
        }
        delete last_node;
        (*tmp).set_next(nullptr);
        last_node = tmp;
    }

    void pop_front() {
        if (empty()) {
            return;
        }
        Node * new_first = (*first_node).get_next();
        delete first_node;
        first_node = new_first;
        if (empty()) {
            last_node = nullptr;
        }
    }

    int get_middle() {
        if (empty()) {
            return 0;
        }
        Node * tmp1 = first_node;
        Node * tmp2 = first_node;
        while((*tmp2).has_next()) {
            tmp2 = (*tmp2).get_next();
            if ((*tmp2).has_next()) {
                tmp2 = (*tmp2).get_next();
                tmp1 = (*tmp1).get_next();
            }
        }
        return (*tmp1).get_value();
    }
};

class ListTester {
public:

    static void run_test(const char* test_name, bool condition) {
        if (condition) {
            std::print("pass {}\n", test_name);
        } else {
            std::print("fail {}\n", test_name);
        }
    }

    static void run_all_tests() {
        test_empty();
        test_push_back();
        test_push_front();
        test_pop_back();
        test_pop_front();
        test_get_middle();
    }

    static void test_empty() {
        List list;
        run_test("empty", list.empty() && list.get_middle() == 0);
    }

    static void test_push_back() {
        List list;
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);
        list.push_back(40);
        
        run_test("push_back", !list.empty() && list.get_middle() == 20);
    }

    static void test_push_front() {
        List list;
        list.push_front(10);
        list.push_front(20);
        list.push_front(30);
        list.push_front(40);
        run_test("push_front", !list.empty() && list.get_middle() == 30);
    }

    static void test_pop_back() {
        List list;
        list.push_back(1);
        list.push_back(2);
        list.pop_back();
        run_test("pop_back", list.get_middle() == 1);
    }

    static void test_pop_front() {
        List list;
        list.push_back(1);
        list.push_back(2);
        list.pop_front();
        run_test("pop_front", list.get_middle() == 2);
    }

    static void test_get_middle() {
        List list1;
        for (int i = 0; i < 5; ++i) {
            list1.push_back(i);
        }
        List list2;
        for (int i = 0; i < 4; ++i) {
            list2.push_back(i);
        }
        run_test("middle", list1.get_middle() == 2 && list2.get_middle() == 1);
    }
};

int main() {
    ListTester tester = ListTester();
    tester.run_all_tests();

    List list = List();
    for (auto i = 0uz; i < 10e3; ++i) {
        list.push_back(i);
    }
    assert(list.get_middle() == 4999);
    for (auto i = 0uz; i < 10e3; ++i) {
        list.push_front(10e3 - i);
    }
    assert(list.get_middle() == 10e3);
    for (auto i = 0uz; i < 10e3; ++i) {
        list.pop_back();
    }
    assert(list.get_middle() == 5000);
    for (auto i = 0uz; i < 10e3 - 3; ++i) {
        list.pop_front();
    }

    list.show();
    assert(list.get_middle() == 9999);

    std::print("always ok\n");
}