#include<iostream>
#include<print>

int main() {
    char input = 'a';

    std::cin >> input;

    switch (input) {
        case 'A' ... 'Z': {
            std::print("uppercase letter\n");
            break;
        }
        case 'a' ... 'z': {
            std::print("lowercase letter\n");
            break;
        }
        case '0' ... '9': {
            std::print("digit\n");
            break;
        }
        case '!': case ',' ... '.': case ':' ... ';': case '?': {
            std::print("punctuation letter\n");
            break;
        }
        default: {
            std::print("other\n");
            break;
        }    
    }
}