#include <cassert>
#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>

//*
#include "ABDQ.hpp"

int main() {
    std::cout << "Starting out\n";
    // -------------------------------
    // 1. Default Constructor
    // -------------------------------
    {
        ABDQ<int> dq;
        
        assert(dq.getSize() == 0);

        dq.pushBack(1);
        dq.pushBack(2);
        dq.pushBack(3);

        assert(dq.getSize() == 3);
        assert(dq.front() == 1);
        assert(dq.back() == 3);
    }

    std::cout << "1 passed\n";

    // -------------------------------
    // 2. Parameterized Constructor
    // -------------------------------
    {
        ABDQ<int> dq(10);
        assert(dq.getSize() == 0);

        for (int i = 0; i < 5; i++) dq.pushBack(i);

        assert(dq.getSize() == 5);
        assert(dq.front() == 0);
        assert(dq.back() == 4);
    }

    std::cout << "2 passed\n";

    // -------------------------------
    // 3. Mixed pushFront / pushBack
    // -------------------------------
    {
        ABDQ<int> dq;

        dq.pushBack(10);   // [10]
        dq.pushFront(5);   // [5,10]
        dq.pushBack(20);   // [5,10,20]
        dq.pushFront(1);   // [1,5,10,20]

        assert(dq.getSize() == 4);
        assert(dq.front() == 1);
        assert(dq.back() == 20);

        // pop a few to ensure order
        assert(dq.popFront() == 1);
        assert(dq.popFront() == 5);
        assert(dq.popBack() == 20);
        assert(dq.popBack() == 10);
        assert(dq.getSize() == 0);
    }

    std::cout << "3 passed\n";

    // -------------------------------
    // 4. popFront / popBack correctness
    // -------------------------------
    {
        ABDQ<int> dq;
        dq.pushBack(1);
        dq.pushBack(2);
        dq.pushBack(3);

        assert(dq.popFront() == 1);
        assert(dq.popBack() == 3);
        assert(dq.front() == 2);
        assert(dq.back() == 2);
        assert(dq.getSize() == 1);
    }

    std::cout << "4 passed\n";

    // -------------------------------
    // 5. Wrap-Around Behavior
    // -------------------------------
    {
        ABDQ<int> dq(4);

        dq.pushBack(1);
        dq.pushBack(2);
        dq.pushBack(3);
        assert(dq.popFront() == 1);  // front moves forward

        dq.pushBack(4);  // should wrap around

        // Now logical order should be: 2, 3, 4
        assert(dq.getSize() == 3);
        assert(dq.front() == 2);
        assert(dq.back() == 4);

        assert(dq.popFront() == 2);
        assert(dq.popFront() == 3);
        assert(dq.popFront() == 4);
    }

    std::cout << "5 passed\n";

    // -------------------------------
    // 6. ensureCapacity() — resize growth
    // -------------------------------
    {
        ABDQ<int> dq(2);

        dq.pushBack(100);
        dq.pushBack(200);
        dq.pushBack(300); // should expand capacity to 4

        assert(dq.getSize() == 3);
        assert(dq.front() == 100);
        assert(dq.back() == 300);
    }

    std::cout << "6 passed\n";


    // -------------------------------
    // 8. Copy Constructor
    // -------------------------------
    {
        ABDQ<int> a;
        a.pushBack(1);
        a.pushBack(2);
        a.pushBack(3);

        ABDQ<int> b(a);  // copy

        assert(b.getSize() == 3);
        assert(b.front() == 1);
        assert(b.back() == 3);

        // ensure deep copy
        b.popFront();
        assert(a.front() == 1);
        assert(b.front() == 2);
    }

    std::cout << "8 passed\n";

    // -------------------------------
    // 9. Copy Assignment
    // -------------------------------
    {
        ABDQ<int> a;
        for (int i = 0; i < 5; i++) a.pushBack(i);

        ABDQ<int> b;
        b = a;

        assert(b.getSize() == 5);
        assert(b.front() == 0);
        assert(b.back() == 4);

        b.popBack();
        b.pushFront(99);

        assert(a.front() == 0);
        assert(a.back() == 4);
        assert(b.front() == 99);
        assert(b.back() == 3);
    }

    std::cout << "9 passed\n";

    // -------------------------------
    // 10. Move Constructor
    // -------------------------------
    {
        ABDQ<int> a;
        a.pushBack(7);
        a.pushBack(8);

        ABDQ<int> b(std::move(a));

        assert(b.getSize() == 2);
        assert(b.front() == 7);
        assert(b.back() == 8);

        // moved-from object must be empty
        assert(a.getSize() == 0);
    }

    std::cout << "10 passed\n";

    // -------------------------------
    // 11. Move Assignment
    // -------------------------------
    {
        ABDQ<int> a;
        a.pushBack(10);
        a.pushBack(20);

        ABDQ<int> b;
        b = std::move(a);

        assert(b.getSize() == 2);
        assert(b.front() == 10);
        assert(b.back() == 20);
        assert(a.getSize() == 0); // moved-from
    }

    std::cout << "11 passed\n";

    // -------------------------------
    // 12. Error Handling (pop on empty)
    // -------------------------------
    {
        ABDQ<int> dq;
        bool threw = false;

        try {
            dq.popFront();
        } catch (...) {
            threw = true;
        }

        assert(threw && "popFront() should throw on empty deque");
    }

    std::cout << "12 passed\n";

    return 0;
}


//*/

/*
#include "LLS.hpp"
int main() {




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