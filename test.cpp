#include <cassert>
#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
#include <stdexcept>

/*/

#include "ABDQ.hpp"



int main() {

    ABDQ<int> dq;

    for (int i=1; i< 10; i++) {
        dq.pushBack(i);
    }
    

    std::cout << "cap: " << dq.capacity_ << std::endl;
    



    int size = dq.size_;
    while (size--) {
        std::cout << dq.popFront() << std::endl;
    }


    return 0;
}


//*/


/* LINKED LIST TEST

#include "LinkedList.hpp" 


int main() {

    LinkedList<int> myLL;

    myLL.addHead(1);
    myLL.addHead(2);
    myLL.addHead(3);
    myLL.addHead(4);
    myLL.removeTail();
    myLL.removeHead();
    myLL.removeTail();
    //myLL.removeHead();


    LinkedList<int> newLL;

    
    newLL.Clear();
    
    newLL = myLL;
    newLL.addHead(100);
    myLL.printForward();
    newLL.printForward();
    

    return 0;
}

//*/