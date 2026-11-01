#include<print>


class Entity {

    friend class Attorney_v1;

    friend class Attorney_v2;

private:
    static void test_v1() {
        std::print("test_v1\n");
    }

    static void test_v2() {
        std::print("test_v2\n");
    }
};

class Attorney_v1 {

    friend class Tester_v1;

private:
    static void test_v1() {
        Entity::test_v1();
    }
};

class Attorney_v2 {

    friend class Tester_v2;

private:
    static void test_v2() {
        Entity::test_v2();
    }

};

class Tester_v1 {
public:
    static void test() {
        Attorney_v1::test_v1();
    }
};

class Tester_v2 {
public:
    static void test() {
        Attorney_v2::test_v2();
    }
};

int main() {
    Tester_v1::test();
    Tester_v2::test();
}
