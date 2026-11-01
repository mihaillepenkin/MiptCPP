#include <cassert>
#include <string>
#include <iostream>

class String {
public:
    String(const std::string & s) : data(new Data(s)) {}

    String(const String & other) : data(other.data) {
        if (data == nullptr) {
            return;
        }
        data->ref_count++;
    }

    ~String() {
        if (data == nullptr) {
            return;
        }
        if (data->ref_count <= 1) {
            delete data;
        } else {
            data->ref_count--;
        }
    }

    String & operator=(const String & other) {
        if (&other == this) {
            return *this;
        }

        if (data != nullptr) {
            if (data->ref_count <= 1) {
                delete data;
            } else {
                data->ref_count--;
            }
        }
        


        data = other.data;

        if (data == nullptr) {
            return *this;
        }

        data->ref_count++;

        return *this;
    }

    std::string get() const {
        if (data == nullptr) {
            return "";
        }
        return data->text;
    }

    std::size_t getRefCount() const {
        if (data == nullptr) {
            return 0;
        }
        return data->ref_count;
    }

    void set(const std::string& s) {
        if (data == nullptr) {
            return;
        }
        copy();
        data->text = s;
    }

private:
    struct Data {
        std::string text = "";
        std::size_t ref_count = 1;

        Data(const std::string & s) : text(s), ref_count(1) {}
    };



    Data * data = nullptr;

    void copy() {
        if (data == nullptr) {
            return;
        }
        if (data->ref_count > 1) {
            data->ref_count--;
            data = new Data(data->text);
        }
    }
};

int main() {
    // 1. Тест конструктора от строки
    {
        String s1("Hello");
        assert(s1.get() == "Hello" && "Конструктор должен установить текст");
        assert(s1.getRefCount() == 1 && "ref_count должен быть 1");
    }

    // 2. Тест копирующего конструктора (разделение данных)
    {
        String s1("Hello");
        String s2 = s1;
        
        assert(s1.get() == "Hello" && "s1 должен сохранить текст");
        assert(s2.get() == "Hello" && "s2 должен получить копию текста");
        assert(s1.getRefCount() == 2 && "ref_count должен быть 2 после копирования");
        assert(s2.getRefCount() == 2 && "ref_count должен быть 2 для обеих копий");
    }

    // 3. Тест Copy-On-Write при set()
    {
        String s1("Hello");
        String s2 = s1;
        
        assert(s1.getRefCount() == 2 && "До изменения ref_count = 2");
        
        s2.set("World");  // Здесь должно произойти копирование
        
        assert(s1.get() == "Hello" && "s1 не должен измениться");
        assert(s2.get() == "World" && "s2 должен измениться");
        assert(s1.getRefCount() == 1 && "s1 должен иметь ref_count = 1");
        assert(s2.getRefCount() == 1 && "s2 должен иметь ref_count = 1");
    }

    // 4. Тест оператора присваивания
    {
        String s1("Hello");
        String s2("World");
        
        s2 = s1;
        
        assert(s1.get() == "Hello" && "s1 не должен измениться");
        assert(s2.get() == "Hello" && "s2 должен получить данные s1");
        assert(s1.getRefCount() == 2 && "ref_count должен быть 2");
    }

    // 5. Тест самоприсваивания
    {
        String s1("Hello");
        s1 = s1;
        
        assert(s1.get() == "Hello" && "Текст должен сохраниться");
        assert(s1.getRefCount() == 1 && "ref_count должен остаться 1");
    }

    // 6. Тест деструктора (освобождение памяти)
    {
        String* s1 = new String("Hello");
        String* s2 = new String(*s1);
        
        assert(s1->getRefCount() == 2 && "ref_count = 2");
        
        delete s1;  // Уменьшаем ref_count до 1
        
        // s2 всё ещё должна работать
        assert(s2->get() == "Hello" && "s2 должна работать после удаления s1");
        assert(s2->getRefCount() == 1 && "ref_count должен быть 1");
        
        delete s2;  // Теперь данные должны удалиться
    }

    // 7. Тест множественных копий
    {
        String s1("Hello");
        String s2 = s1;
        String s3 = s1;
        String s4 = s1;
        
        assert(s1.getRefCount() == 4 && "ref_count должен быть 4");
        
        s3.set("Changed");  // Копируем только s3
        
        assert(s1.get() == "Hello" && "s1 не изменился");
        assert(s2.get() == "Hello" && "s2 не изменился");
        assert(s3.get() == "Changed" && "s3 изменился");
        assert(s4.get() == "Hello" && "s4 не изменился");
        assert(s1.getRefCount() == 3 && "ref_count для общих данных = 3");
        assert(s3.getRefCount() == 1 && "ref_count для s3 = 1");
    }

    // 8. Тест цепочки присваиваний
    {
        String s1("A");
        String s2("B");
        String s3("C");
        
        s3 = s2 = s1;
        
        assert(s1.get() == "A" && "s1 = A");
        assert(s2.get() == "A" && "s2 = A");
        assert(s3.get() == "A" && "s3 = A");
        assert(s1.getRefCount() == 3 && "Все три объекта разделяют данные");
    }

    // 9. Тест изменения после присваивания
    {
        String s1("Original");
        String s2 = s1;
        
        s1.set("Modified");
        
        assert(s1.get() == "Modified" && "s1 изменился");
        assert(s2.get() == "Original" && "s2 не изменился");
        assert(s1.getRefCount() == 1 && "s1 имеет свои данные");
        assert(s2.getRefCount() == 1 && "s2 имеет свои данные");
    }
}