#include<cassert>
#include<print>

class Entity_v1 {
public:
    virtual ~Entity_v1() = default;

    virtual void test() const {
        std::print("entity test_v1\n");
    }
};

class Entity_v2 {
public:
    virtual ~Entity_v2() = default;

    virtual void test() const {
        std::print("entity test_v2\n");
    }
};

class Adapter_v1 : public Entity_v1 {
public:    
    virtual void test_v1() const {
        std::print("adapter test_v1\n");
    }

    void test() const override {
        test_v1();
    }
};

class Adapter_v2 : public Entity_v2 {
public:       
    virtual void test_v2() const {
        std::print("adapter test_v2\n");
    }

    void test() const override {
        test_v2();
    }
};

class Client final : public Adapter_v1, public Adapter_v2 {
public:    
    void test_v1() const override {
        std::print("client test_v1\n");

    }

    void test_v2() const override {
        std::print("client test_v2\n");
    }
};

int main() {
    Client client = {};
    client
    client.test_v1();
    client.test_v2();

    Entity_v1 & e1 = client;
    Entity_v2 & e2 = client;

    e1.test();
    e2.test();
}