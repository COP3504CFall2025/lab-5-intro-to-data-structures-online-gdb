
/*/
#include <cassert>
#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
#include <stdexcept>

#include "ABDQ.hpp"



struct ABDQInterface {
    static const int SIZE = 4;
    
    int index;
    ABDQ<int>* cells[SIZE];

    ABDQInterface() : index(0) {}

    ~ABDQInterface() {c 
        for (int i=0; i< SIZE; i++) {
            if (cells[i] != nullptr) delete cells[i];
        }
    }


    void invalid() {
        std::cout << "Invalid input. Try again\n";
    }

    void change_options(bool empty) {
        if (empty) std::cout << "Observe (o), Edit (e), or Create (c): " << std::endl;
        else std::cout << "Observe (o) or Edit (e): " << std::endl;
        
        char option;
        std::cin >> option;
        
        if (option == 'o') {

        } else if (option == 'e') {

        } else if (empty && option == 'c') {

        } else {
            invalid();
            change_options(empty);
        }
        
    }

    void move_options() {
        std::cout << "Index: " << index << (cells[index] == nullptr ? "(null)" : "(active)") << std::endl;

        std::cout << "Options: " << std::endl;
        std::cout << "\tw - Go up" << std::endl;
        std::cout << "\ts - Go down" << std::endl;
        std::cout << "\tc - change" << std::endl;

        char option;
        std::cin >> option;

        if (option == 'w') {
            if (index > 0) index --;
        } else if (option == 's') {
            if (index < SIZE) index ++;
        } else if (option == 'c') {
            change_options(cells[index] == nullptr);
        } else {
            invalid();
        }
    }

};


int main() {
    ABDQ<int> dq;


    /* 
    - Tester-interface - :

    You can move up and down

    Cell options:
    //Watch
        - cap: capacity
        - size: size
        - f_: front_index
        - b_: back_index
        - front: front()
        - back: back()

    //Action
        - pushf - push front
        - pushb - push back
        - popf - pop front
        - popb - pop back
        - copy [int]
        - move [int] (deletes index int)
        - delete

    //Create
        - default
        - [int] -> capacity constructor
        - copy [from what]
        - move [from what]
    */

    

    
